#include "unit/Character.h"
#include "DamageCheck.h"

bool DamageCheck::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (act.anim == AnimState::ATK)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

		//	�L�����N�^�[�̃^�C�v�ɂ���đ���̃��C���[��ς���
		auto layer = nowScene->getChildByName("EMLayer");
		if (act.cType == CharaType::ENEMY)
		{
			layer = nowScene->getChildByName("PLLayer");
		}

		auto cPos = sp.getPosition();
		auto spSize = sp.getContentSize();

		//	�����Ă�������ɑ΂��čU������pBOX
		auto rect = cocos2d::Rect(cPos.x, cPos.y - spSize.height / 2, spSize.width / 3, spSize.height / 2);
		if (act.dir == DIR::LEFT)
		{
			rect = cocos2d::Rect(cPos.x - spSize.width / 3, cPos.y - spSize.height / 2, spSize.width / 3, spSize.height / 2);
		}
		
		for (auto obj : layer->getChildren())
		{
			//	����̔���pBOX
			auto objBox = obj->boundingBox();

			Character* enemy = (Character*)obj;

			//	���ꂼ���BOX�𔻒�
			if (rect.intersectsRect(objBox))
			{
				if (!lpScoreMng.GetFever() || act.cType == CharaType::PLAYER)
				{
					//	���肪���Ƀ_���[�W��ԂȂ珈�����Ȃ�
					if (enemy->GetAnim() != AnimState::DAMAGE && enemy->GetAnim() != AnimState::DIE
						&& enemy->GetDamage() == 0 && enemy->GetDamageCnt() == 0)
					{
						//	�_���[�W��^���A������̂����点��
						enemy->SetDamage(1);
						if (lpScoreMng.GetFever())
						{
							enemy->SetDamageCnt(0);
						}
						else
						{
							enemy->SetDamageCnt(10);
						}

						//	�v���C���[���_���[�W���󂯂��ꍇ�̓X�R�A�����炷
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

