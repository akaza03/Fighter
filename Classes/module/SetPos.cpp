#include "unit/Character.h"
#include "SetPos.h"

bool SetPos::operator()(cocos2d::Sprite & sp, ActData & act)
{
	sp.setPosition(sp.getPosition().x + act.distance, sp.getPosition().y);
	return false;
}
