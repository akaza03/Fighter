#include "map/MapMaker.h"
#include "Enemy.h"


Enemy::Enemy()
{

	_actData.cType = CharaType::ENEMY;

}


Enemy::~Enemy()
{
}

void Enemy::update(float d)
{
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			unitUpdate(itr.second);
		}
	}

	if (deathFlag)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("EMLayer");

		//	�G�l�~�[��S���X���C�h������
		for (auto obj : layer->getChildren())
		{
			Character* enemy = (Character*)obj;
			enemy->SetMoveFlag(true);
		}

		//	�V�����G�l�~�[�𐶂ݏo��
		EnemyCreate();

		//	�G�t�F�N�g�ƃT�E���h�𔭐�������
		lpEffectManager.SetEffect(RES_ID("deathEff").c_str(), "FGLayer", true, getPosition(), 20, true);
		lpAudioManager.SetSound("blow");

		deathFlag = false;
	}

	if (_actData.nowAnim == AnimState::DIE)
	{
		if (getPosition().x <= 0 || getPosition().x >= lpMapMaker.GetMapSize().width)
		{
			//	���g���G�l�~�[���C���[����폜����
			auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
			auto layer = nowScene->getChildByName("EMLayer");
			layer->removeChild(this);
		}
	}
}

void Enemy::EnemyCreate()
{
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			lpMapMaker.SetEnemy(itr.second.charaID, itr.second.dir);

			//	�X�R�A�ƃt�B�[�o�[�J�E���g�𑝂₷
			auto point = 1;
			switch (itr.second.charaID)
			{
			case 0:
				point = 50;
				break;
			case 1:
				point = 100;
				break;
			default:
				break;
			}
			lpScoreMng.PlusScore(point);
			lpScoreMng.PlusFeverCnt(20);
		}
	}
}

