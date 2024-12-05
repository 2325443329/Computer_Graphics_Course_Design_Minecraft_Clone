# bjfu22cggroup2（本项目相关）

## 项目说明

在下载本文件之后，建议使用 CMake 进行整合。请依照以下步骤进行操作：

1. 在解压后的文件夹中依次输入：

```bash
mkdir build    # 创建 build 文件夹
cd build       # 进入 build 文件夹
cmake ..       # 可以不使用命令行指令，直接在文件资源管理器中创建 build 文件夹并进入，再打开命令行输入该命令
cmake --build . # 编译工程
```

这样就可以在 `build` 文件夹中找到我们熟悉的 `.sln` 文件，在 `bin` 文件夹中可以找到我们需要的 `.exe` 文件。

## 项目上传流程

在项目组成员进行上传时，请按以下步骤操作：

1. **获取远程仓库的最新更新：**

```bash
git fetch origin  # 从远程仓库获取最新的更新（不合并）
git status        # 检查本地仓库的当前状态，确认是否落后于远程仓库
```

2. **拉取远程更新并合并：**

```bash
git pull origin main  # 拉取并自动合并远程 main 分支上的更新
```

3. **检查修改的文件：**

```bash
git status    # 显示修改、添加、删除的文件
git diff      # 查看具体修改了哪些内容
```

4. **将修改的文件添加到暂存区：**

```bash
git add .         # 添加所有修改的文件到暂存区
# 或者
git add <file1> <file2> ...  # 仅添加特定文件
```

5. **提交修改：**

```bash
git commit -m "描述本次修改的内容"  # 提交修改，并描述本次修改的内容
```

6. **推送修改到远程仓库：**

```bash
git push origin main  # 将本地提交推送到远程 GitHub 仓库
```

7. **查看本次提交修改了哪些文件（可选）：**

```bash
git show --name-only  # 查看本次提交修改了哪些文件
```
本项目协作者：
* [**WenHe Wan**](https://github.com/2325443329)
* [**ShiHuang Liu**](https://github.com/Lieos123)
* [**SiChen Li**](https://github.com/ChineseFootballKingAweiluo)
* [**PengCheng Yuan**]
* [**MinJia Zhu**]
---
本项目大都参考自该开源项目，感谢开源，我们对它进行了一点点修改，使得它可以切换player的皮肤纹理和生物与player的碰撞检测
# ⛏️ Minecraft clone

![Release](https://img.shields.io/badge/Release-v2.0-blueviolet)
![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)
![Libraries](https://img.shields.io/badge/Libraries-OpenGL_SDL_GLM-20d645)
![Size](https://img.shields.io/badge/Size-53%20Mo-f12222)
![Open Source](https://badges.frapsoft.com/os/v2/open-source.svg?v=103)

<br/>

*⚠️ This project was made for school with a deadline and I chose to leave it as it was at the time of submission ⚠️*

<br/>

This program uses the concept of the famous game Minecraft but with better graphics. It procedurally generates an infinite world, the player has an animated character and can break blocks, there are also different biomes and mobs.

<br/>

<p align="center">
	<img src="https://i.imgur.com/RCGkX52.png" width="700">
</p>

<br/>

# 📋 Summary

* **[📋 Summary](#-summary)**
* **[🎥 Video](#-video)**
* **[🧪 Tests](#-tests)**
* **[📝 Notes](#-notes)**
* **[🙏 Credits](#-credits)**

<br/>

<br/>

# 🎥 Video

Here is a video presenting the program :

[<p align="center"><img src="https://i.imgur.com/StJSmmr.png" width="500"></p>](https://www.youtube.com/watch?v=muUEtjMYQMY)

<br/>

# 🧪 Tests

<p align="center">
	<img src="https://i.imgur.com/cyE45Ji.png" width="700">
</p>

<p align="center">
	<img src="https://i.imgur.com/7aaPlvT.png" width="700">
</p>

<p align="center">
	<img src="https://i.imgur.com/PBEU62t.png" width="700">
</p>

<p align="center">
	<img src="https://i.imgur.com/4p2mObU.png" width="700">
</p>

<br/>

# 📝 Notes

This program is a school project for Polytech Paris-Saclay as part of our computer graphics course and we won a prize for the best project :

<p align="center">
	<img src="https://i.imgur.com/pyCPLJq.png" width="700">
</p>

<br/>

# 🙏 Credits

* [**Angel Uriot**](https://github.com/angeluriot) : Co-creator of the project.
* [**Gaétan Renard**]() : Co-creator of the project.
* [**Arthur Azambre**](https://github.com/arthurazambre) : Co-creator of the project.
