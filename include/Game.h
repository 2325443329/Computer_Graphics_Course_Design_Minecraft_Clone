#ifndef GAME_H
#define GAME_H

#include "utils.h"
#include "Shader.h"
#include "Block.h"
#include "Chunk.h"
#include "utils.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Luminary.h"
#include "Sun.h"
#include "Moon.h"
#include "Sky.h"
#include "Texture.h"
#include "Shader.h"
#include "FrameBuffer.h"

constexpr float reflection_quality = 0.5f;	// ������������0��1��

// ������Ϸ��

class Game
{
public:

	static World					world;			// ����
	static Sun						sun;			// ̫��
	static Moon						moon;			// ����
	static Sky						sky;			// ���
	static std::stack<glm::mat4>	matrices;		// �����ջ
	static Player					player;			// ���
	static Camera					fixed_cam;		// ��ҹ̶��������
	static bool						fix_cam;		// ������Ƿ�̶�
	static bool						fake_cam;		// �Ƿ�ʹ�����������
	static bool						in_water;		// ������Ƿ���ˮ��
	static bool						stop_moving;	// �Ƿ�ֹͣ�ƶ������
	static bool						debug;			// �Ƿ���ʾ������Ϣ
	static float					time;			// ��Ϸʱ��

	static void						init();			// ��ʼ��
	static void						checks_events(const SDL_Event& my_event);	// �¼����
	static void						update(glm::ivec2& mouse_pos);	// ������Ϸ״̬
	static void						draw();			// ��Ⱦ��Ϸ����
};

#endif
