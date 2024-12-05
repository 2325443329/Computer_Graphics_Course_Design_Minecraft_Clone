#ifndef UTILS_H
#define UTILS_H

#include "libraries.h"

// 常量定义
constexpr float						pi = 3.14159265359f;			// 圆周率 (Pi)
constexpr float						framerate = 60.f;						// 最大帧率 (每秒最大帧数)
constexpr float						frame_duration = 1.f / framerate;			// 每帧的最小时长
constexpr float						frame_duration_ms = 1.f / framerate * 1e3;	// 每帧的时长，单位：毫秒
constexpr float						epsilon = 0.01f;					// 一个较小的常数值
constexpr float						epsilon_2 = 0.005f;					// 一个更小的常数值

// 定义一组位置，用于围绕某个点的四个方向
constexpr std::array<glm::ivec3, 4>	around_positions = { glm::ivec3(-1, 0, 0), glm::ivec3(1, 0, 0), glm::ivec3(0, 0, -1), glm::ivec3(0, 0, 1) };

// 类型别名
typedef glm::vec4 Color;	// 定义颜色类型，包括透明度
typedef glm::vec3 ColorRGB;	// 定义RGB颜色类型，不包括透明度
typedef glm::vec4 Plane;	// 定义平面类型

// 外部声明，互斥锁
extern std::mutex lock;

// 定义一个窗口结构体，包含窗口的属性和操作
struct Window
{
	static SDL_Window* window;		// 窗口对象
	static SDL_GLContext	context;	// OpenGL上下文
	static glm::ivec2		size;		// 窗口大小
	static glm::ivec2		center;		// 窗口中心位置

	// 窗口初始化方法
	static bool				init();

	// 清除窗口
	static void				clear();
};

// 函数声明

// 将3D向量进行四舍五入处理
glm::ivec3	round(const glm::vec3& vector);

// 生成指定范围内的随机整数
int32_t		random_int(int32_t min, int32_t max);

// 生成指定范围内的随机浮动数
float		random_float(float min, float max);

// 根据指定的概率返回随机布尔值
bool		rand_probability(float probability);

// 获取3D向量的水平分量
float		get_horizontal_norm(const glm::vec3& vector);

// 设置3D向量的水平分量
void		set_horizontal_norm(glm::vec3& vector, float value);

// 矩阵与向量的乘法运算
glm::vec3	operator*(const glm::mat4& matrix, const glm::vec3& vector);

// 归一化一个浮动值到[0, 1]区间
float		normalize(float number);

// 将一个值映射到指定的最小最大范围内
float		ratio(float number, float min, float max);

// 对一个值进行平滑的限制，限制范围内的平滑过渡
float		smooth_clamp(float value, float min, float max, float smoothness);

#endif
