#include "utils.h"
#include "Shader.h"

std::mutex		lock;

SDL_Window* Window::window = NULL;
SDL_GLContext	Window::context = NULL;
glm::ivec2		Window::size = glm::ivec2(10, 10);
glm::ivec2		Window::center = glm::ivec2(5, 5);

// 初始化窗口
bool Window::init()
{
	// 初始化SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		SHADER_ERROR("SDL初始化失败: %s\n", SDL_GetError());
		return false;
	}

	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0, &screen);

	size.x = screen.w * (3.f / 4.f);
	size.y = screen.h * (3.f / 4.f);
	center.x = size.x / 2;
	center.y = size.y / 2;

	// 创建窗口
	window = SDL_CreateWindow("Minecraft clone",	// 标题
		SDL_WINDOWPOS_UNDEFINED,					// X 位置
		SDL_WINDOWPOS_UNDEFINED,					// Y 位置
		size.x, size.y,								// 分辨率
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);		// 标志（OpenGL + 显示）

	// 初始化OpenGL版本（版本3.0）
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// 初始化OpenGL上下文（OpenGL资源的存储位置）
	context = SDL_GL_CreateContext(window);

	// 告诉GLEW初始化此版本的OpenGL功能
	glewExperimental = GL_TRUE;
	glewInit();

	// 开始使用OpenGL绘制内容
	glViewport(0, 0, size.x, size.y); // 绘制整个屏幕

	// 设置OpenGL背景颜色（RGBA，每个组件的值在0.f到1.f之间）
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glEnable(GL_DEPTH_TEST); // 启用深度测试
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 启用裁剪平面
	glEnable(GL_CLIP_DISTANCE0);

	// 启用面剔除，仅显示朝向正确的面
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	return true;
}

// 销毁窗口
void Window::clear()
{
	if (context != NULL)
		SDL_GL_DeleteContext(Window::context);

	if (window != NULL)
		SDL_DestroyWindow(Window::window);
}

// 将浮点向量转换为整数向量
glm::ivec3 round(const glm::vec3& vector)
{
	return glm::ivec3(std::round(vector.x), std::round(vector.y), std::round(vector.z));
}

// 返回一个在min和max之间的随机整数
int32_t random_int(int32_t min, int32_t max)
{
	return (rand() % (max - min)) + min;
}

// 返回一个在min和max之间的随机浮点数
float random_float(float min, float max)
{
	return (rand() / static_cast<float>(RAND_MAX)) * (max - min) + min;
}

// 给定概率返回真
bool rand_probability(float probability)
{
	if (probability < 0.f)
		return false;

	if (probability < 1.f)
		return (rand() / static_cast<float>(RAND_MAX) < probability);

	return true;
}

// 计算向量的水平长度
float get_horizontal_norm(const glm::vec3& vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.z, 2));
}

// 修改向量的水平长度
void set_horizontal_norm(glm::vec3& vector, float value)
{
	float norm = get_horizontal_norm(vector);

	if (norm != 0)
	{
		vector.x /= norm;
		vector.z /= norm;

		vector.x *= value;
		vector.z *= value;
	}
}

// 矩阵与向量的乘法操作符
glm::vec3 operator*(const glm::mat4& matrix, const glm::vec3& vector)
{
	glm::vec4 v = matrix * glm::vec4(vector.x, vector.y, vector.z, 1.f);
	return glm::vec3(v.x, v.y, v.z);
}

// 归一化一个数值
float normalize(float number)
{
	return std::clamp(number, 0.f, 1.f);
}

// 计算一个数字在两个边界之间的比例
float ratio(float number, float min, float max)
{
	return (number - min) / (max - min);
}

// 将一个数字限制在两个值之间
float smooth_clamp(float value, float min, float max, float smoothness)
{
	return (1.f / (1.f + exp(-value / smoothness))) * (max - min) + min;
}
