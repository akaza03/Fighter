#pragma once
#include <functional>
#include "cocos2d.h"
#include "module/ActSet.h"
#include "module/ActModule.h"
#include "manager/ResourceManager.h"
#include "manager/AnimManager.h"
#include "manager/ScoreManager.h"
#include "manager/AudioManager.h"
#include "manager/EffManager.h"
#include "input/UseKey.h"
#include "input/OprtState.h"

class OprtState;

using AnimMap = std::map < std::string, cocos2d::Action* >;

//	���݂̃L�[,1�t���[���O�̃L�[,�o�^����Ă��邩�ǂ���
using keyList = std::map<UseKey, std::tuple<bool, bool, bool>>;

//	�L�����N�^�[�̏��p
struct ActData
{
	int HP = 1;										//	�̗�
	int MaxHP = 1;									//	�ő�HP
	int damage = 0;									//	�󂯂��_���[�W
	int damageCnt = 0;								//	�_���[�W���󂯂����̍d������
	float speed = 0;								//	�ړ����x
	cocos2d::Vec2 distance = cocos2d::Vec2(0,0);	//	�ړ����鋗��
	float totalDis = 0;								//	���v�ړ�����
	bool moveFlag = false;							//	�G�̈ړ��p�t���O
	bool atkFlag = false;							//	�U�������ǂ���
	bool atkHit = false;							//	�U���������������ǂ���
	bool atkMiss = false;							//	�U�����O�ꂽ���ǂ���
	cocos2d::Vec2 touchPos;							//	�^�b�`���W
	bool dirInver = false;							//	�����]������ꍇ��true
	DIR dir = DIR::RIGHT;							//	���݂̌���
	keyList key;									//	�ǂ̃L�[���������珈������̂�(List)
	AnimState anim;									//	���g�̃A�j���[�V����
	AnimState nowAnim = AnimState::IDLE;			//	���݂̃A�j���[�V����
	CharaType cType;								//	�L�����N�^�[�̃^�C�v
	int charaID;									//	�L�����N�^�[��ID
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;
	bool SetInit(int id, cocos2d::Vec2 pos, int hp, float speed, DIR dir, cocos2d::Scene *scene);

	AnimState GetAnim();							//	���݂̃A�j���[�V�������擾

	//	�_���[�W�̃Z�b�g�Q�b�g
	void SetDamage(int number);
	int GetDamage();

	//	�_���[�W���̍d�����Ԃ̃Z�b�g�Q�b�g
	void SetDamageCnt(int number);
	int GetDamageCnt();

	//	�G�p�̈ړ��t���O�̃Z�b�g
	void SetMoveFlag(bool flag);

	//	�U���������������ǂ����̊m�F
	bool GetAtkMiss();

	//	�Q�[���I���̃Z�b�g
	void SetGameEnd(bool flag);

private:
	void InitActData();								//	ActData�̏�����
protected:
	OprtState *_oprtState;							//	���쐧��
	ActData _actData;								//	�L�����N�^�[�̏��p
	std::map<const char *,ActData> _charaList;		//	�L�����N�^�[�̏��p���X�g

	cocos2d::Vec2 oldTouchPos;
	bool deathFlag = false;							//	���S�t���O
	bool gameEndFlag = false;						//	�Q�[���I���t���O

	char *nowAnimName(AnimState animName);

	AnimMap _animMap;

	void unitUpdate(ActData & act);					//	unit���ʂ�update����

};
