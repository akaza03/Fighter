#include "unit/Character.h"
#include "AnimUpdate.h"

bool AnimUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto anim = AnimState::IDLE;
	if (act.damageCnt > 0)
	{
		anim = AnimState::DAMAGE;
	}
	else if (act.atkFlag)
	{
		anim = AnimState::ATK;
	}

	if (act.nowAnim == AnimState::DIE)
	{
		anim = AnimState::DIE;
	}
	act.nowAnim = anim;

	return false;
}
