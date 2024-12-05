#ifndef LUMINARY_H
#define LUMINARY_H

#include "utils.h"
#include "Light.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "Camera.h"

// ����������

class Luminary
{
protected:

	Texture* texture;				// ���������
	Light					light;					// ����Ĺ�Դ
	glm::mat4				model;					// ����ı任����
	VertexBuffer			object;					// OpenGL�Ķ��㻺��

	// ��̬�����������š�ƽ�ƺ���ת����
	static const glm::mat4	scale_matrix;			// ���ž���
	static const glm::mat4	translation_matrix;		// ƽ�ƾ���
	static const glm::mat4	rotation_matrix;		// ��ת����

public:

	// ����ĳ����������Ƕȡ��ٶȡ���С���������ʼʱ��
	static constexpr float	angle = pi / 6.f;	// �������б�Ƕ�
	static constexpr float	speed = 0.01f;	// ������˶��ٶ�
	static constexpr float	size = 30.f;		// ����Ĵ�С
	static constexpr float	distance = 500.f;	// ������۲��ߵľ���
	static constexpr float	start_time = pi / 4.f;	// �������ʼʱ��

	// Ĭ�Ϲ��캯��
	Luminary();
	Luminary(const Luminary& other);

	// ��ֵ�����
	Luminary& operator=(const Luminary& other);

	// ��ʼ������
	virtual void			init();
	// ���º�������������ʵ��
	virtual void			update(const glm::vec3& player_pos) = 0;
	// ���ƺ���
	void					draw(const Camera& camera, const std::vector<const Light*>& lights) const;
	// ��ȡ�����λ��
	glm::vec3				get_position() const;
	// ��ȡ��Դ
	const Light* get_light() const;
};

#endif
