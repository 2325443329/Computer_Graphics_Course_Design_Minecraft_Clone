#include "Light.h"

// 创建一个光源

Light::Light()
{
	type = Type::Ambient;
	vector = glm::vec3(1.f, 0.f, 0.f);
	color = Color(0.f, 0.f, 0.f, 0.f);
	intensity = 0.f;
}

// 从另一个光源创建一个光源

Light::Light(const Light& other)
{
	*this = other;
}

// 根据属性创建一个光源

Light::Light(Type type, const glm::vec3& vector, const Color& color, float intensity)
{
	set_type(type);
	set_vector(vector);
	set_color(color);
	set_intensity(intensity);
}

// 重载赋值操作符

Light& Light::operator=(const Light& other)
{
	type = other.type;
	vector = other.vector;
	color = other.color;
	intensity = other.intensity;

	return *this;
}

// 获取光源的类型

Light::Type Light::get_type() const
{
	return type;
}

// 设置光源的类型

void Light::set_type(Type type)
{
	this->type = type;
}

// 获取光源的位置或方向

glm::vec3 Light::get_vector() const
{
	return vector;
}

// 设置光源的位置或方向

void Light::set_vector(const glm::vec3& vector)
{
	if (type == Type::Directional)
	{
		// 如果方向向量为零，默认为 (1, 0, 0)
		if (vector == glm::vec3(0.f, 0.f, 0.f))
			this->vector = glm::vec3(1.f, 0.f, 0.f);
		else
			this->vector = glm::normalize(vector); // 归一化方向向量
	}
	else
		this->vector = vector;
}

// 获取光源的颜色

Color Light::get_color() const
{
	return color;
}

// 设置光源的颜色

void Light::set_color(const Color& color)
{
	this->color = color;
	// 根据透明度调整 RGB 值
	this->color.r *= this->color.a;
	this->color.g *= this->color.a;
	this->color.b *= this->color.a;
	this->color.a = 1.f; // 透明度设为 1（不透明）
}

// 获取光源的强度

float Light::get_intensity() const
{
	return intensity;
}

// 设置光源的强度

void Light::set_intensity(float intensity)
{
	this->intensity = std::max(intensity, 0.f); // 确保强度不为负
}
