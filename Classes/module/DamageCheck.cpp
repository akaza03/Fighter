#include "unit/Character.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.anim == AnimState::ATK)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

		//	キャラクターのタイプによって相手のレイヤーを変える
		auto layer = nowScene->getChildByName("EMLayer");
		if (act.cType == CharaType::ENEMY)
		{
			layer = nowScene->getChildByName("PLLayer");
		}

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
				if (!lpScoreMng.GetFever() || act.cType == CharaType::PLAYER)
				{
					//	相手が既にダメージ状態なら処理しない
					if (enemy->GetAnim() != AnimState::DAMAGE && enemy->GetAnim() != AnimState::DIE
						&& enemy->GetDamage() == 0 && enemy->GetDamageCnt() == 0)
					{
						//	ダメージを与え、相手をのけぞらせる
						enemy->SetDamage(1);
						if (lpScoreMng.GetFever())
						{
							enemy->SetDamageCnt(0);
						}
						else
						{
							enemy->SetDamageCnt(10);
						}

						//	プレイヤーがダメージを受けた場合はスコアを減らす
						if (act.cType == CharaType::ENEMY)
						{
							lpScoreMng.PlusScore(-200);
							lpScoreMng.PlusFeverCnt(-30);
						}
					}
					act.atkHit = true;
				}
			}
		}

		if (!act.atkHit)
		{
			act.atkMiss = true;
		}
	}
	else
	{
		act.atkMiss = false;
		act.atkHit = false;
	}
	return false;
}

