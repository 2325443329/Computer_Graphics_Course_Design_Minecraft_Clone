#ifndef LENSFLARE_H
#define LENSFLARE_H

#include "utils.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Camera.h"

// ����һ����ͷ������

class LensFlare
{
public:

	static constexpr uint8_t				nb_shapes = 9;		// ��״����
	static constexpr float					size = 2.5f;		// ��״�Ĵ�С
	static constexpr float				 spacing = 0.3f;		// ��״֮��ļ��

private:

	static std::array<Texture, nb_shapes>	textures;			// ÿ����״������
	static std::array<glm::mat4, nb_shapes>	scale_matrices;		// ÿ����״�����ž���
	static Texture							light_texture;		// ���ι�Դ������
	static glm::mat4						light_scale_matrix;	// ��Դ�����ž���
	static VertexBuffer						object;				// OpenGL ���㻺����

public:

	static void						init();			// ��ʼ��
	static void						draw(const Camera& camera, const glm::vec3 light_position, float intensity, const Color& color);	// ��Ⱦ��ͷ����
};

#endif
