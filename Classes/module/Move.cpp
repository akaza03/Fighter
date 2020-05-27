#include "unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.cType == CharaType::ENEMY)
	{
		if (act.anim != AnimState::DAMAGE && act.anim != AnimState::DIE && act.moveFlag)
		{
			//	¶ˆÚ“®
			if (act.dir == DIR::LEFT)
			{
				dis -= act.speed;
			}
			//	‰EˆÚ“®
			if (act.dir == DIR::RIGHT)
			{
				dis += act.speed;
			}

			act.totalDis += act.speed;

			if (act.totalDis >= 64)
			{
				act.totalDis = 0;
				act.moveFlag = false;
			}
		}
	}
	act.distance = cocos2d::Vec2(dis,0);

	return false;
}
