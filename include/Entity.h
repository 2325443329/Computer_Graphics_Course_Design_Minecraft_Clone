#ifndef ENTITY_H
#define ENTITY_H

#include "utils.h"
#include "Camera.h"
#include "World.h"
#include "Block.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "Texture.h"

// ����һ��ʵ����
class Entity
{
public:

	static constexpr float		jump_speed = 9.f;	// ��Ծ�ٶ�
	static constexpr float		walk_speed = 4.5f;	// �����ٶ�
	static constexpr float		texture_size = 64.f;	// Ƥ���������С

	// ����ģ�͵�һ������
	class Part
	{
	private:

		VertexBuffer				object;				// OpenGL ���㻺����

	public:

		glm::mat4					propagated_matrix;	// ��������
		glm::mat4					local_matrix;		// ���ؾ���
		std::vector<Part*>			children;			// ���ӵĲ���

		Part();
		Part(const Part& other);
		Part(Mesh mesh, const glm::vec2& texture_pos, const glm::vec3& size, const std::vector<Part*>& children, bool horizontal);

		Part& operator=(const Part& other);

		void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;

		static std::vector<float>	init_texcoords(const glm::vec2& texture_pos, const glm::vec3& size, bool horizontal);
	};

protected:

	float						y_offset;				// ʵ�����ײ������������ y ��ƫ��
	Part						body;					// ����
	Part						neck;					// ����
	std::array<glm::vec3, 12>	hitbox;					// ʵ�����ײ��	
	glm::vec3					previous_pos;			// ��һλ��
	glm::vec3					position;				// ʵ���λ��	
	glm::vec3					speed;					// ʵ����ٶ�	
	bool						in_air;					// �Ƿ��ڿ���
	Chunk* chunk;					// ʵ�����ڵĿ�
	Texture* texture;				// ʵ�������
	bool						is_blocked;				// �Ƿ����������巢����ײ
	bool						walking;				// �Ƿ���������
	glm::mat4					body_initial;			// ����ĳ�ʼ����
	glm::mat4					neck_initial;			// ���ӵĳ�ʼ����
	float						body_angle;				// �������ת�Ƕ�
	float						head_angle;				// ͷ������ת�Ƕ�

public:

	Entity();
	Entity(const Entity& other);
	virtual						~Entity() = 0;

	virtual Entity& operator=(const Entity& other);

	void						move(const glm::vec3& position);	// �ƶ�ʵ��
	void						rotate(float angle);	// ��תʵ��
	glm::vec3					get_position() const;	// ��ȡʵ��λ��
	Chunk* get_chunk() const;		// ��ȡʵ�����ڵĿ�
	void						jump();					// ��ʵ����Ծ
	void						update_position();		// ����ʵ��λ��
	void						update_rotation();		// ����ʵ����ת
	void						find_entity_chunk(const World& world);	// ����ʵ�����ڵĿ�
	void						check_hitbox(const World& world, const glm::vec3& player_pos);	// �����ײ��
	virtual void				update(const World& world, const glm::vec3& player_pos);	// ����ʵ��
	void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;	// ����ʵ��
};

#endif
