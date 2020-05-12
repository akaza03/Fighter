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
			//	�L�[�̃`�F�b�N
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	���̃L�[���o�^����Ă���΃L�[���X�V����
				if (std::get<2>(itr.second.key[checkKey.first]))
				{
					std::get<0>(itr.second.key[checkKey.first]) = checkKey.second;
				}
			}

			if ((CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) && (CC_TARGET_PLATFORM != CC_PLATFORM_MAC) && (CC_TARGET_PLATFORM != CC_PLATFORM_LINUX))
			{
				std::get<0>(itr.second.key[UseKey::K_SPACE]) = true;
			}

			unitUpdate(itr.second);
		}
	}
}

