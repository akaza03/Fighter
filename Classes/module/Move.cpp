#include "unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.cType == CharaType::ENEMY)
	{
		if (act.anim != AnimState::DAMAGE && act.anim != AnimState::DIE && act.moveFlag)
		{
			//	���ړ�
			if (act.dir == DIR::LEFT)
			{
				dis -= act.speed;
			}
			//	�E�ړ�
			if (act.dir == DIR::RIGHT)
			{
				dis += act.speed;
			}

			act.totalDis += act.speed;

			if (act.totalDis >= 48)
			{
				act.totalDis = 0;
				act.moveFlag = false;
			}
		}
	}
	act.distance = dis;

	return false;
}
