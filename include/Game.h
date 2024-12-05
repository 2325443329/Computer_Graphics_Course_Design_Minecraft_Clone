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

constexpr float reflection_quality = 0.5f;	// 反射质量（从0到1）

// 定义游戏类

class Game
{
public:

	static World					world;			// 世界
	static Sun						sun;			// 太阳
	static Moon						moon;			// 月亮
	static Sky						sky;			// 天空
	static std::stack<glm::mat4>	matrices;		// 矩阵堆栈
	static Player					player;			// 玩家
	static Camera					fixed_cam;		// 玩家固定的摄像机
	static bool						fix_cam;		// 摄像机是否固定
	static bool						fake_cam;		// 是否使用虚拟摄像机
	static bool						in_water;		// 摄像机是否在水下
	static bool						stop_moving;	// 是否停止移动摄像机
	static bool						debug;			// 是否显示调试信息
	static float					time;			// 游戏时间

	static void						init();			// 初始化
	static void						checks_events(const SDL_Event& my_event);	// 事件检查
	static void						update(glm::ivec2& mouse_pos);	// 更新游戏状态
	static void						draw();			// 渲染游戏画面
};

#endif
