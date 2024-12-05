#ifndef MOB_H
#define MOB_H

#include "utils.h"
#include "Entity.h"

class World;

// 定义一个生物类

// 行走前的时间
// 跳跃前的时间
// 随机时间
// 当前动画帧
// 是否有动画
// 是否会消失

class Mob : public Entity
{
private:

	int				time_check;			
	int				tempo;				
	int				time_check_rand;	
	float			animation_frame;	
	bool			is_animated;		
	bool			will_dispawn;		

public:

					Mob();
					Mob(const Mob& other);

	virtual Mob&	operator=(const Mob& other);

	void			behaviour();
	void			update(const World& world, const glm::vec3& player_pos) override;
	void			update_dispawn(const glm::vec3& player_pos);
	virtual void	animate(float time) = 0;

	friend			World;
};

#endif