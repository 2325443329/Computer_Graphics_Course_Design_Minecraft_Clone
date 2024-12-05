#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "Camera.h"
#include "World.h"
#include "Chunk.h"
#include "Block.h"
#include "Skin.h"
#include "Material.h"
#include "Light.h"

// ����һ�������

class Player // : Entity :(
{
public:

	// ����������ҵĸ�������
	static constexpr float		jump_speed = 9.f;	// ��Ծ�ٶ�
	static constexpr float		walk_speed = 7.f;	// �����ٶ�
	static constexpr float		run_speed = 10.f;	// �ܲ��ٶ�
	static constexpr float		fly_speed = 25.f;	// �����ٶ�
	static constexpr float		break_distance = 10.f;	// �ݻ�һ�������������
	static constexpr float		place_distance = 10.f;	// ����һ�������������

private:

	Skin						skin;					// ���ģ�ͣ�3D��
	glm::vec3					previous_pos;			// ���֮ǰ��λ��
	glm::vec3					position;				// ��ҵ�ǰλ��
	std::array<glm::vec3, 12>	hitbox;					// �����ײ��
	glm::vec3					speed;					// ����ٶ�
	bool						in_air;					// ����Ƿ��ڿ���
	Chunk* chunk;					// ������ڵ�����

public:

	Camera						camera;					// ��������
	bool						fly;					// �Ƿ����÷���ģʽ
	bool						first_person;			// �Ƿ�Ϊ��һ�˳��ӽ�

	int block_type = 0;					// ���ѡ��ķ�������

	Player();
	Player(const Player& other);
	Player(const glm::vec3& position);

	Player& operator=(const Player& other);

	// ��ȡ���λ��
	glm::vec3					get_position() const;

	// ����Ҹ������λ����ת�ӽ�
	void						look(const glm::ivec2& mouse_pos);

	// �������ͷ����λ��
	void						update_head();

	// ����Ҹ��ݼ��������ƶ�
	void						move(const Uint8* keystates, World& world);

	// �����Ծ
	void						jump();

	// ������ҵ�λ����Ϣ
	void						update_position();

	// ����������ڵ�����
	void						find_player_chunk(World& world);

	// �����ҵ���ײ���Ƿ��뻷����ײ
	void						check_hitbox(World& world);

	// ��Ҵݻٷ���
	void						break_block();

	// ��ҷ��÷���
	void                        place_block();

	// ���� Skin �� switch_skin ����
	void						switch_skin(bool next);

	// �������
	void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;
};

#endif
