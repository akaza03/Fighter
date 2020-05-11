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

			//	現在のHP
			auto oldHp = itr.second.HP;
			//	現在のcharaID
			auto oldID = itr.second.charaID;

			//	モジュールを使用したアクション処理
			ActModule()(*this, itr.second);

			//_animMap[nowAnimName(itr.second.nowAnim)].

			//	キャラクターの交代
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

			//	外部のチェック用
			_actData.nowAnim = itr.second.nowAnim;

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	次のアニメーションに現在のキー情報を渡す準備
				auto &nextKey = _charaList[nowAnimName(itr.second.nowAnim)];

				//	キーの初期化
				for (auto itrKey : UseKey())
				{
					//	次のアニメーションに現在のアニメーションのキー情報を渡す
					std::get<0>(nextKey.key[itrKey]) = std::get<0>(itr.second.key[itrKey]);
					std::get<1>(nextKey.key[itrKey]) = std::get<1>(itr.second.key[itrKey]);
					//	今のアニメーションのキー情報を初期化
					std::get<0>(itr.second.key[itrKey]) = false;
					std::get<1>(itr.second.key[itrKey]) = false;
				}
				//	ステータスを渡す
				nextKey.nowAnim = itr.second.nowAnim;
				nextKey.HP = itr.second.HP;
				nextKey.dirInver = itr.second.dirInver;
				nextKey.charaID = itr.second.charaID;

				lpAnimMng.AnimRun(this, itr.second.nowAnim, itr.second.cType, _animMap);
			}
		}
	}
}

