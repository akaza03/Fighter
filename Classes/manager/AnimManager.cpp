#include "AnimManager.h"

AnimManager* AnimManager::s_Instance = nullptr;


AnimManager::AnimManager()
{
	AnimationInit();
}


AnimManager::~AnimManager()
{
	for (auto &itr : _animMap)
	{
		itr.second->release();
	}
}

void AnimManager::AnimationInit()
{
	auto pass = RES_ID("p0unit");
	_animMap["p0_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["p0_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["p0_atk"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 2, 0.1f, false);
	_animMap["p0_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["p0_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);

	pass = RES_ID("e0unit");
	_animMap["e0_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["e0_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["e0_atk"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 2, 0.1f, false);
	_animMap["e0_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["e0_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);

	pass = RES_ID("e1unit");
	_animMap["e1_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["e1_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["e1_atk"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 2, 0.1f, false);
	_animMap["e1_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["e1_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);

	pass = RES_ID("e2unit");
	_animMap["e2_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["e2_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["e2_atk"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 2, 0.1f, false);
	_animMap["e2_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["e2_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);

	pass = RES_ID("e3unit");
	_animMap["e3_idle"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 0), 3, 0.3f, true);
	_animMap["e3_run"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(2, 1), 2, 0.3f, true);
	_animMap["e3_atk"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(1, 3), 2, 0.1f, false);
	_animMap["e3_damage"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(0, 4), 3, 0.3f, true);
	_animMap["e3_die"] = AnimationCreate(pass, cocos2d::Vec2(9, 6), cocos2d::Vec2(6, 5), 3, 0.3f, true);
}

cocos2d::Animation * AnimManager::AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop)
{
	//	キャッシュ用画像
	auto cacheSp = cocos2d::Sprite::create(imagePass);
	auto spTexture = cacheSp->getTexture();
	auto _animation = cocos2d::Animation::create();
	//	1コマのサイズ
	auto imageSize = cocos2d::Vec2(cacheSp->getContentSize().width / divCnt.x, cacheSp->getContentSize().height / divCnt.y);

	for (int i = 0; i < animCntMax; i++)
	{
		if (startID.x >= divCnt.x)
		{
			startID.x = 0;
			startID.y++;
		}
		_animation->addSpriteFrameWithTexture(spTexture,cocos2d::Rect(startID.x * imageSize.x, startID.y * imageSize.y,
																		imageSize.x, imageSize.y));
		startID.x++;
	}
	_animation->setDelayPerUnit(frame);

	_animation->setRestoreOriginalFrame(true);

	_animation->retain();

	return _animation;
}

void AnimManager::AnimRun(cocos2d::Sprite * sprite, AnimState anim, CharaType type , AnimMap &charaAnim)
{
	auto animName = GetAnimName(anim);

	auto action = charaAnim[animName];

	if (action != nullptr)
	{
		if (animName == "atk")
		{
			action->setTag(10);
		}
		sprite->stopAllActions();
		sprite->runAction(charaAnim[animName]);
	}

	AnimCountPlus(charaAnim);
}


bool AnimManager::SetAnim(CharaType type, int id, AnimMap &anim)
{
	std::string charaID;
	if (type == CharaType::PLAYER)
	{
		charaID = "p";
	}
	else if (type == CharaType::ENEMY)
	{
		charaID = "e";
	}

	charaID = charaID + std::to_string(id);

	if (_animMap.count(charaID + "_idle") != 0)
	{
		anim["idle"] = cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_idle"]));
		anim["run"] = cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_run"]));
		anim["atk"] = cocos2d::Animate::create(_animMap[charaID + "_atk"]);
		anim["damage"] = cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_damage"]));
		anim["die"] = cocos2d::RepeatForever::create(cocos2d::Animate::create(_animMap[charaID + "_die"]));
		return true;
	}
	return false;
}

void AnimManager::AnimCountPlus(AnimMap &anim)
{
	anim["idle"]->retain();
	anim["run"]->retain();
	anim["atk"]->retain();
	anim["damage"]->retain();
	anim["die"]->retain();
}

std::string AnimManager::GetAnimName(AnimState anim)
{
	switch (anim)
	{
	case IDLE:
		return "idle";
		break;
	case RUN:
		return "run";
		break;
	case ATK:
		return "atk";
		break;
	case DAMAGE:
		return "damage";
		break;
	case DIE:
		return "die";
		break;
	case STATE_MAX:
		break;
	default:
		break;
	}
	return "non";
}
