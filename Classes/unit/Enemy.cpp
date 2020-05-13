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
			//	デバッグ用
			//	キーのチェック
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	そのキーが登録されていればキーを更新する
				if (std::get<2>(itr.second.key[checkKey.first]))
				{
					std::get<0>(itr.second.key[checkKey.first]) = checkKey.second;
				}
			}

			unitUpdate(itr.second);
		}
	}

	if (deathFlag)
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		auto layer = nowScene->getChildByName("EMLayer");
		layer->removeChild(this);
	}
}

