#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

// 定义一个相机类

class Camera
{
private:

	glm::vec3				position;					// 相机的位置
	float					sensitivity;				// 鼠标灵敏度
	float					fov;						// 视场角
	glm::mat4				view;						// 视图矩阵
	glm::mat4				projection;					// 投影矩阵
	glm::vec3				direction;					// 相机的方向
	float					yaw;						// 水平旋转角度
	float					pitch;						// 垂直旋转角度

public:

	static constexpr float	default_fov = pi / 4.f;		// 默认视场角
	static constexpr float	default_sensitivity = 0.2f;	// 默认鼠标灵敏度

	Camera(const Camera& other);
	Camera(const glm::vec3& position = glm::vec3(0.f, 0.f, 0.f), float sensitivity = default_sensitivity, float fov = default_fov);

	Camera& operator=(const Camera& other);

	void					look(const glm::ivec2& mouse_pos);						// 通过鼠标位置调整相机的视角
	glm::mat4				get_matrix() const;										// 获取相机的矩阵（视图 + 投影）
	void					set_position(const glm::vec3& position);				// 设置相机的位置
	glm::vec3				get_position() const;									// 获取相机的位置
	float					get_yaw() const;											// 获取相机的水平旋转角度
	float					get_pitch() const;										// 获取相机的垂直旋转角度
	glm::vec3				get_direction() const;									// 获取相机的方向
	void					invert(float mirror_level);								// 反转相机的方向
	void					change_resolution(float width, float height);			// 改变分辨率（宽度和高度）
};

#endif
