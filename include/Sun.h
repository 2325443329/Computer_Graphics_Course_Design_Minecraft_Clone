#ifndef SUN_H
#define SUN_H

#include "utils.h"
#include "Luminary.h"

// ����̫���࣬�̳���Luminary��

class Sun : public Luminary
{
public:

	// ��ʼ��̫��
	void	init() override;

	// ����̫����λ�û�״̬��ͨ��������ҵ�λ��
	void	update(const glm::vec3& player_pos) override;
};

#endif
