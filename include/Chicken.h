#ifndef CHICKEN_H
#define CHICKEN_H

#include "Mob.h"

// ����һ������

class Chicken : public Mob
{
private:

	Part		head;					// ͷ��
	Part		shoulder_1;				// ���
	Part		shoulder_2;				// �Ҽ�
	Part		hips_1;					// ����
	Part		hips_2;					// ����
	Part		leg;					// �Ȳ�
	Part		palm;					// ����
	Part		wing_1;					// ����
	Part		wing_2;					// ����
	Part		beak;					// �
	Part		beak_bottom;			// ��²�
	Part		wattle;					// ����
	glm::mat4	beak_bottom_initial;	// ��²��ĳ�ʼ����
	glm::mat4	shoulder_1_initial;		// ���ĳ�ʼ����
	glm::mat4	shoulder_2_initial;		// �Ҽ�ĳ�ʼ����
	glm::mat4	hips_1_initial;			// ���εĳ�ʼ����
	glm::mat4	hips_2_initial;			// ���εĳ�ʼ����

public:

	Chicken();
	Chicken(const Chicken& other);
	Chicken(const glm::vec3& position);

	Chicken& operator=(const Chicken& other);

	void		animate(float time);		// �������ţ�����ʱ����������¶���״̬
};

#endif
