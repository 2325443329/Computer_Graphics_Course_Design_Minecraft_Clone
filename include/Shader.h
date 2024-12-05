#ifndef SHADER_H
#define SHADER_H

#include "libraries.h"

// �������־��Ϣ����󳤶ȶ���
#define ERROR_MAX_LENGTH 500

// ��ɫ���ƺ꣬���ڸ�ʽ����־���
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define BOLD  "\x1B[1m"
#define RESET "\x1B[0m"

// λ�����꣬�������ú�����ض�λ
#define SET_BIT(bits, pos)   (bits |= 1 << (pos))
#define RESET_BIT(bits, pos) (bits &= ~(1 << (pos)))

// ��ȡ��ǰ�ļ����ļ�����ȥ��·����
#ifndef __FILENAME__
#define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#endif

// ������󡢾������Ϣ����ĺ꣬�����ļ������к�
#ifndef SHADER_ERROR
#define SHADER_ERROR(x, ...)     (fprintf(stderr, RED "Error : " GRN "%s:%d " RESET x, __FILENAME__, __LINE__, ## __VA_ARGS__))
#endif

#ifndef SHADER_WARNING
#define SHADER_WARNING(x, ...)   (fprintf(stdout, YEL "Warning : " GRN "%s:%d " RESET x, __FILENAME__, __LINE__, ## __VA_ARGS__))
#endif

#ifndef SHADER_INFO
#define SHADER_INFO(x, ...)   (fprintf(stdout, BOLD WHT "INFO : " RESET GRN "%s:%d " RESET x , __FILENAME__, __LINE__, ## __VA_ARGS__))
#endif

// ����û��ֱ��ʹ�� std::cout�������ú�����ʽ�����󡢾������Ϣ

// Shader�࣬���ڼ��غ͹�����ɫ������
class Shader
{
private:

	std::shared_ptr<GLuint>	program_id;	// ��ɫ������ID
	std::shared_ptr<GLuint>	vertex_id;	// ������ɫ��ID
	std::shared_ptr<GLuint>	frag_id;	// Ƭ����ɫ��ID

	// ������ɫ������
	int						loadShader(const std::string& code, int type);

	// ���ļ�������ɫ��
	bool					loadFromFiles(FILE* vertexFile, FILE* fragFile);

	// ���ַ���������ɫ��
	bool					loadFromStrings(const std::string& vertexString, const std::string& fragString);

public:

	// ����Ԥ�������ɫ�������磬ˮ����ա��顢���εȣ�
	static Shader			block;		// �����ɫ��
	static Shader			entity;		// ʵ�壨����������ɫ��
	static Shader			sky;		// ��յ���ɫ��
	static Shader			luminary;	// �������ɫ��
	static Shader			water;		// ˮ�����ɫ��
	static Shader			in_water;	// �����ˮ��ʱ��ˮ����ɫ��
	static Shader			screen;		// �������ɫ��
	static Shader			lens_flare;	// ��ͷ���ε���ɫ��
	static Shader			debug;		// ������ɫ��

	// ���캯������������
	Shader();
	Shader(const Shader& other);
	Shader(const std::string& vert_path, const std::string& frag_path);
	~Shader();

	Shader& operator=(const Shader& other);

	// ���ļ�������ɫ��
	bool					load(const std::string& vert_path, const std::string& frag_path);

	// ��ȡ��ɫ������ID
	GLuint					get_id() const;

	// ����ɫ��
	void					bind() const;

	// �������ɫ��
	static void				unbind();

	// ��ʼ����ɫ��ϵͳ
	static void				init();
};

#endif
