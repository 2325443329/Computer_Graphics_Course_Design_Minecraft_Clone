#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "utils.h"
#include "Texture.h"

// 定义一个帧缓冲区类

class FrameBuffer
{
private:

	std::shared_ptr<GLuint>	fbo;		// 帧缓冲区的ID
	Texture					texture;	// 帧缓冲区的纹理
	std::shared_ptr<GLuint>	rbo;		// 深度/模板缓冲区的ID
	uint16_t				width;		// 分辨率（宽度）
	uint16_t				height;		// 分辨率（高度）

public:

	static FrameBuffer		game;		// 用于后处理的帧缓冲区
	static FrameBuffer		reflection;	// 用于水面反射的帧缓冲区
	static FrameBuffer		refraction;	// 用于水面折射的帧缓冲区
	static FrameBuffer		lens_flare;	// 用于镜头光晕的帧缓冲区

	FrameBuffer();
	FrameBuffer(const FrameBuffer& other);
	FrameBuffer(uint16_t width, uint16_t height);
	~FrameBuffer();

	FrameBuffer& operator=(const FrameBuffer& other);

	void					create(uint16_t width, uint16_t height);	// 创建帧缓冲区
	Texture					get_texture() const;						// 获取纹理
	void					bind() const;								// 绑定帧缓冲区

	static void				unbind();									// 解绑帧缓冲区
	static void				clear();									// 清除帧缓冲区内容
	static void				init();										// 初始化帧缓冲区
};

#endif
