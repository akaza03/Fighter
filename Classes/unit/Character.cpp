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
	_actData.touchPos = cocos2d::Vec2(-10, -10);

	//	�A�j���[�V�����̃Z�b�g
	if (!lpAnimMng.SetAnim(_actData.cType, id, _animMap))
	{
		return false;
	}

	InitActData();

	auto sprite = Sprite::create();
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));

	//if (_actData.cType == CharaType::PLAYER)
	{
		//	�v���b�g�t�H�[���ɂ���đ�����@��ς���
		if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
		{
			_oprtState = new OprtKey();
		}
		else
		{
			_oprtState = new OprtTouch();
		}

		//	����C�x���g�̍쐬
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), scene);
	}

	setFlippedX(true);

	return true;
}


void Character::InitActData()
{
	//	�L�����N�^�[�̏��̒ǉ�
	oldTouchPos = _actData.touchPos;

	_actData.key[UseKey::K_LEFT] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_RIGHT] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_UP] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_DOWN] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_SPACE] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_A] = std::make_tuple(false, false, true);
	_actData.key[UseKey::K_S] = std::make_tuple(false, false, true);

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

void Character::unitUpdate(ActData & act)
{
	//	���݂�HP
	auto oldHp = act.HP;
	//	���݂�charaID
	auto oldID = act.charaID;

	//	���W���[�����g�p�����A�N�V��������
	ActModule()(*this, act);

	if (act.damageCnt > 0)
	{
		_actData.damageCnt--;
	}

	act.HP -= _actData.damage;
	_actData.damage = 0;

	if (act.HP >= act.MaxHP)
	{
		act.HP = act.MaxHP;
	}

	if (act.HP <= 0 && oldHp != act.HP)
	{
		act.HP = 0;
		act.nowAnim = AnimState::DIE;
		_actData.nowAnim = AnimState::DIE;
	}

	//	�O���̃`�F�b�N�p
	_actData.nowAnim = act.nowAnim;

	act.damageCnt = _actData.damageCnt;

	if (act.nowAnim != act.anim)
	{
		//	���̃A�j���[�V�����Ɍ��݂̃L�[����n������
		auto &nextKey = _charaList[nowAnimName(act.nowAnim)];

		//	�L�[�̏�����
		for (auto itrKey : UseKey())
		{
			//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����̃L�[����n��
			std::get<0>(nextKey.key[itrKey]) = std::get<0>(act.key[itrKey]);
			std::get<1>(nextKey.key[itrKey]) = std::get<1>(act.key[itrKey]);
			//	���̃A�j���[�V�����̃L�[����������
			std::get<0>(act.key[itrKey]) = false;
			std::get<1>(act.key[itrKey]) = false;
		}
		//	�X�e�[�^�X��n��
		nextKey.nowAnim = act.nowAnim;
		nextKey.HP = act.HP;
		nextKey.atkFlag = act.atkFlag;
		nextKey.dir = act.dir;
		nextKey.dirInver = act.dirInver;
		nextKey.charaID = act.charaID;
		nextKey.touchPos = act.touchPos;
		nextKey.damageCnt = act.damageCnt;

		lpAnimMng.AnimRun(this, act.nowAnim, act.cType, _animMap);
	}
}


AnimState Character::GetAnim()
{
	return _actData.nowAnim;
}

int Character::GetDamage()
{
	return _actData.damage;
}

void Character::SetDamage(int number)
{
	_actData.damage = number;
}

int Character::GetDamageCnt()
{
	return _actData.damageCnt;
}

void Character::SetDamageCnt(int number)
{
	_actData.damageCnt = number;
}