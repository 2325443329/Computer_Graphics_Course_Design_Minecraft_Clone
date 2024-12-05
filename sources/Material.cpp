#include "Material.h"

Material Material::block = Material(Color(), 0.2f, 0.6f, 0.f, 1.f);
Material Material::entity = Material(Color(), 0.2f, 0.6f, 0.4f, 100.f);
Material Material::water = Material(Color(0.f, 0.2f, 0.8f, 1.f), 0.4f, 0.4f, 0.4f, 500.f);

// 创建一个材质

Material::Material()
{
	color = Color(0.f, 0.f, 0.f, 0.f);
	ambient = 0.f;
	diffuse = 0.f;
	specular = 0.f;
	shininess = 0.f;
}

// 从另一个材质创建一个新的材质

Material::Material(const Material& other)
{
	*this = other;
}

// 从给定的属性创建一个材质

Material::Material(const Color& color, float ambient, float diffuse, float specular, float shininess)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

// 赋值操作符重载

Material& Material::operator=(const Material& other)
{
	color = other.color;
	ambient = other.ambient;
	diffuse = other.diffuse;
	specular = other.specular;
	shininess = other.shininess;

	return *this;
}

// 获取颜色

Color Material::get_color() const
{
	return color;
}

// 设置颜色

void Material::set_color(const Color& color)
{
	this->color = color;
}

// 获取环境光强度

float Material::get_ambient() const
{
	return ambient;
}

// 设置环境光强度

void Material::set_ambient(float ambient)
{
	this->ambient = normalize(ambient);
}

// 获取漫反射光强度

float Material::get_diffuse() const
{
	return diffuse;
}

// 设置漫反射光强度

void Material::set_diffuse(float diffuse)
{
	this->diffuse = normalize(diffuse);
}

// 获取高光反射光强度

float Material::get_specular() const
{
	return specular;
}

// 设置高光反射光强度

void Material::set_specular(float specular)
{
	this->specular = normalize(specular);
}

// 获取光泽度（反射的锐度）

float Material::get_shininess() const
{
	return shininess;
}

// 设置光泽度（反射的锐度）

void Material::set_shininess(float shininess)
{
	this->shininess = std::max(shininess, 0.f);
}
