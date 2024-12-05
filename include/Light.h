#ifndef LIGHT_H
#define LIGHT_H

#include "utils.h"

// �����Դ��

struct Light
{
public:

	// ö�ٶ����Դ����
	enum class Type { Ambient = 0, Directional = 1, Point = 2 };

private:

	Type		type;		// ��Դ����
	glm::vec3	vector;		// ��Դ�ķ����λ��
	Color		color;		// ��Դ����ɫ
	float		intensity;	// ��Դ��ǿ��

public:

	// ���캯��
	Light();
	Light(const Light& other);
	Light(Type type, const glm::vec3& vector, const Color& color = Color(1.f, 1.f, 1.f, 1.f), float intensity = 1.f);

	// ��ֵ�����
	Light& operator=(const Light& other);

	// ��ȡ��Դ����
	Type		get_type() const;
	// ���ù�Դ����
	void		set_type(Type type);

	// ��ȡ��Դ�ķ����λ��
	glm::vec3	get_vector() const;
	// ���ù�Դ�ķ����λ��
	void		set_vector(const glm::vec3& vector);

	// ��ȡ��Դ��ɫ
	Color		get_color() const;
	// ���ù�Դ��ɫ
	void		set_color(const Color& color);

	// ��ȡ��Դǿ��
	float		get_intensity() const;
	// ���ù�Դǿ��
	void		set_intensity(float intensity);
};

#endif
