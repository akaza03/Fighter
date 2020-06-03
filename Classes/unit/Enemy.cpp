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

		//	エネミーを全員スライドさせる
		for (auto obj : layer->getChildren())
		{
			Character* enemy = (Character*)obj;
			enemy->SetMoveFlag(true);
		}

		//	新しくエネミーを生み出す
		EnemyCreate();

		//	エフェクトとサウンドを発生させる
		lpEffectManager.SetEffect(RES_ID("deathEff").c_str(), "FGLayer", true, getPosition(), 20, true);
		lpAudioManager.SetSound("blow");

		deathFlag = false;
	}

	if (_actData.nowAnim == AnimState::DIE)
	{
		if (getPosition().x <= 0 || getPosition().x >= lpMapMaker.GetMapSize().width)
		{
			//	自身をエネミーレイヤーから削除する
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

			//	スコアとフィーバーカウントを増やす
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

