#include "unit/Character.h"
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto dis = 0;
	if (act.cType == CharaType::ENEMY)
	{
		if (act.anim != AnimState::DAMAGE)
		{
			//	¶ˆÚ“®
			if (std::get<0>(act.key[UseKey::K_A])
				&& std::get<2>(act.key[UseKey::K_A]))
			{
				dis -= act.speed;
			}
			//	‰EˆÚ“®
			if (std::get<0>(act.key[UseKey::K_S])
				&& std::get<2>(act.key[UseKey::K_S]))
			{
				dis += act.speed;
			}
		}
	}
	act.distance = dis;

	return false;
}
