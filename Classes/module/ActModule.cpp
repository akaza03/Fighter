#include "unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	移動処理
	Move()(sp, act);
	//	敵が死亡時の吹き飛び処理
	Blow()(sp, act);
	//	攻撃
	Attack()(sp, act);
	//	向きの更新
	DirCheck()(sp, act);
	//	アニメーションの更新
	AnimUpdate()(sp, act);
	//　当たり判定
	DamageCheck()(sp, act);
	//	移動
	SetPos()(sp, act);
	//	キーの更新
	OldKeyUpdate()(sp, act);
}
