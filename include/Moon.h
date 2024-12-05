#ifndef MOON_H
#define MOON_H

#include "utils.h"
#include "Luminary.h"

// ����һ�������࣬�̳��� Luminary ��

class Moon : public Luminary
{
private:

	bool	inverted; // �����ľ����Ƿ��򣨱�ʾ�Ƿ�����ʾ��

public:

	// ��ʼ������������д�Ի���
	void	init() override;

	// ����������״̬����д�Ի���
	void	update(const glm::vec3& player_pos) override;
};

#endif
