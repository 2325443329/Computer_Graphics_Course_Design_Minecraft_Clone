#ifndef SKIN_H
#define SKIN_H

#include "utils.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Mesh.h"
#include "VertexBuffer.h"

class Player;

// ������ҵ�3Dģ��

class Skin
{
public:

	// �������벽̬�Ͷ�����صĳ���
	static constexpr float max_walk_strength = 0.7f;						// ��󲽷�
	static constexpr float strength_step = max_walk_strength / 10.f;	// �ﵽ��󲽷����ٶ�
	static constexpr float walk_anim_speed = 0.2f;						// �����������ٶ�
	static constexpr float turn_speed = 0.1f;						// ��ת�������ٶ�
	static constexpr float max_head_rotation = pi / 4.f;					// ͷ����ת�����Ƕ�
	static constexpr float texture_size = 64.f;						// Ƥ������Ĵ�С

	// ����ģ�͵ĸ��������������ֱۡ�����Ȳ��ȣ�

	class Part
	{
	private:

		VertexBuffer				object;				// OpenGL�Ķ��㻺����
		glm::mat4					propagated_matrix;	// ��������
		glm::mat4					local_matrix;		// ���ؾ���
		std::vector<Part*>			children;			// �Ӳ���

	public:

		Part();						// ���캯��
		Part(const Part& other);		// �������캯��
		Part(Mesh mesh, const glm::vec2& texture_pos, const glm::vec3& size, const std::vector<Part*>& children);

		Part& operator=(const Part& other);		// ��ֵ������

		// ���Ʋ����ĺ���
		void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;

		// ��ʼ����������
		static std::vector<float>	init_texcoords(const glm::vec2& texture_pos, const glm::vec3& size);

		friend						Skin;
		friend						Player;
	};

private:

	// ����ģ�͵ĸ�������
	Part		arm_1;				// ���
	Part		shoulder_1;			// ���
	Part		arm_2;				// �ұ�
	Part		shoulder_2;			// �Ҽ�
	Part		leg_1;				// ����
	Part		hips_1;				// ���Ų�
	Part		leg_2;				// ����
	Part		hips_2;				// ���Ų�
	Part		camera;				// �����
	Part		head;				// ͷ��
	Part		neck;				// ����
	Part		body;				// ����

	// �����ߺͶ�����ص�״̬
	bool		walking;			// �Ƿ�������
	bool		running;			// �Ƿ�������
	bool		forward;			// �Ƿ�ǰ
	bool		left;				// �Ƿ���
	bool		right;				// �Ƿ���
	bool		back;				// �Ƿ񳯺�
	uint32_t	animation_i;		// ��ǰ����״̬
	float		walk_strength;		// �����Ĵ�С
	glm::mat4	shoulder_1_initial;	// ���ĳ�ʼ����
	glm::mat4	shoulder_2_initial;	// �Ҽ�ĳ�ʼ����
	glm::mat4	hips_1_initial;		// ���Ų��ĳ�ʼ����
	glm::mat4	hips_2_initial;		// ���Ų��ĳ�ʼ����
	glm::mat4	neck_initial;		// �����ĳ�ʼ����
	float		body_angle;			// ����ĽǶ�
	float		head_angle;			// ͷ���ĽǶ�

	int current_skin_index = 0;  // ��ǰƤ��������

public:

	// ���캯���Ϳ������캯��
	Skin();
	Skin(const Skin& other);
	Skin(const glm::vec3& position, const glm::vec3& direction);

	// ��ֵ������
	Skin& operator=(const Skin& other);

	// �ƶ�����ת��صĺ���
	void		move(const glm::vec3& position);
	void		rotate(float angle);
	void		rotate_head(float yaw, float pitch);

	// �������߶���
	void		update_walk();

	// �л�����һ��Ƥ��
	void		switch_skin(bool next);

	// ��������ģ��
	void		draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;

	friend		Player;
};

#endif
