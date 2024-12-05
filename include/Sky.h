#ifndef SKY_H
#define SKY_H

#include "utils.h"
#include "Light.h"
#include "Material.h"
#include "Camera.h"
#include "VertexBuffer.h"

// ���������

class Sky
{
private:

	// ��յ���ɫ����
	Color					high_color;			// ��ն�������ɫ
	Color					low_color;			// ��յײ�����ɫ
	Light					light;				// ��յĻ�����
	glm::mat4				model;				// �任����
	VertexBuffer			object;				// OpenGL ���㻺����

	// ��̬�����ž���
	static glm::mat4		scale_matrix;		// ���ž���

public:

	// ��յĿ��Ӿ��볣��
	static constexpr float	distance = 550.f;	// ��յľ���

	// ���캯�����������캯���͸�ֵ������
	Sky();
	Sky(const Sky& other);
	Sky& operator=(const Sky& other);

	// ��ʼ�������ºͻ������
	void					init();
	void					update(const glm::vec3& player_pos, float sun_height);
	void					draw(const Camera& camera, const std::vector<const Light*>& lights) const;

	// ��ȡ��յĹ�Դ
	const Light* get_light() const;
};

#endif
