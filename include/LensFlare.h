#ifndef LENSFLARE_H
#define LENSFLARE_H

#include "utils.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Camera.h"

// 定义一个镜头光晕类

class LensFlare
{
public:

	static constexpr uint8_t				nb_shapes = 9;		// 形状数量
	static constexpr float					size = 2.5f;		// 形状的大小
	static constexpr float				 spacing = 0.3f;		// 形状之间的间距

private:

	static std::array<Texture, nb_shapes>	textures;			// 每个形状的纹理
	static std::array<glm::mat4, nb_shapes>	scale_matrices;		// 每个形状的缩放矩阵
	static Texture							light_texture;		// 光晕光源的纹理
	static glm::mat4						light_scale_matrix;	// 光源的缩放矩阵
	static VertexBuffer						object;				// OpenGL 顶点缓冲区

public:

	static void						init();			// 初始化
	static void						draw(const Camera& camera, const glm::vec3 light_position, float intensity, const Color& color);	// 渲染镜头光晕
};

#endif
