#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

// ����һ�������

class Camera
{
private:

	glm::vec3				position;					// �����λ��
	float					sensitivity;				// ���������
	float					fov;						// �ӳ���
	glm::mat4				view;						// ��ͼ����
	glm::mat4				projection;					// ͶӰ����
	glm::vec3				direction;					// ����ķ���
	float					yaw;						// ˮƽ��ת�Ƕ�
	float					pitch;						// ��ֱ��ת�Ƕ�

public:

	static constexpr float	default_fov = pi / 4.f;		// Ĭ���ӳ���
	static constexpr float	default_sensitivity = 0.2f;	// Ĭ�����������

	Camera(const Camera& other);
	Camera(const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f), float sensitivity = default_sensitivity, float fov = default_fov);

	Camera& operator=(const Camera& other);

	void					look(const glm::ivec2& mouse_pos);						// ͨ�����λ�õ���������ӽ�
	glm::mat4				get_matrix() const;										// ��ȡ����ľ�����ͼ + ͶӰ��
	void					set_position(const glm::vec3& position);				// ���������λ��
	glm::vec3				get_position() const;									// ��ȡ�����λ��
	float					get_yaw() const;											// ��ȡ�����ˮƽ��ת�Ƕ�
	float					get_pitch() const;										// ��ȡ����Ĵ�ֱ��ת�Ƕ�
	glm::vec3				get_direction() const;									// ��ȡ����ķ���
	void					invert(float mirror_level);								// ��ת����ķ���
	void					change_resolution(float width, float height);			// �ı�ֱ��ʣ���Ⱥ͸߶ȣ�
};

#endif
