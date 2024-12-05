#ifndef SKIN_H
#define SKIN_H

#include "utils.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Mesh.h"
#include "VertexBuffer.h"

class Player;

// 定义玩家的3D模型

class Skin
{
public:

	// 以下是与步态和动画相关的常量
	static constexpr float max_walk_strength = 0.7f;						// 最大步幅
	static constexpr float strength_step = max_walk_strength / 10.f;	// 达到最大步幅的速度
	static constexpr float walk_anim_speed = 0.2f;						// 步伐动画的速度
	static constexpr float turn_speed = 0.1f;						// 旋转动画的速度
	static constexpr float max_head_rotation = pi / 4.f;					// 头部旋转的最大角度
	static constexpr float texture_size = 64.f;						// 皮肤纹理的大小

	// 定义模型的各个部件（例如手臂、肩膀、腿部等）

	class Part
	{
	private:

		VertexBuffer				object;				// OpenGL的顶点缓冲区
		glm::mat4					propagated_matrix;	// 传播矩阵
		glm::mat4					local_matrix;		// 本地矩阵
		std::vector<Part*>			children;			// 子部件

	public:

		Part();						// 构造函数
		Part(const Part& other);		// 拷贝构造函数
		Part(Mesh mesh, const glm::vec2& texture_pos, const glm::vec3& size, const std::vector<Part*>& children);

		Part& operator=(const Part& other);		// 赋值操作符

		// 绘制部件的函数
		void						draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;

		// 初始化纹理坐标
		static std::vector<float>	init_texcoords(const glm::vec2& texture_pos, const glm::vec3& size);

		friend						Skin;
		friend						Player;
	};

private:

	// 定义模型的各个部件
	Part		arm_1;				// 左臂
	Part		shoulder_1;			// 左肩
	Part		arm_2;				// 右臂
	Part		shoulder_2;			// 右肩
	Part		leg_1;				// 左腿
	Part		hips_1;				// 左髋部
	Part		leg_2;				// 右腿
	Part		hips_2;				// 右髋部
	Part		camera;				// 摄像机
	Part		head;				// 头部
	Part		neck;				// 脖部
	Part		body;				// 身体

	// 与行走和动画相关的状态
	bool		walking;			// 是否正在走
	bool		running;			// 是否正在跑
	bool		forward;			// 是否朝前
	bool		left;				// 是否朝左
	bool		right;				// 是否朝右
	bool		back;				// 是否朝后
	uint32_t	animation_i;		// 当前动画状态
	float		walk_strength;		// 步伐的大小
	glm::mat4	shoulder_1_initial;	// 左肩的初始矩阵
	glm::mat4	shoulder_2_initial;	// 右肩的初始矩阵
	glm::mat4	hips_1_initial;		// 左髋部的初始矩阵
	glm::mat4	hips_2_initial;		// 右髋部的初始矩阵
	glm::mat4	neck_initial;		// 脖部的初始矩阵
	float		body_angle;			// 身体的角度
	float		head_angle;			// 头部的角度

	int current_skin_index = 0;  // 当前皮肤的索引

public:

	// 构造函数和拷贝构造函数
	Skin();
	Skin(const Skin& other);
	Skin(const glm::vec3& position, const glm::vec3& direction);

	// 赋值操作符
	Skin& operator=(const Skin& other);

	// 移动和旋转相关的函数
	void		move(const glm::vec3& position);
	void		rotate(float angle);
	void		rotate_head(float yaw, float pitch);

	// 更新行走动画
	void		update_walk();

	// 切换到下一个皮肤
	void		switch_skin(bool next);

	// 绘制整个模型
	void		draw(const Camera& camera, const std::vector<const Light*>& lights, const Plane& clipping_plane = Plane(0.f, 1.f, 0.f, 10000.f)) const;

	friend		Player;
};

#endif
