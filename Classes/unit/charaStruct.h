#pragma once

//	�A�j���[�V�����̃^�C�v
enum AnimState
{
	IDLE,
	RUN,
	ATK,
	DAMAGE,
	DIE,
	STATE_MAX
};

//	�L�����N�^�[�̃^�C�v
enum CharaType
{
	PLAYER,
	ENEMY,
	CHARA_MAX
};

//	����
enum DIR
{
	LEFT,
	RIGHT,
	DIR_MAX
};