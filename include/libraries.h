#ifndef LIBRARIES_H
#define LIBRARIES_H

// SDL 库
#include <SDL2/SDL.h>					// SDL 主库
#include <SDL2/SDL_syswm.h>				// SDL 系统窗口管理
#include <SDL2/SDL_image.h>				// SDL 图像处理

// OpenGL 库
#include <GL/glew.h>					// GLEW，用于加载 OpenGL 扩展
#include <GL/gl.h>						// OpenGL 核心库

// GML（OpenGL Shading Language）库
#include <glm/glm.hpp>					// GLM 基础数学库
#include <glm/gtc/matrix_transform.hpp>	// GLM 矩阵变换
#include <glm/gtc/type_ptr.hpp>			// GLM 类型指针
#include <glm/gtc/noise.hpp>				// GLM 噪声函数

// 其他常用库
#include <atomic>						// 原子操作支持
#include <array>							// 数组容器
#include <cmath>							// 数学函数
#include <vector>							// 向量容器
#include <mutex>							// 互斥量支持
#include <thread>							// 线程支持
#include <iostream>						// 输入输出流
#include <stdlib.h>						// 标准库函数
#include <stdint.h>						// 固定大小整数类型
#include <stdio.h>						// 标准输入输出
#include <string.h>						// 字符串处理
#include <random>						// 随机数生成
#include <algorithm>						// 常用算法
#include <numeric>						// 数值算法
#include <cstdlib>						// C标准库函数
#include <stack>							// 栈容器
#include <list>							// 链表容器
#include <utility>						// 工具函数
#include <cstring>						// C 风格字符串处理
#include <memory>						// 内存管理
#include <iomanip>						// 输入输出格式控制

#endif
