#!/bin/bash

# 从 GitHub 下载 JPush iOS SDK 与 JCore iOS SDK，并提取到 jg-jpush-u 插件目录
# JPush 仓库: https://github.com/jpush/jpush-sdk   JCore 仓库: https://github.com/jpush/jcore-sdk
# 使用方法: ./.cursor/scripts/download_ios_sdk.sh <JPush版本标签>
# 示例: ./.cursor/scripts/download_ios_sdk.sh v5.3.0

set -e  # 遇到错误立即退出

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 检查参数
if [ $# -eq 0 ]; then
    echo -e "${RED}错误: 请提供 JPush 版本标签${NC}"
    echo "使用方法: $0 <JPush版本标签>"
    echo "示例: $0 v5.3.0"
    exit 1
fi

VERSION_TAG=$1
REPO_URL="https://github.com/jpush/jpush-sdk.git"
JCORE_REPO_URL="https://github.com/jpush/jcore-sdk.git"
TEMP_DIR=$(mktemp -d)
JCORE_TEMP_DIR=$(mktemp -d)
# 使用项目根目录下的临时目录存放下载的 xcframework
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
TARGET_DIR="${PROJECT_ROOT}/.temp/ios-sdk"
# 插件目标目录：jg-jpush-u
PLUGIN_TARGET_DIR="${PROJECT_ROOT}/uni_modules/jg-jpush-u/utssdk/app-ios/Libs/JPush"
PLUGIN_JCORE_DIR="${PROJECT_ROOT}/uni_modules/jg-jpush-u/utssdk/app-ios/Libs/JCore"

# 处理版本标签（移除 'v' 前缀如果存在）
VERSION_NUMBER=${VERSION_TAG#v}
SDK_NAME="jpush-ios-${VERSION_NUMBER}.xcframework"

# 清理函数
cleanup() {
    if [ -d "$TEMP_DIR" ]; then
        rm -rf "$TEMP_DIR"
    fi
    if [ -d "$JCORE_TEMP_DIR" ]; then
        rm -rf "$JCORE_TEMP_DIR"
    fi
}

# 注册清理函数
trap cleanup EXIT

echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}JPush + JCore iOS SDK 下载工具 (jg-jpush-u)${NC}"
echo -e "${BLUE}========================================${NC}"
echo "JPush 版本标签: $VERSION_TAG"
echo "JPush SDK 名称: $SDK_NAME"
echo "目标目录: $TARGET_DIR"
echo "插件 JPush 目录: $PLUGIN_TARGET_DIR"
echo "插件 JCore 目录: $PLUGIN_JCORE_DIR"
echo ""

# 检查 git 是否安装
if ! command -v git &> /dev/null; then
    echo -e "${RED}错误: 未找到 git 命令，请先安装 git${NC}"
    exit 1
fi

# 检查目标目录是否存在
if [ ! -d "$TARGET_DIR" ]; then
    echo -e "${YELLOW}创建目标目录: $TARGET_DIR${NC}"
    mkdir -p "$TARGET_DIR"
fi

# 克隆仓库到临时目录
echo -e "${GREEN}[1/5] 正在克隆仓库 (标签: $VERSION_TAG)...${NC}"
if ! git clone --depth 1 --branch "$VERSION_TAG" "$REPO_URL" "$TEMP_DIR" 2>&1 | grep -v "Cloning into"; then
    echo -e "${RED}错误: 无法克隆仓库或标签不存在${NC}"
    echo "请检查版本标签是否正确: $VERSION_TAG"
    echo ""
    echo -e "${YELLOW}提示: 可以使用以下命令查看所有可用标签:${NC}"
    echo "git ls-remote --tags $REPO_URL | grep -o 'refs/tags/.*' | sed 's|refs/tags/||' | sort -V"
    exit 1
fi

# 检查 SDK 文件是否存在
SDK_PATH="$TEMP_DIR/$SDK_NAME"
if [ ! -d "$SDK_PATH" ]; then
    echo -e "${YELLOW}未找到 $SDK_NAME，正在查找 jpush-ios-*.xcframework...${NC}"
    FOUND=$(find "$TEMP_DIR" -type d -name "jpush-ios-*.xcframework" 2>/dev/null | head -1)
    if [ -n "$FOUND" ]; then
        SDK_NAME=$(basename "$FOUND")
        SDK_PATH="$FOUND"
        echo -e "${YELLOW}使用找到的 SDK: $SDK_NAME${NC}"
    else
        echo -e "${RED}错误: 在仓库中未找到 jpush-ios-*.xcframework${NC}"
        exit 1
    fi
fi

# 显示 SDK 信息
SDK_SIZE=$(du -sh "$SDK_PATH" | cut -f1)
echo -e "${GREEN}[2/5] 找到 SDK (大小: $SDK_SIZE)${NC}"

# 删除旧版本（如果存在）
OLD_SDK=$(find "$TARGET_DIR" -type d -name "jpush-ios-*.xcframework" 2>/dev/null | head -1)
if [ -n "$OLD_SDK" ]; then
    OLD_NAME=$(basename "$OLD_SDK")
    if [ "$OLD_NAME" != "$SDK_NAME" ]; then
        echo -e "${YELLOW}[3/5] 删除旧版本: $OLD_NAME${NC}"
        rm -rf "$OLD_SDK"
    else
        echo -e "${YELLOW}[3/5] 检测到相同版本，将覆盖...${NC}"
        rm -rf "$OLD_SDK"
    fi
else
    echo -e "${GREEN}[3/5] 未找到旧版本${NC}"
fi

# 复制新 SDK
echo -e "${GREEN}[4/5] 正在复制 SDK 到目标目录...${NC}"
cp -R "$SDK_PATH" "$TARGET_DIR/"

# 验证复制是否成功
if [ ! -d "$TARGET_DIR/$SDK_NAME" ]; then
    echo -e "${RED}错误: SDK 复制失败${NC}"
    exit 1
fi

# 提取文件到插件目录
echo -e "${GREEN}[5/5] 正在提取文件到插件目录...${NC}"
XCFRAMEWORK_PATH="$TARGET_DIR/$SDK_NAME"
IOS_ARM64_PATH="$XCFRAMEWORK_PATH/ios-arm64"

# 检查 ios-arm64 目录是否存在
if [ ! -d "$IOS_ARM64_PATH" ]; then
    echo -e "${RED}错误: 未找到 ios-arm64 目录: $IOS_ARM64_PATH${NC}"
    exit 1
fi

# 检查源文件：libJPush.a、JPUSHService.h
LIB_FILE="$IOS_ARM64_PATH/libJPush.a"
HEADER_FILE="$IOS_ARM64_PATH/Headers/JPUSHService.h"

if [ ! -f "$LIB_FILE" ]; then
    echo -e "${RED}错误: 未找到静态库 libJPush.a: $IOS_ARM64_PATH${NC}"
    exit 1
fi

if [ ! -f "$HEADER_FILE" ]; then
    echo -e "${RED}错误: 未找到头文件 JPUSHService.h: $IOS_ARM64_PATH/Headers/${NC}"
    exit 1
fi

# 确保目标目录存在
if [ ! -d "$PLUGIN_TARGET_DIR" ]; then
    echo -e "${YELLOW}创建插件目标目录: $PLUGIN_TARGET_DIR${NC}"
    mkdir -p "$PLUGIN_TARGET_DIR"
fi

# 复制到插件目录，统一输出为 JPush 文件名（jg-jpush-u 使用 libJPush.a、JPUSHService.h）
echo -e "${YELLOW}  复制 libJPush.a...${NC}"
cp "$LIB_FILE" "$PLUGIN_TARGET_DIR/libJPush.a"

echo -e "${YELLOW}  复制 JPUSHService.h...${NC}"
cp "$HEADER_FILE" "$PLUGIN_TARGET_DIR/JPUSHService.h"

# ---------- 下载并提取 JCore iOS SDK (https://github.com/jpush/jcore-sdk) ----------
echo ""
echo -e "${GREEN}[JCore] 正在克隆 JCore SDK 仓库 (main 分支，最新版本)...${NC}"
if ! git clone --depth 1 --branch main "$JCORE_REPO_URL" "$JCORE_TEMP_DIR" 2>/dev/null; then
    echo -e "${RED}错误: 无法克隆 JCore 仓库${NC}"
    exit 1
fi

JCORE_XCF=$(find "$JCORE_TEMP_DIR" -type d -name "jcore-ios-*.xcframework" 2>/dev/null | sort -V | tail -1)
if [ -z "$JCORE_XCF" ] || [ ! -d "$JCORE_XCF" ]; then
    echo -e "${RED}错误: 在 JCore 仓库中未找到 jcore-ios-*.xcframework${NC}"
    exit 1
fi

JCORE_ARM64="${JCORE_XCF}/ios-arm64"
if [ ! -d "$JCORE_ARM64" ]; then
    echo -e "${RED}错误: 未找到 JCore ios-arm64 目录: $JCORE_ARM64${NC}"
    exit 1
fi

JCORE_LIB="${JCORE_ARM64}/libJCore.a"
JCORE_HEADERS_DIR="${JCORE_ARM64}/Headers"
if [ ! -f "$JCORE_LIB" ]; then
    echo -e "${RED}错误: 未找到 libJCore.a: $JCORE_ARM64${NC}"
    exit 1
fi

if [ ! -d "$PLUGIN_JCORE_DIR" ]; then
    mkdir -p "$PLUGIN_JCORE_DIR"
fi

echo -e "${YELLOW}  复制 libJCore.a 及头文件到 JCore 目录...${NC}"
cp "$JCORE_LIB" "$PLUGIN_JCORE_DIR/libJCore.a"
if [ -d "$JCORE_HEADERS_DIR" ]; then
    for f in "$JCORE_HEADERS_DIR"/*.h; do
        [ -f "$f" ] && cp "$f" "$PLUGIN_JCORE_DIR/" && echo -e "${YELLOW}     $(basename "$f")${NC}"
    done
fi

# 验证 JPush 与 JCore 文件是否均成功复制
JPUSH_OK=0
JCORE_OK=0
[ -f "$PLUGIN_TARGET_DIR/libJPush.a" ] && [ -f "$PLUGIN_TARGET_DIR/JPUSHService.h" ] && JPUSH_OK=1
[ -f "$PLUGIN_JCORE_DIR/libJCore.a" ] && JCORE_OK=1

if [ "$JPUSH_OK" -eq 1 ] && [ "$JCORE_OK" -eq 1 ]; then
    LIB_SIZE=$(du -sh "$PLUGIN_TARGET_DIR/libJPush.a" | cut -f1)
    HEADER_SIZE=$(du -sh "$PLUGIN_TARGET_DIR/JPUSHService.h" | cut -f1)
    JCORE_LIB_SIZE=$(du -sh "$PLUGIN_JCORE_DIR/libJCore.a" | cut -f1)
    echo ""
    echo -e "${BLUE}========================================${NC}"
    echo -e "${GREEN}✓ JPush + JCore SDK 下载和提取完成!${NC}"
    echo -e "${BLUE}========================================${NC}"
    echo "JPush SDK: $TARGET_DIR/$SDK_NAME ($SDK_SIZE)"
    echo ""
    echo -e "${GREEN}已提取到插件 (jg-jpush-u):${NC}"
    echo "  - JPush: $PLUGIN_TARGET_DIR/libJPush.a ($LIB_SIZE), JPUSHService.h ($HEADER_SIZE)"
    echo "  - JCore: $PLUGIN_JCORE_DIR/libJCore.a ($JCORE_LIB_SIZE) 及头文件"
    
    # 清理临时目录
    if [ -d "$TARGET_DIR" ]; then
        echo ""
        echo -e "${YELLOW}清理临时文件...${NC}"
        rm -rf "$TARGET_DIR"
        echo -e "${GREEN}✓ 已清理 .temp/ios-sdk 目录${NC}"
    fi
else
    echo -e "${RED}错误: 文件提取失败 (JPush:$JPUSH_OK JCore:$JCORE_OK)${NC}"
    exit 1
fi

