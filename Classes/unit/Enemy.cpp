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

		for (auto obj : layer->getChildren())
		{
			Character* enemy = (Character*)obj;
			enemy->SetMoveFlag(true);
		}

		layer->removeChild(this);
	}
}

