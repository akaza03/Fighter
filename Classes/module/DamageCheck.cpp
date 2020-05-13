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

			//	���肪���Ƀ_���[�W��ԂȂ珈�����Ȃ�
			if (enemy->GetAnim() != AnimState::DAMAGE && enemy->GetDamage() == 0)
			{
				//	���ꂼ���BOX�𔻒�
				if (rect.intersectsRect(objBox))
				{
					enemy->SetDamage(50);
					enemy->SetDamageCnt(50);
					//if (act.damageCnt <= 0 && act.invTime <= 0 && act.anim != AnimState::THROW && act.anim != AnimState::DAMAGE)
					//{
					//	//	���������ꍇ�̓_���[�W�d��
					//	act.damageCnt = shot->GetStunTime();
					//	DoDamage(sp, act);
					//}
				}
			}
		}
	}
	return false;
}

void DamageCheck::DoDamage(cocos2d::Sprite & sp, ActData & act)
{
}

