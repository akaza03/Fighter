#include "unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.cType == CharaType::ENEMY)
	{
		if (act.anim != AnimState::DAMAGE)
		{
			//	���ړ�
			if (std::get<0>(act.key[UseKey::K_LEFT])
				&& std::get<2>(act.key[UseKey::K_LEFT]))
			{
				dis -= act.speed;
			}
			//	�E�ړ�
			if (std::get<0>(act.key[UseKey::K_RIGHT])
				&& std::get<2>(act.key[UseKey::K_RIGHT]))
			{
				dis += act.speed;
			}
		}
	}
	act.distance = dis;

	return false;
}
