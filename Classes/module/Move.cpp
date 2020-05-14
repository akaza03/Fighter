#include "unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.cType == CharaType::ENEMY)
	{
		if (act.anim != AnimState::DAMAGE && act.anim != AnimState::DIE)
		{
			//	左移動
			if (act.dir == DIR::LEFT)
			{
				dis -= act.speed;
			}
			//	右移動
			if (act.dir == DIR::RIGHT)
			{
				dis += act.speed;
			}
		}
	}
	act.distance = dis;

	return false;
}
