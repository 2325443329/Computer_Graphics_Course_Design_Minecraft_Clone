#ifndef WOLF_H
#define WOLF_H

#include "Mob.h"

// 定义狼类，继承自Mob类
class Wolf : public Mob
{
private:

    Part    muzzle;             // 狼的鼻子部分
    Part    ear_1;              // 左耳
    Part    ear_2;              // 右耳
    Part    head;               // 头部
    Part    topbody;            // 上半身
    Part    tail;               // 尾巴
    Part    front_leg_1;        // 左前腿
    Part    front_leg_2;        // 右前腿
    Part    back_leg_1;         // 左后腿
    Part    back_leg_2;         // 右后腿
    Part    tailbase;           // 尾巴根部
    Part    shoulder_1;         // 左肩膀
    Part    shoulder_2;         // 右肩膀
    Part    hip_1;              // 左臀部
    Part    hip_2;              // 右臀部
    glm::mat4 shoulder_1_initial;  // 初始左肩膀矩阵
    glm::mat4 shoulder_2_initial;  // 初始右肩膀矩阵
    glm::mat4 hip_1_initial;      // 初始左臀部矩阵
    glm::mat4 hip_2_initial;      // 初始右臀部矩阵

public:

    // 构造函数
    Wolf();
    // 拷贝构造函数
    Wolf(const Wolf& other);
    // 根据位置构造狼
    Wolf(const glm::vec3& position);

    // 赋值运算符
    Wolf& operator=(const Wolf& other);

    // 动画更新函数
    void animate(float time);
};

#endif
