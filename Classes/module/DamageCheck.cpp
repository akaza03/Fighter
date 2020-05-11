#include "unit/Character.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	return false;
}

void DamageCheck::DoDamage(cocos2d::Sprite & sp, ActData & act)
{
}

