#include "Material.h"

Material Material::block = Material(Color(), 0.2f, 0.6f, 0.f, 1.f);
Material Material::entity = Material(Color(), 0.2f, 0.6f, 0.4f, 100.f);
Material Material::water = Material(Color(0.f, 0.2f, 0.8f, 1.f), 0.4f, 0.4f, 0.4f, 500.f);

// ����һ������

Material::Material()
{
	color = Color(0.f, 0.f, 0.f, 0.f);
	ambient = 0.f;
	diffuse = 0.f;
	specular = 0.f;
	shininess = 0.f;
}

// ����һ�����ʴ���һ���µĲ���

Material::Material(const Material& other)
{
	*this = other;
}

// �Ӹ��������Դ���һ������

Material::Material(const Color& color, float ambient, float diffuse, float specular, float shininess)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

// ��ֵ����������

Material& Material::operator=(const Material& other)
{
	color = other.color;
	ambient = other.ambient;
	diffuse = other.diffuse;
	specular = other.specular;
	shininess = other.shininess;

	return *this;
}

// ��ȡ��ɫ

Color Material::get_color() const
{
	return color;
}

// ������ɫ

void Material::set_color(const Color& color)
{
	this->color = color;
}

// ��ȡ������ǿ��

float Material::get_ambient() const
{
	return ambient;
}

// ���û�����ǿ��

void Material::set_ambient(float ambient)
{
	this->ambient = normalize(ambient);
}

// ��ȡ�������ǿ��

float Material::get_diffuse() const
{
	return diffuse;
}

// �����������ǿ��

void Material::set_diffuse(float diffuse)
{
	this->diffuse = normalize(diffuse);
}

// ��ȡ�߹ⷴ���ǿ��

float Material::get_specular() const
{
	return specular;
}

// ���ø߹ⷴ���ǿ��

void Material::set_specular(float specular)
{
	this->specular = normalize(specular);
}

// ��ȡ����ȣ��������ȣ�

float Material::get_shininess() const
{
	return shininess;
}

// ���ù���ȣ��������ȣ�

void Material::set_shininess(float shininess)
{
	this->shininess = std::max(shininess, 0.f);
}
