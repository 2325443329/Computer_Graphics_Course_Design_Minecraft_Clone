#ifndef WOLF_H
#define WOLF_H

#include "Mob.h"

// �������࣬�̳���Mob��
class Wolf : public Mob
{
private:

    Part    muzzle;             // �ǵı��Ӳ���
    Part    ear_1;              // ���
    Part    ear_2;              // �Ҷ�
    Part    head;               // ͷ��
    Part    topbody;            // �ϰ���
    Part    tail;               // β��
    Part    front_leg_1;        // ��ǰ��
    Part    front_leg_2;        // ��ǰ��
    Part    back_leg_1;         // �����
    Part    back_leg_2;         // �Һ���
    Part    tailbase;           // β�͸���
    Part    shoulder_1;         // ����
    Part    shoulder_2;         // �Ҽ��
    Part    hip_1;              // ���β�
    Part    hip_2;              // ���β�
    glm::mat4 shoulder_1_initial;  // ��ʼ�������
    glm::mat4 shoulder_2_initial;  // ��ʼ�Ҽ�����
    glm::mat4 hip_1_initial;      // ��ʼ���β�����
    glm::mat4 hip_2_initial;      // ��ʼ���β�����

public:

    // ���캯��
    Wolf();
    // �������캯��
    Wolf(const Wolf& other);
    // ����λ�ù�����
    Wolf(const glm::vec3& position);

    // ��ֵ�����
    Wolf& operator=(const Wolf& other);

    // �������º���
    void animate(float time);
};

#endif
