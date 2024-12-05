#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "utils.h"
#include "Texture.h"

// ����һ��֡��������

class FrameBuffer
{
private:

	std::shared_ptr<GLuint>	fbo;		// ֡��������ID
	Texture					texture;	// ֡������������
	std::shared_ptr<GLuint>	rbo;		// ���/ģ�建������ID
	uint16_t				width;		// �ֱ��ʣ���ȣ�
	uint16_t				height;		// �ֱ��ʣ��߶ȣ�

public:

	static FrameBuffer		game;		// ���ں����֡������
	static FrameBuffer		reflection;	// ����ˮ�淴���֡������
	static FrameBuffer		refraction;	// ����ˮ�������֡������
	static FrameBuffer		lens_flare;	// ���ھ�ͷ���ε�֡������

	FrameBuffer();
	FrameBuffer(const FrameBuffer& other);
	FrameBuffer(uint16_t width, uint16_t height);
	~FrameBuffer();

	FrameBuffer& operator=(const FrameBuffer& other);

	void					create(uint16_t width, uint16_t height);	// ����֡������
	Texture					get_texture() const;						// ��ȡ����
	void					bind() const;								// ��֡������

	static void				unbind();									// ���֡������
	static void				clear();									// ���֡����������
	static void				init();										// ��ʼ��֡������
};

#endif
