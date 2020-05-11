#include "unit/Character.h"
#include "AnimUpdate.h"

bool AnimUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto anim = AnimState::IDLE;
	if (act.damageCnt > 0)
	{
		anim = AnimState::DAMAGE;
	}
	else if ((!sp.getActionByTag(10) && std::get<0>(act.key[UseKey::K_SPACE]) && !std::get<1>(act.key[UseKey::K_SPACE]))
		 || (sp.getActionByTag(10)))
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
