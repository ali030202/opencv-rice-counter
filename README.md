# OpenCV Rice Counter

基于 C++ 和 OpenCV 的图像处理练习项目。主程序读取仓库中的 `rice.tif`，通过阈值分割和轮廓面积筛选估算图像中的米粒数量；仓库还包含若干独立的滤波、边缘检测和图像缩放示例。

## 功能

- **米粒计数（`sy1.cpp`）**：灰度读取、Gaussian 模糊、自适应阈值、腐蚀与膨胀、外轮廓提取，并按轮廓面积阈值计数。
- **滤波示例**：中值滤波、均值滤波和高斯滤波；部分示例同时比较 OpenCV 内置函数与手写实现。
- **边缘与圆检测示例**：Canny 边缘检测和 Hough 圆检测。
- **缩放与旋转示例（`demoMyResize.cpp`）**：手写最近邻缩放，并与 OpenCV 的 `resize` 对比。

> 当前 Visual Studio 工程默认只编译 `sy1.cpp`。其余源文件各自包含入口函数，应作为独立示例分别运行。

## 环境要求

- Windows
- Visual Studio 2022（MSVC v143）及 Windows SDK
- OpenCV 4.9.0；工程当前 Debug x64 配置指向 `E:\\opencv`，并链接 `opencv_world490d.lib`

如果 OpenCV 安装在其他位置，请在 Visual Studio 项目属性中调整 **C/C++ → 附加包含目录**、**链接器 → 附加库目录**和**链接器 → 输入 → 附加依赖项**。运行时还需要让对应的 OpenCV DLL 位于可执行文件目录或系统 `PATH` 中。

## 运行米粒计数

1. 克隆仓库并打开解决方案：

   ```bash
   git clone https://github.com/ali030202/opencv-rice-counter.git
   ```

2. 在 Visual Studio 中打开 `Project3.sln`，选择 **Debug | x64**，确认 OpenCV 路径与本机安装一致。
3. 将调试工作目录设为仓库根目录（`$(ProjectDir)`），因为程序以相对路径读取 `rice.tif`。
4. 编译并运行。程序会显示灰度图、阈值图以及形态学处理结果，并在控制台输出估算数量：

   ```text
   Number of rices: <count>
   ```

## 计数流程

```text
rice.tif
  → 灰度图
  → 5×5 GaussianBlur
  → 自适应阈值
  → 腐蚀 2 次、膨胀 2 次
  → 提取外轮廓
  → 只统计面积大于 110 的轮廓
```

面积阈值写在 `sy1.cpp` 中，针对当前示例图像设置。换用图像或调整光照后，通常需要重新检查阈值和形态学参数；该示例用于学习传统图像处理流程，不是面向任意场景的通用计数器。

## 项目文件

| 文件 | 说明 |
| --- | --- |
| `sy1.cpp` | 默认启动的米粒计数程序 |
| `rice.tif` | 米粒计数示例图像 |
| `中值滤波.cpp` | OpenCV 中值滤波与手写中值滤波对比 |
| `均值滤波.cpp` | OpenCV 均值滤波与手写均值滤波对比 |
| `高斯滤波.cpp` | OpenCV 高斯滤波与手写高斯滤波对比 |
| `边缘检测.cpp` | Canny 和 Hough 圆检测示例 |
| `temp.cpp` | Hough 圆检测示例 |
| `demoMyResize.cpp` | 图像缩放与旋转示例 |
| `Project3.sln` | Visual Studio 解决方案 |

除 `rice.tif` 外，其他示例引用的 `salt-0.05.bmp`、`salt-0.1.bmp`、`circle.bmp` 和 `img_A.png` 未包含在当前仓库中；运行相应示例前，需要自行提供这些输入图像，或修改源码中的文件路径。
