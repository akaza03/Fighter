#include "unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	�ړ�����
	Move()(sp, act);
	if (act.cType == CharaType::PLAYER)
	{
		//	�U��
		Attack()(sp, act);
	}
	//	�����̍X�V
	DirCheck()(sp, act);
	//	�A�j���[�V�����̍X�V
	AnimUpdate()(sp, act);
	//�@�����蔻��
	DamageCheck()(sp, act);
	//	�ړ�
	SetPos()(sp, act);
	//	�L�[�̍X�V
	OldKeyUpdate()(sp, act);
}
