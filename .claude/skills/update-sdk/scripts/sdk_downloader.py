#!/usr/bin/env python3
"""Download and replace direct SDK files (for plugins that don't use maven/cocoapods)."""

import sys
import json
import re
import shutil
import fnmatch
import tempfile
import zipfile
import argparse
from pathlib import Path

try:
    import requests
except ImportError:
    print("ERROR: Missing dependencies. Run: pip3 install requests")
    sys.exit(1)

CONFIG_PATH = ".claude/skills/update-sdk/scripts/config.json"
HEADERS = {"User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36"}

DOWNLOAD_KEYS = {
    "jpush": {"android": "android", "ios": "ios", "harmony": "hmos"},
    "jcore": {"android": "android", "ios": "ios"},
}


def load_config():
    with open(CONFIG_PATH, "r", encoding="utf-8") as f:
        return json.load(f)


def get_zip_url(sdk_type: str, platform: str) -> tuple[str, str]:
    """Follow redirect chain to get the actual zip URL and available version."""
    key = DOWNLOAD_KEYS.get(sdk_type, {}).get(platform)
    if not key:
        return "", "unknown"

    base_url = f"https://www.jiguang.cn/downloads/sdk/{key}"
    try:
        resp = requests.get(base_url, allow_redirects=True, headers=HEADERS, timeout=30)
        final_url = resp.url
    except requests.RequestException as e:
        print(f"  ERROR: Failed to resolve download URL: {e}")
        return "", "unknown"

    filename = Path(final_url.split("?")[0]).name
    match = re.search(r"(\d+\.\d+\.\d+)", filename)
    version = match.group(1) if match else "unknown"
    return final_url, version


def download_zip(zip_url: str) -> bytes | None:
    """Download a zip and return raw bytes."""
    print(f"  Downloading {zip_url.split('?')[0].split('/')[-1]} ...")
    try:
        resp = requests.get(zip_url, stream=True, headers=HEADERS, timeout=300)
        resp.raise_for_status()
    except requests.RequestException as e:
        print(f"  ERROR: Download failed: {e}")
        return None

    data = b""
    for chunk in resp.iter_content(chunk_size=65536):
        data += chunk
    print(f"  Downloaded {len(data) // 1024} KB")
    return data


def extract_xcframeworks(zip_data: bytes, ios_cfg: dict, dest_dir: Path) -> list[str]:
    """
    Extract .a and header files from xcframework slices inside the zip.

    For each entry in ios_cfg['xcframeworks']:
      - Find the xcframework dir matching name_glob inside zip_subdir
      - Navigate into the specified slice (e.g. ios-arm64)
      - Copy lib*.a files and Headers/*.h to dest_dir/dest_subdir/
    """
    zip_subdir = ios_cfg.get("zip_subdir", "")
    xcfw_configs = ios_cfg.get("xcframeworks", [])

    copied_files = []

    with tempfile.TemporaryDirectory() as tmp:
        tmp_path = Path(tmp)
        with zipfile.ZipFile(__import__("io").BytesIO(zip_data)) as zf:
            zf.extractall(tmp_path)

        # Locate the zip_subdir within the extracted tree
        candidates = list(tmp_path.rglob(zip_subdir.split("/")[-1])) if zip_subdir else [tmp_path]
        base_dir = None
        for c in candidates:
            if c.is_dir() and zip_subdir.split("/")[-1] in c.name:
                # Make sure it's the right path (matches zip_subdir suffix)
                rel = str(c.relative_to(tmp_path)).replace("\\", "/")
                if rel.endswith(zip_subdir) or zip_subdir.endswith(c.name):
                    base_dir = c
                    break
        if base_dir is None:
            # Fallback: search for any dir matching the last component
            matches = [p for p in tmp_path.rglob("*") if p.is_dir() and p.name == zip_subdir.split("/")[-1]]
            base_dir = matches[0] if matches else tmp_path

        for xcfw_cfg in xcfw_configs:
            name_glob = xcfw_cfg["name_glob"]
            slice_name = xcfw_cfg["slice"]
            dest_subdir = xcfw_cfg.get("dest_subdir", "")

            # Find xcframework dir matching name_glob
            xcfw_dirs = [p for p in base_dir.iterdir() if p.is_dir() and fnmatch.fnmatch(p.name, name_glob)]
            if not xcfw_dirs:
                print(f"  WARNING: No xcframework matching '{name_glob}' found in {base_dir}")
                continue

            xcfw_dir = xcfw_dirs[0]
            slice_dir = xcfw_dir / slice_name
            if not slice_dir.exists():
                print(f"  WARNING: Slice '{slice_name}' not found in {xcfw_dir.name}")
                continue

            out_dir = dest_dir / dest_subdir if dest_subdir else dest_dir
            out_dir.mkdir(parents=True, exist_ok=True)

            # Copy lib*.a from slice root
            for lib_file in slice_dir.glob("lib*.a"):
                dest_file = out_dir / lib_file.name
                shutil.copy2(lib_file, dest_file)
                print(f"  Copied {lib_file.name} → {out_dir}")
                copied_files.append(str(dest_file.relative_to(dest_dir.parent.parent.parent.parent)))

            # Copy Headers/*.h from slice
            headers_dir = slice_dir / "Headers"
            if headers_dir.exists():
                for h_file in sorted(headers_dir.glob("*.h")):
                    dest_file = out_dir / h_file.name
                    shutil.copy2(h_file, dest_file)
                    print(f"  Copied {h_file.name} → {out_dir}")
                    copied_files.append(str(dest_file.relative_to(dest_dir.parent.parent.parent.parent)))

    return copied_files


def extract_sdk_files(zip_url: str, dest_dir: Path, patterns: list) -> list[str]:
    """Download zip and extract files/dirs matching patterns into dest_dir (legacy flat mode)."""
    dest_dir.mkdir(parents=True, exist_ok=True)

    data = download_zip(zip_url)
    if data is None:
        return []

    with tempfile.TemporaryDirectory() as tmp:
        tmp_path = Path(tmp)
        with zipfile.ZipFile(__import__("io").BytesIO(data)) as zf:
            zf.extractall(tmp_path)
        copied = _copy_matching(tmp_path, dest_dir, patterns)

    return copied


SKIP_DIRS = {"example", "demo", "__MACOSX", ".git"}


def _copy_matching(src_root: Path, dest_dir: Path, patterns: list) -> list[str]:
    """Walk src_root and copy files/dirs whose name matches any pattern."""
    copied = []
    visited_dirs = set()
    copied_names = set()

    for item in sorted(src_root.rglob("*")):
        if any(part in SKIP_DIRS for part in item.parts):
            continue
        if any(item.is_relative_to(d) for d in visited_dirs):
            continue

        name = item.name
        if not any(fnmatch.fnmatch(name, p) for p in patterns):
            continue
        if name in copied_names:
            continue

        dest = dest_dir / name

        if item.is_dir():
            if dest.exists():
                shutil.rmtree(dest)
            shutil.copytree(item, dest)
            visited_dirs.add(item)
            print(f"  Copied {name}/ → {dest_dir}")
        else:
            shutil.copy2(item, dest)
            print(f"  Copied {name} → {dest_dir}")

        copied.append(name)
        copied_names.add(name)

    return copied


def replace_from_local(user_path: str, dest_dir: Path, ios_cfg: dict) -> dict:
    """Copy SDK files from a user-provided local path (zip or dir)."""
    src = Path(user_path)
    dest_dir.mkdir(parents=True, exist_ok=True)

    if src.is_file() and src.suffix == ".zip":
        print(f"  Extracting {src.name} ...")
        with open(src, "rb") as f:
            zip_data = f.read()
        if ios_cfg.get("xcframeworks"):
            copied = extract_xcframeworks(zip_data, ios_cfg, dest_dir)
        else:
            patterns = ios_cfg.get("file_patterns", ["*.a", "*.h"])
            with tempfile.TemporaryDirectory() as tmp:
                with zipfile.ZipFile(src) as zf:
                    zf.extractall(tmp)
                copied = _copy_matching(Path(tmp), dest_dir, patterns)
    else:
        patterns = ios_cfg.get("file_patterns", ["*.a", "*.h"])
        copied = _copy_matching(src, dest_dir, patterns)

    return {"status": "updated", "source": "user_provided", "files": copied}


def handle_platform(platform: str, sdk_type: str, target_version: str,
                    direct_cfg: dict, user_sdk_path: str | None) -> dict:
    print(f"\n=== {platform.upper()} SDK (target: v{target_version}) ===")
    dest_dir = Path(direct_cfg["dest_dir"])

    if user_sdk_path:
        result = replace_from_local(user_sdk_path, dest_dir, direct_cfg)
        return {"platform": platform, **result}

    zip_url, available_version = get_zip_url(sdk_type, platform)

    if not zip_url:
        return {"platform": platform, "status": "error", "reason": "Could not resolve download URL"}

    if sdk_type != "jcore" and available_version != target_version.lstrip("v"):
        msg = (f"Latest available version is {available_version}, "
               f"target {target_version} not yet released. "
               f"Re-run with --{platform}-sdk-path /path/to/sdk when available.")
        print(f"  ⚠️  {msg}")
        return {"platform": platform, "status": "version_mismatch",
                "available": available_version, "target": target_version, "reason": msg}

    # iOS: use xcframework extraction if configured
    if platform == "ios" and direct_cfg.get("xcframeworks"):
        data = download_zip(zip_url)
        if data is None:
            return {"platform": platform, "status": "error", "reason": "Download failed"}
        copied = extract_xcframeworks(data, direct_cfg, dest_dir)
    else:
        patterns = direct_cfg.get("file_patterns", ["*.aar", "*.jar", "*.a", "*.framework", "*.xcframework"])
        copied = extract_sdk_files(zip_url, dest_dir, patterns)

    if copied:
        return {"platform": platform, "status": "updated", "source": "auto", "files": copied}
    else:
        return {"platform": platform, "status": "error", "reason": "No matching files found in zip"}


def main():
    parser = argparse.ArgumentParser(description="Download and replace direct SDK files")
    parser.add_argument("--android", help="Android SDK target version")
    parser.add_argument("--ios", help="iOS SDK target version")
    parser.add_argument("--harmony", help="HarmonyOS SDK target version")
    parser.add_argument("--android-sdk-path", help="Local path to Android SDK (zip or dir)")
    parser.add_argument("--ios-sdk-path", help="Local path to iOS SDK (zip or dir)")
    parser.add_argument("--harmony-sdk-path", help="Local path to HarmonyOS SDK (zip or dir)")
    args = parser.parse_args()

    config = load_config()
    sdk_type = config.get("sdk_type", "jpush")
    direct_sdk = config.get("direct_sdk", {})

    if not direct_sdk:
        print("INFO: This plugin uses maven/cocoapods. No direct SDK files to manage.")
        return

    results = []
    platforms = [
        ("android", args.android, args.android_sdk_path),
        ("ios", args.ios, args.ios_sdk_path),
        ("harmony", args.harmony, args.harmony_sdk_path),
    ]

    for platform, version, user_path in platforms:
        if version and direct_sdk.get(platform):
            results.append(handle_platform(platform, sdk_type, version,
                                           direct_cfg=direct_sdk[platform],
                                           user_sdk_path=user_path))

    with open(".claude/skills/update-sdk/scripts/.sdk_download_result.json", "w") as f:
        json.dump(results, f, indent=2, ensure_ascii=False)

    print("\n=== SDK download summary ===")
    for r in results:
        icon = "✅" if r["status"] == "updated" else "⚠️ "
        detail = f" ({len(r.get('files', []))} files)" if r.get("files") else ""
        print(f"  {icon} {r['platform']}: {r['status']}{detail}")


if __name__ == "__main__":
    main()
