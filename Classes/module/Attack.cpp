#include "unit/Character.h"
#include "DamageCheck.h"
#include "Attack.h"

bool Attack::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	画面横サイズ
	auto scSizeX = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width;

	act.atkFlag = true;
	//	プレイヤーの場合
	if (act.cType == CharaType::PLAYER)
	{
		//	Android版
		if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
		{
			if (sp.getActionByTag(10))
			{
			}
			else if (act.touchPos.x >= 0 && act.touchPos.x < scSizeX / 2)
			{
				if (act.dir == DIR::RIGHT)
				{
					act.dirInver = true;
				}
			}
			else if (act.touchPos.x >= scSizeX / 2 && act.touchPos.x <= scSizeX)
			{
				if (act.dir == DIR::LEFT)
				{
					act.dirInver = true;
				}
			}
			else
			{
				act.atkFlag = false;
			}
		}
		//	PC版
		else
		{
			if (sp.getActionByTag(10))
			{
			}
			else if (std::get<0>(act.key[UseKey::K_LEFT]) && !std::get<1>(act.key[UseKey::K_LEFT]))
			{
				if (act.dir == DIR::RIGHT)
				{
					act.dirInver = true;
				}
			}
			else if (std::get<0>(act.key[UseKey::K_RIGHT]) && !std::get<1>(act.key[UseKey::K_RIGHT]))
			{
				if (act.dir == DIR::LEFT)
				{
					act.dirInver = true;
				}
			}
			else
			{
				act.atkFlag = false;
			}
		}
	}
	//	敵の場合
	else
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("PLLayer");

		for (auto obj : layer->getChildren())
		{
			Character* player = (Character*)obj;

			act.atkFlag = false;
			if (player->GetAtkMiss() && player->GetAnim() == AnimState::ATK)
			{
				if (EnemyHitCheck(sp, act))
				{
					act.atkFlag = true;
				}
			}
		}
	}
	return false;
}

bool Attack::EnemyHitCheck(cocos2d::Sprite & sp, ActData & act)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	auto layer = nowScene->getChildByName("PLLayer");

	auto cPos = sp.getPosition();
	auto spSize = sp.getContentSize();

	//	向いている方向に対して攻撃判定用BOX
	auto rect = cocos2d::Rect(cPos.x, cPos.y - spSize.height / 2, spSize.width / 3, spSize.height / 2);
	if (act.dir == DIR::LEFT)
	{
		rect = cocos2d::Rect(cPos.x - spSize.width / 3, cPos.y - spSize.height / 2, spSize.width / 3, spSize.height / 2);
	}

	for (auto obj : layer->getChildren())
	{
		//	相手の判定用BOX
		auto objBox = obj->boundingBox();
		Character* enemy = (Character*)obj;
		//	それぞれのBOXを判定
		if (rect.intersectsRect(objBox))
		{
			//	ダメージを与え、相手をのけぞらせる
			return true;
		}
	}
	return false;
}
