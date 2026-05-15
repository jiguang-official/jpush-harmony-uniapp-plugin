---
name: update-sdk
description: |
  更新 jpush-harmony-uniapp-plugin 及其子模块（fcm/huawei/honor/meizu/nio/oppo/vivo/xiaomi）的 JPush SDK 版本。自动拉取极光官网 Changelog，更新主模块 Android config.json（Maven）和 iOS 直引静态库（.a 文件），更新 UTS 层（app-android/app-ios/app-harmony/interface.uts）代码，支持 --module 参数指定子模块，展示变更摘要确认后提示手动上传至 DCloud 插件市场。
  Use when: 更新 JPush SDK、升级推送 SDK 版本、UTS 插件更新、鸿蒙插件 SDK 更新、jpush-harmony-uniapp-plugin 发布新版本、更新厂商通道子模块。
allowed-tools:
  - Bash
  - Read
  - Edit
  - Write
  - WebFetch
---

你正在更新 **jpush-harmony-uniapp-plugin** 及其子模块。

**用户参数：** $ARGUMENTS

---

## 第一步：解析参数

从 `$ARGUMENTS` 中提取：
- `--android X.X.X` → Android JPush SDK 目标版本（Android 端通过 config.json maven 引用）
- `--ios X.X.X` → iOS JPush SDK 目标版本（iOS 端直引 .a 静态库）
- `--module mod1,mod2` → 可选，指定更新哪些子模块（缺省更新全部 8 个子模块）
  - 可选值：`fcm`、`huawei`、`honor`、`meizu`、`nio`、`oppo`、`vivo`、`xiaomi`
- `--ios-sdk-path /path` → 可选，本地 iOS SDK 路径（当官网版本不一致时使用）

---

## 第二步：安装依赖

```bash
pip3 install requests beautifulsoup4 -q 2>&1 | tail -1
```

---

## 第三步：拉取 SDK Changelog

```bash
python3 .claude/skills/update-sdk/scripts/changelog_fetcher.py --android <ANDROID_VERSION> --ios <IOS_VERSION>
```

读取 `.claude/skills/update-sdk/scripts/.changelog_cache.json`。

---

## 第四步：AI 分析变更

分析 Changelog，整理：

> **注意**：Changelog 同时包含 JPush 和 JCore 的变更。

1. 新增 API（Android/iOS/Harmony 三端各自的新功能）
2. 若 Android 和 iOS 有相同语义的新 API，在 `interface.uts` 中合并为一个统一接口；**不要直接标为单端 Only**，先检查另一端是否已有等价实现（见下方说明）
3. 移除/废弃 API
4. 行为变更
5. 新插件版本号（`uni_modules/jg-jpush-u/package.json`）：始终升 patch（如 3.4.9 → 3.5.0，3.9.9 → 4.0.0）

> **跨平台等价检查**：当 Changelog 只在某一端（如 Android）出现新增 API 时，先读取另一端的 UTS 文件（`app-android/index.uts` 或 `app-ios/index.uts`），搜索功能相同或名称相近的方法。如果另一端已有对应实现，则在 `interface.uts` 中合并为统一接口；只有确认另一端完全没有等价功能时，才标注单端 Only。

---

## 第五步：更新主模块版本号引用

```bash
python3 .claude/skills/update-sdk/scripts/plugin_updater.py \
  --android <ANDROID_VERSION> \
  --bump-patch \
  --changelog-summary "<ONE_LINE_SUMMARY>"
```

（iOS 直引 .a 文件，版本号在文件本身，不在 config.json 中引用）

---

## 第六步：更新子模块 Android config.json（按 --module 过滤）

读取 `.claude/skills/update-sdk/scripts/config.json` 中的 `uts_sub_modules` 列表，对每个需要更新的子模块：

```python
# 伪代码，实际由 Claude 逐个执行
for module in selected_modules:
    update config.json: dependencies 中厂商 SDK 的版本号
    update package.json: version 字段
```

示例——更新 jg-jpush-u-huawei 子模块（若华为 SDK 版本需要同步更新）：
读取 `uni_modules/jg-jpush-u-huawei/utssdk/app-android/config.json`，找到华为推送 SDK 的 dependency，更新版本。

---

## 第七步：检查并替换 iOS SDK 文件（直引 .a 库）

```bash
python3 .claude/skills/update-sdk/scripts/sdk_downloader.py \
  --ios <IOS_VERSION> \
  [--ios-sdk-path <PATH>]
```

替换 `uni_modules/jg-jpush-u/utssdk/app-ios/Libs/` 下的 `libJPush.a`、`libJCore.a` 及头文件。

---

## 第八步：更新 UTS 层代码

**编写代码前，先通过 WebFetch 查询官网 API 文档，确认新增方法的完整签名、参数类型和返回值：**
- Android 文档：`https://docs.jiguang.cn/jpush/client/Android/android_api`
- iOS 文档：`https://docs.jiguang.cn/jpush/client/iOS/ios_api`

在文档中搜索第四步识别出的新增方法名，确认签名后再编写下方代码。

根据第四步的变更计划，编辑以下文件：

**Android** — `uni_modules/jg-jpush-u/utssdk/app-android/index.uts`
- 添加新 API 实现，调用 JPush Android SDK 对应方法

**iOS** — `uni_modules/jg-jpush-u/utssdk/app-ios/index.uts`
- 添加新 API 实现，调用 JPush iOS SDK 对应方法

**Harmony** — `uni_modules/jg-jpush-u/utssdk/app-harmony/index.uts`
- 添加新 API 实现（如 Harmony 端 SDK 有对应功能）

**接口定义** — `uni_modules/jg-jpush-u/utssdk/interface.uts`
- 为所有新增统一 API 添加接口声明

---

## 第九步：展示变更摘要并请求确认

```
========== jpush-harmony-uniapp-plugin 更新摘要 ==========
Android JPush SDK: 旧版本 → 新版本（config.json 已更新）
iOS JPush SDK:     旧版本 → 新版本（.a 文件已替换）
主模块版本:         旧版本 → 新版本

新增 API（UTS 统一接口）：
  + methodName(params): ReturnType  // 说明

更新的子模块：
  ✅ jg-jpush-u-fcm     → vX.X.X
  ✅ jg-jpush-u-huawei  → vX.X.X
  ...

修改的文件：...

⚠️  以下所有子目录需手动上传至 DCloud 插件市场：
  - uni_modules/jg-jpush-u
  - uni_modules/jg-jpush-u-fcm
  ...（共 9 个）
=========================================================

确认以上变更并继续？[y/N]
```

---

## 第十步：发布提示（确认后执行）

```bash
python3 .claude/skills/update-sdk/scripts/publisher.py
```

脚本打印所有需上传的 DCloud 子模块路径，并完成 git commit/tag/push。
