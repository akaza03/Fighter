#include "unit/Character.h"
#include "AnimUpdate.h"

bool AnimUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto anim = AnimState::IDLE;
	if (act.damageCnt > 0)
	{
		anim = AnimState::DAMAGE;
	}
	else if (std::get<1>(act.key[UseKey::K_SPACE]))
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
