#include "Sky.h"
#include "Luminary.h"
#include "Chunk.h"
#include "Game.h"

glm::mat4 Sky::scale_matrix = glm::scale(glm::mat4(1.f), glm::vec3(distance * 2.f, distance * 2.f, distance * 2.f));

// 创建天空
Sky::Sky()
{
	high_color = Color(0.f, 0.f, 0.f, 1.f);
	low_color = Color(0.f, 0.f, 0.f, 1.f);
	model = glm::mat4(1.f);
}

// 从另一个天空对象创建天空
Sky::Sky(const Sky& other)
{
	*this = other;
}

// 初始化天空
void Sky::init()
{
	light = Light(Light::Type::Ambient, glm::vec3(), high_color, 1.f);

	scale_matrix = glm::scale(glm::mat4(1.f), glm::vec3(distance * 2.f, distance * 2.f, distance * 2.f));
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, Chunk::height + 3.f, 0.f));
	model = translation_matrix * scale_matrix;

	object.send_data(Shader::sky, Mesh::sphere_64, DataType::Positions);
}

// 赋值运算符
Sky& Sky::operator=(const Sky& other)
{
	high_color = other.high_color;
	low_color = other.low_color;
	light = other.light;
	model = other.model;
	object = other.object;

	return *this;
}

// 更新天空
void Sky::update(const glm::vec3& player_pos, float sun_height)
{
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.f), player_pos);
	model = translation_matrix * scale_matrix;

	const float max_intensity = distance / 2.f;
	const float min_intensity = -distance / 4.f;

	float intensity = std::clamp(ratio(sun_height, min_intensity, max_intensity), 0.1f, 1.f);

	high_color.r = 0.f * intensity;
	high_color.g = 0.3f * intensity;
	high_color.b = 1.f * intensity;

	low_color.r = 0.2f * intensity;
	low_color.g = 0.8f * intensity;
	low_color.b = 1.f * intensity;

	light.set_color(low_color);
	light.set_intensity(intensity);
}

// 绘制天空
void Sky::draw(const Camera& camera, const std::vector<const Light*>& lights) const
{
	glFrontFace(GL_CW);
	Shader::sky.bind();
	object.bind();

	object.send_uniform("u_model", model);
	object.send_uniform("u_mvp", camera.get_matrix() * model);
	object.send_uniform("u_high_color", high_color);
	object.send_uniform("u_low_color", low_color);
	object.send_uniform("u_camera", camera.get_position());
	object.send_uniform("u_water_level", water_level);
	object.send_uniform("u_fake_cam", (int)Game::fake_cam);

	ColorRGB water_color = ColorRGB(0.f, 0.f, 0.f);

	for (uint16_t i = 0; i < std::min((int)lights.size(), (int)nb_max_lights); i++)
		water_color += ColorRGB(Material::water.get_color()) * ColorRGB(lights[i]->get_color()) * lights[i]->get_intensity();

	object.send_uniform("u_water_color", water_color);

	object.draw();

	VertexBuffer::unbind();
	Shader::unbind();
	glFrontFace(GL_CCW);
}

// 获取天空光源的指针
const Light* Sky::get_light() const
{
	return &light;
}
