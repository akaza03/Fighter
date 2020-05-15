#include "unit/Character.h"
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

			if (player->GetAtkMiss() && player->GetAnim() == AnimState::ATK)
			{
				act.atkFlag = true;
			}
			else
			{
				act.atkFlag = false;
			}
		}
	}
	return false;
}
