#ifndef FOX_H
#define FOX_H

#include "Mob.h"

// ����һ��������

class Fox : public Mob
{
private:

	Part		muzzle;				// ��������
	Part		ear_1;				// ���
	Part		ear_2;				// �Ҷ�
	Part		head;				// ͷ��
	Part		tail;				// β��
	Part		leg;				// ��
	Part		tailbase;			// β�͵ĸ���
	Part		shoulder_1;			// ����
	Part		shoulder_2;			// �Ҽ��
	Part		hips_1;				// ���β�
	Part		hips_2;				// ���β�
	glm::mat4	shoulder_1_initial;	// ����ĳ�ʼ����
	glm::mat4	shoulder_2_initial;	// �Ҽ��ĳ�ʼ����
	glm::mat4	hips_1_initial;		// ���β��ĳ�ʼ����
	glm::mat4	hips_2_initial;		// ���β��ĳ�ʼ����
	glm::mat4	head_initial;		// ͷ���ĳ�ʼ����
	glm::mat4	tail_initial;		// β�͵ĳ�ʼ����


public:

	Fox();
	Fox(const Fox& other);
	Fox(const glm::vec3& position);

	Fox& operator=(const Fox& other);

	void		animate(float time);	// ��������
};

#endif
