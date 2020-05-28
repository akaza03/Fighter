#include "unit/Character.h"
#include "Blow.h"

bool Blow::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.cType == CharaType::ENEMY && act.nowAnim == AnimState::DIE)
	{
		auto dis = cocos2d::Vec2(10,3);
		if (act.dir == DIR::RIGHT)
		{
			dis.x = - dis.x;
		}
		act.distance = dis;
	}
	return false;
}
