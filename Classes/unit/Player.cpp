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

			//	���݂�HP
			auto oldHp = itr.second.HP;
			//	���݂�charaID
			auto oldID = itr.second.charaID;

			//	���W���[�����g�p�����A�N�V��������
			ActModule()(*this, itr.second);

			//_animMap[nowAnimName(itr.second.nowAnim)].

			//	�L�����N�^�[�̌��
			if (oldID != itr.second.charaID)
			{
				_animMap.clear();
				lpAnimMng.SetAnim(itr.second.cType, itr.second.charaID, _animMap);
				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}

			if (itr.second.HP <= 0)
			{
				itr.second.HP = 0;
				itr.second.nowAnim = AnimState::DIE;
			}

			if (itr.second.HP >= itr.second.MaxHP)
			{
				itr.second.HP = itr.second.MaxHP;
			}

			if (itr.second.HP <= 0 && oldHp != itr.second.HP)
			{
				itr.second.nowAnim = AnimState::DIE;
				_actData.nowAnim = AnimState::DIE;
			}

			//	�O���̃`�F�b�N�p
			_actData.nowAnim = itr.second.nowAnim;

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	���̃A�j���[�V�����Ɍ��݂̃L�[����n������
				auto &nextKey = _charaList[nowAnimName(itr.second.nowAnim)];

				//	�L�[�̏�����
				for (auto itrKey : UseKey())
				{
					//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����̃L�[����n��
					std::get<0>(nextKey.key[itrKey]) = std::get<0>(itr.second.key[itrKey]);
					std::get<1>(nextKey.key[itrKey]) = std::get<1>(itr.second.key[itrKey]);
					//	���̃A�j���[�V�����̃L�[����������
					std::get<0>(itr.second.key[itrKey]) = false;
					std::get<1>(itr.second.key[itrKey]) = false;
				}
				//	�X�e�[�^�X��n��
				nextKey.nowAnim = itr.second.nowAnim;
				nextKey.HP = itr.second.HP;
				nextKey.dirInver = itr.second.dirInver;
				nextKey.charaID = itr.second.charaID;

				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}
}

