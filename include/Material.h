#ifndef MATERIAL_H
#define MATERIAL_H

#include "utils.h"

// ���������

class Material
{
private:

	Color			color;		// ���ʵ���ɫ
	float			ambient;	// �������ǿ��
	float			diffuse;	// ��������ǿ��
	float			specular;	// �߹ⷴ���ǿ��
	float			shininess;	// ����ȣ����Ʒ���������̶ȣ�

public:

	// ��̬����ʵ��������ʡ�ʵ����ʡ�ˮ����
	static Material	block;		// ��Ĳ���
	static Material	entity;		// ʵ��Ĳ���
	static Material	water;		// ˮ�Ĳ���

	// Ĭ�Ϲ��캯��
	Material();
	Material(const Material& other);
	Material(const Color& color, float ambient, float diffuse, float specular, float shininess);

	// ��ֵ�����
	Material& operator=(const Material& other);

	// ��ȡ�����ò��ʵĸ�������
	Color			get_color() const;
	void			set_color(const Color& color);
	float			get_ambient() const;
	void			set_ambient(float ambient);
	float			get_diffuse() const;
	void			set_diffuse(float diffuse);
	float			get_specular() const;
	void			set_specular(float specular);
	float			get_shininess() const;
	void			set_shininess(float shininess);
};

#endif
