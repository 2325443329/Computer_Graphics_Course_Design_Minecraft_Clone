#include "utils.h"
#include "Shader.h"

std::mutex		lock;

SDL_Window* Window::window = NULL;
SDL_GLContext	Window::context = NULL;
glm::ivec2		Window::size = glm::ivec2(10, 10);
glm::ivec2		Window::center = glm::ivec2(5, 5);

// ��ʼ������
bool Window::init()
{
	// ��ʼ��SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		SHADER_ERROR("SDL��ʼ��ʧ��: %s\n", SDL_GetError());
		return false;
	}

	SDL_DisplayMode screen;
	SDL_GetCurrentDisplayMode(0, &screen);

	size.x = screen.w * (3.f / 4.f);
	size.y = screen.h * (3.f / 4.f);
	center.x = size.x / 2;
	center.y = size.y / 2;

	// ��������
	window = SDL_CreateWindow("Minecraft clone",	// ����
		SDL_WINDOWPOS_UNDEFINED,					// X λ��
		SDL_WINDOWPOS_UNDEFINED,					// Y λ��
		size.x, size.y,								// �ֱ���
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);		// ��־��OpenGL + ��ʾ��

	// ��ʼ��OpenGL�汾���汾3.0��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// ��ʼ��OpenGL�����ģ�OpenGL��Դ�Ĵ洢λ�ã�
	context = SDL_GL_CreateContext(window);

	// ����GLEW��ʼ���˰汾��OpenGL����
	glewExperimental = GL_TRUE;
	glewInit();

	// ��ʼʹ��OpenGL��������
	glViewport(0, 0, size.x, size.y); // ����������Ļ

	// ����OpenGL������ɫ��RGBA��ÿ�������ֵ��0.f��1.f֮�䣩
	glClearColor(0.f, 0.f, 0.f, 1.f);

	glEnable(GL_DEPTH_TEST); // ������Ȳ���
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���òü�ƽ��
	glEnable(GL_CLIP_DISTANCE0);

	// �������޳�������ʾ������ȷ����
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	return true;
}

// ���ٴ���
void Window::clear()
{
	if (context != NULL)
		SDL_GL_DeleteContext(Window::context);

	if (window != NULL)
		SDL_DestroyWindow(Window::window);
}

// ����������ת��Ϊ��������
glm::ivec3 round(const glm::vec3& vector)
{
	return glm::ivec3(std::round(vector.x), std::round(vector.y), std::round(vector.z));
}

// ����һ����min��max֮����������
int32_t random_int(int32_t min, int32_t max)
{
	return (rand() % (max - min)) + min;
}

// ����һ����min��max֮������������
float random_float(float min, float max)
{
	return (rand() / static_cast<float>(RAND_MAX)) * (max - min) + min;
}

// �������ʷ�����
bool rand_probability(float probability)
{
	if (probability < 0.f)
		return false;

	if (probability < 1.f)
		return (rand() / static_cast<float>(RAND_MAX) < probability);

	return true;
}

// ����������ˮƽ����
float get_horizontal_norm(const glm::vec3& vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.z, 2));
}

// �޸�������ˮƽ����
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

// �����������ĳ˷�������
glm::vec3 operator*(const glm::mat4& matrix, const glm::vec3& vector)
{
	glm::vec4 v = matrix * glm::vec4(vector.x, vector.y, vector.z, 1.f);
	return glm::vec3(v.x, v.y, v.z);
}

// ��һ��һ����ֵ
float normalize(float number)
{
	return std::clamp(number, 0.f, 1.f);
}

// ����һ�������������߽�֮��ı���
float ratio(float number, float min, float max)
{
	return (number - min) / (max - min);
}

// ��һ����������������ֵ֮��
float smooth_clamp(float value, float min, float max, float smoothness)
{
	return (1.f / (1.f + exp(-value / smoothness))) * (max - min) + min;
}
