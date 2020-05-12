#include "Player.h"

Player::Player()
{
	_actData.cType = CharaType::PLAYER;
}

Player::~Player()
{
}

void Player::update(float d)
{
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			//	キーのチェック
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	そのキーが登録されていればキーを更新する
				if (std::get<2>(itr.second.key[checkKey.first]))
				{
					std::get<0>(itr.second.key[checkKey.first]) = checkKey.second;
				}
			}

			if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
			{
				std::get<0>(itr.second.key[UseKey::K_SPACE]) = true;
			}

			//	タッチ座標の取得
			if (_oprtState->GetTouchPoint() != oldTouchPos)
			{
				itr.second.touchPos = _oprtState->GetTouchPoint();
				oldTouchPos = itr.second.touchPos;
			}
			else
			{
				itr.second.touchPos = cocos2d::Vec2(-10, -10);
			}

			unitUpdate(itr.second);
		}
	}
}

