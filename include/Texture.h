#ifndef TEXTURE_H
#define TEXTURE_H

#include "utils.h"

// ���������࣬���ڹ���Ͳ�������

class Texture
{
private:

	std::shared_ptr<GLuint>	id;				// ����ID������OpenGL�е��������

public:

	static Texture			blocks;			// ���������
	//static Texture			player;			// ���ģ�͵�����
	static Texture			sun;			// ̫��������
	static Texture			moon;			// ����������
	static Texture			water_dudv;		// ����Ť��ˮ�淴�������
	static Texture			water_normals;	// ����ˮ�淨�ߵ�����
	static Texture			cursor;			// ��Ϸ�еĹ������
	static Texture          wolf;            // �ǵ�����
	static Texture          fox;             // ���������
	static Texture          chicken;         // ��������
	static std::vector<Texture> player_skins; // ���ڴ洢�������Ƥ������

	Texture();				// ���캯��
	Texture(const Texture& other);	// ���ƹ��캯��
	Texture(const std::string& path);	// ��·���Ĺ��캯��
	~Texture();				// ��������

	Texture& operator=(const Texture& other);	// ��ֵ�����

	// ��������֧���������ģʽ�͹���ģʽ������
	void					load(const std::string& path, GLenum wrapping = GL_REPEAT, GLint filtering = GL_NEAREST);

	// ������ָ��������Ԫ
	void					bind(uint8_t index) const;

	// ��ȡ�����ID
	GLuint					get_id() const;

	// ��ȡ����ID��ָ��
	GLuint* get_id_ptr();

	// ���������ID
	void					set_id(GLuint id);

	// �������
	static void				unbind();

	// ��ʼ������������磬���������Ĭ��״̬��
	static void				init();

	// ���ڼ������е����Ƥ������
	static void load_player_skins();
};

#endif
