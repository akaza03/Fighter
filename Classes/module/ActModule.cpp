#include "unit/Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	�ړ�����
	Move()(sp, act);
	//	�U��
	Attack()(sp, act);

	//	�A�j���[�V�����̍X�V
	AnimUpdate()(sp, act);
	//	�����̍X�V
	DirCheck()(sp, act);
	//	�ړ�
	SetPos()(sp, act);

	//	�L�[�̍X�V
	OldKeyUpdate()(sp, act);

	DamageCheck()(sp, act);
}
