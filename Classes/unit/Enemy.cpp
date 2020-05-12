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
}

void Enemy::typeUpdate(ActData & act)
{

}
