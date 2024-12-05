#include "Light.h"

// ����һ����Դ

Light::Light()
{
	type = Type::Ambient;
	vector = glm::vec3(1.f, 0.f, 0.f);
	color = Color(0.f, 0.f, 0.f, 0.f);
	intensity = 0.f;
}

// ����һ����Դ����һ����Դ

Light::Light(const Light& other)
{
	*this = other;
}

// �������Դ���һ����Դ

Light::Light(Type type, const glm::vec3& vector, const Color& color, float intensity)
{
	set_type(type);
	set_vector(vector);
	set_color(color);
	set_intensity(intensity);
}

// ���ظ�ֵ������

Light& Light::operator=(const Light& other)
{
	type = other.type;
	vector = other.vector;
	color = other.color;
	intensity = other.intensity;

	return *this;
}

// ��ȡ��Դ������

Light::Type Light::get_type() const
{
	return type;
}

// ���ù�Դ������

void Light::set_type(Type type)
{
	this->type = type;
}

// ��ȡ��Դ��λ�û���

glm::vec3 Light::get_vector() const
{
	return vector;
}

// ���ù�Դ��λ�û���

void Light::set_vector(const glm::vec3& vector)
{
	if (type == Type::Directional)
	{
		// �����������Ϊ�㣬Ĭ��Ϊ (1, 0, 0)
		if (vector == glm::vec3(0.f, 0.f, 0.f))
			this->vector = glm::vec3(1.f, 0.f, 0.f);
		else
			this->vector = glm::normalize(vector); // ��һ����������
	}
	else
		this->vector = vector;
}

// ��ȡ��Դ����ɫ

Color Light::get_color() const
{
	return color;
}

// ���ù�Դ����ɫ

void Light::set_color(const Color& color)
{
	this->color = color;
	// ����͸���ȵ��� RGB ֵ
	this->color.r *= this->color.a;
	this->color.g *= this->color.a;
	this->color.b *= this->color.a;
	this->color.a = 1.f; // ͸������Ϊ 1����͸����
}

// ��ȡ��Դ��ǿ��

float Light::get_intensity() const
{
	return intensity;
}

// ���ù�Դ��ǿ��

void Light::set_intensity(float intensity)
{
	this->intensity = std::max(intensity, 0.f); // ȷ��ǿ�Ȳ�Ϊ��
}
