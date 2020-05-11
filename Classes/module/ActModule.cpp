#include "unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	移動処理
	Move()(sp, act);

	//	アニメーションの更新
	AnimUpdate()(sp, act);

	//	移動
	SetPos()(sp, act);

	//	攻撃
	Attack()(sp, act);

	//	キーの更新
	OldKeyUpdate()(sp, act);

	DamageCheck()(sp, act);
}
