#ifndef UTILS_H
#define UTILS_H

#include "libraries.h"

// ��������
constexpr float						pi = 3.14159265359f;			// Բ���� (Pi)
constexpr float						framerate = 60.f;						// ���֡�� (ÿ�����֡��)
constexpr float						frame_duration = 1.f / framerate;			// ÿ֡����Сʱ��
constexpr float						frame_duration_ms = 1.f / framerate * 1e3;	// ÿ֡��ʱ������λ������
constexpr float						epsilon = 0.01f;					// һ����С�ĳ���ֵ
constexpr float						epsilon_2 = 0.005f;					// һ����С�ĳ���ֵ

// ����һ��λ�ã�����Χ��ĳ������ĸ�����
constexpr std::array<glm::ivec3, 4>	around_positions = { glm::ivec3(-1, 0, 0), glm::ivec3(1, 0, 0), glm::ivec3(0, 0, -1), glm::ivec3(0, 0, 1) };

// ���ͱ���
typedef glm::vec4 Color;	// ������ɫ���ͣ�����͸����
typedef glm::vec3 ColorRGB;	// ����RGB��ɫ���ͣ�������͸����
typedef glm::vec4 Plane;	// ����ƽ������

// �ⲿ������������
extern std::mutex lock;

// ����һ�����ڽṹ�壬�������ڵ����ԺͲ���
struct Window
{
	static SDL_Window* window;		// ���ڶ���
	static SDL_GLContext	context;	// OpenGL������
	static glm::ivec2		size;		// ���ڴ�С
	static glm::ivec2		center;		// ��������λ��

	// ���ڳ�ʼ������
	static bool				init();

	// �������
	static void				clear();
};

// ��������

// ��3D���������������봦��
glm::ivec3	round(const glm::vec3& vector);

// ����ָ����Χ�ڵ��������
int32_t		random_int(int32_t min, int32_t max);

// ����ָ����Χ�ڵ����������
float		random_float(float min, float max);

// ����ָ���ĸ��ʷ����������ֵ
bool		rand_probability(float probability);

// ��ȡ3D������ˮƽ����
float		get_horizontal_norm(const glm::vec3& vector);

// ����3D������ˮƽ����
void		set_horizontal_norm(glm::vec3& vector, float value);

// �����������ĳ˷�����
glm::vec3	operator*(const glm::mat4& matrix, const glm::vec3& vector);

// ��һ��һ������ֵ��[0, 1]����
float		normalize(float number);

// ��һ��ֵӳ�䵽ָ������С���Χ��
float		ratio(float number, float min, float max);

// ��һ��ֵ����ƽ�������ƣ����Ʒ�Χ�ڵ�ƽ������
float		smooth_clamp(float value, float min, float max, float smoothness);

#endif
