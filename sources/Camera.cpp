#include "Camera.h"

// 从另一台相机创建相机

Camera::Camera(const Camera& other)
{
	*this = other;
}

// 根据这些属性创建相机

Camera::Camera(const glm::vec3& position, float sensitivity, float fov)
{
	this->position = position;
	this->sensitivity = sensitivity;
	this->fov = fov;

	direction = glm::vec3(0.f, 0.f, -1.f);

	projection = glm::perspective(fov, static_cast<float>(Window::size.x) / static_cast<float>(Window::size.y), 0.1f, 100.f);
	view = glm::lookAt(this->position, this->position + direction, glm::vec3(0.f, 1.f, 0.f));

	yaw = -90.f;
	pitch = 0.f;
}

// 赋值运算符重载

Camera& Camera::operator=(const Camera& other)
{
	position = other.position;
	sensitivity = other.sensitivity;
	fov = other.fov;
	view = other.view;
	projection = other.projection;
	direction = other.direction;
	yaw = other.yaw;
	pitch = other.pitch;

	return *this;
}

// 根据鼠标的移动来改变相机的方向

void Camera::look(const glm::ivec2& mouse_pos)
{
	yaw += (mouse_pos.x - Window::center.x) * sensitivity;
	pitch -= (mouse_pos.y - Window::center.y) * sensitivity;

	if (pitch > 89.f)
		pitch = 89.f;

	if (pitch < -89.f)
		pitch = -89.f;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	view = glm::lookAt(position, position + direction, glm::vec3(0.f, 1.f, 0.f));
}

// 返回相机的矩阵

glm::mat4 Camera::get_matrix() const
{
	// glm::perspective 有bug，不能正确处理 "near" 和 "far" 参数，所以这里手动处理
	return glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f, 0.1)) * projection * view;
}

// 改变相机的位置

void Camera::set_position(const glm::vec3& position)
{
	this->position = position;
	view = glm::lookAt(this->position, this->position + direction, glm::vec3(0.f, 1.f, 0.f));
}

// 返回相机的位置

glm::vec3 Camera::get_position() const
{
	return position;
}

// 返回相机的水平角度

float Camera::get_yaw() const
{
	return yaw;
}

// 返回相机的垂直角度

float Camera::get_pitch() const
{
	return pitch;
}

// 返回相机的方向

glm::vec3 Camera::get_direction() const
{
	return direction;
}

// 根据水平镜面的高度反转相机

void Camera::invert(float mirror_level)
{
	position.y = position.y - 2.f * (position.y - mirror_level);
	pitch = -pitch;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);

	view = glm::lookAt(position, position + direction, glm::vec3(0.f, 1.f, 0.f));
}

// 改变相机的图像分辨率

void Camera::change_resolution(float width, float height)
{
	projection = glm::perspective(fov, width / height, 0.1f, 100.f);
}
