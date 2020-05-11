#include "unit/Character.h"
#include "OldKeyUpdate.h"


bool OldKeyUpdate::operator()(cocos2d::Sprite & sp, ActData & act)
{
	for (auto itrKey : UseKey())
	{
		//	次のアニメーションに現在のアニメーションのキー情報を渡す
		std::get<1>(act.key[itrKey]) = std::get<0>(act.key[itrKey]);
	}
	return false;
}
