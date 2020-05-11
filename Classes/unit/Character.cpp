#include "input/OprtKey.h"
#include "input/OprtTouch.h"
#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
	for (auto &itr : _animMap)
	{
		itr.second->release();
	}
}

bool Character::SetInit(int id, cocos2d::Vec2 pos, int hp, float speed, cocos2d::Scene *scene)
{
	_actData.HP = hp;
	_actData.MaxHP = _actData.HP;
	_actData.charaID = id;
	_actData.speed = speed;

	//	アニメーションのセット
	if (!lpAnimMng.SetAnim(_actData.cType, id, _animMap))
	{
		return false;
	}
	InitActData();

	auto sprite = Sprite::create();
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));

	if (_actData.cType == CharaType::PLAYER)
	{
		//	プラットフォームによって操作方法を変える
		if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
		{
			_oprtState = new OprtKey();
		}
		else
		{
			_oprtState = new OprtTouch();
		}

		//	操作イベントの作成
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), scene);
	}

	setFlippedX(true);

	return true;
}

int Character::GetDamageCnt()
{
	return _actData.damageCnt;
}

void Character::InitActData()
{
	//	キャラクターの情報の追加
	//oldTouchPos = _actData.touchPos;

	_actData.key[UseKey::K_LEFT] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_RIGHT] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_UP] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_DOWN] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_SPACE] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_A] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_S] = std::make_tuple(false, false, true);

	//_actData.checkPoint[DIR::LEFT] = false;
	//_actData.checkPoint[DIR::RIGHT] = false;
	//_actData.checkPoint[DIR::UP] = false;
	//_actData.checkPoint[DIR::DOWN] = false;

	_actData.anim = AnimState::IDLE;
	_charaList.emplace(std::make_pair("idle", _actData));
	_actData.anim = AnimState::RUN;
	_charaList.emplace(std::make_pair("run", _actData));
	_actData.anim = AnimState::ATK;
	_charaList.emplace(std::make_pair("atk", _actData));

	_actData.key[UseKey::K_LEFT] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_RIGHT] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_UP] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_DOWN] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_SPACE] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_A] = std::make_tuple(false, false, false);
	_actData.key[UseKey::K_S] = std::make_tuple(false, false, false);

	_actData.anim = AnimState::DAMAGE;
	_charaList.emplace(std::make_pair("damage", _actData));
	_actData.anim = AnimState::DIE;
	_charaList.emplace(std::make_pair("die", _actData));

	lpAnimMng.AnimRun(this, _charaList["idle"].nowAnim, _charaList["idle"].cType, _animMap);
}

char * Character::nowAnimName(AnimState animName)
{
	char* nextKeyName = "idle";
	switch (animName)
	{
	case IDLE:
		nextKeyName = "idle";
		break;
	case RUN:
		nextKeyName = "run";
		break;
	case ATK:
		nextKeyName = "atk";
		break;
	case DAMAGE:
		nextKeyName = "damage";
		break;
	case DIE:
		nextKeyName = "die";
		break;
	case STATE_MAX:
		break;
	default:
		break;
	}

	return nextKeyName;
}
