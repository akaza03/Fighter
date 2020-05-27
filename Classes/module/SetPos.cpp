#include "unit/Character.h"
#include "SetPos.h"

bool SetPos::operator()(cocos2d::Sprite & sp, ActData & act)
{
	sp.setPosition(sp.getPosition().x + act.distance.x, sp.getPosition().y + act.distance.y);
	return false;
}
