#include "unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.cType == CharaType::ENEMY)
	{
		if (act.anim != AnimState::DAMAGE && act.anim != AnimState::DIE && act.moveFlag)
		{
			auto mSpeed = act.speed;
			if (lpScoreMng.GetFever())
			{
				mSpeed += act.speed;
			}

			//	¶ˆÚ“®
			if (act.dir == DIR::LEFT)
			{
				dis -= mSpeed;
			}
			//	‰EˆÚ“®
			if (act.dir == DIR::RIGHT)
			{
				dis += mSpeed;
			}

			act.totalDis += mSpeed;

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
