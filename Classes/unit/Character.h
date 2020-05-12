#pragma once
#include <functional>
#include "cocos2d.h"
#include "module/ActSet.h"
#include "module/ActModule.h"
#include "manager/ResourceManager.h"
#include "manager/AnimManager.h"
#include "input/UseKey.h"
#include "input/OprtState.h"

class OprtState;

using AnimMap = std::map < std::string, cocos2d::Action* >;

//	���݂̃L�[,1�t���[���O�̃L�[,�o�^����Ă��邩�ǂ���
using keyList = std::map<UseKey, std::tuple<bool, bool, bool>>;

//	�L�����N�^�[�̏��p
struct ActData
{
	int HP = 1;									//	�̗�
	int MaxHP = 1;								//	�ő�HP
	float speed = 0;							//	�ړ����x
	float distance = 0;
	bool atkFlag = false;						//	�U�������ǂ���
	cocos2d::Vec2 touchPos;						//	�^�b�`���W
	int damageCnt = 0;							//	�_���[�W���󂯂����̍d������
	bool dirInver = false;						//	�����]������ꍇ��true
	DIR dir = DIR::RIGHT;						//	���݂̌���
	keyList key;								//	�ǂ̃L�[���������珈������̂�(List)
	AnimState anim;								//	���g�̃A�j���[�V����
	AnimState nowAnim = AnimState::IDLE;		//	���݂̃A�j���[�V����
	CharaType cType;							//	�L�����N�^�[�̃^�C�v
	int charaID;
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;
	bool SetInit(int id, cocos2d::Vec2 pos, int hp, float speed, cocos2d::Scene *scene);

	int GetDamageCnt();																//	�d�����̃J��������p

private:
	void InitActData();										//	ActData�̏�����
protected:
	OprtState *_oprtState;									//	���쐧��
	ActData _actData;										//	�L�����N�^�[�̏��p
	std::map<const char *,ActData> _charaList;				//	�L�����N�^�[�̏��p���X�g

	cocos2d::Vec2 oldTouchPos;

	char *nowAnimName(AnimState animName);

	AnimMap _animMap;

	void unitUpdate(ActData & act);							//	unit���ʂ�update����

};
