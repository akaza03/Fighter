#pragma once

//	アニメーションのタイプ
enum AnimState
{
	IDLE,
	RUN,
	ATK,
	DAMAGE,
	DIE,
	STATE_MAX
};

//	キャラクターのタイプ
enum CharaType
{
	PLAYER,
	ENEMY,
	CHARA_MAX
};

//	向き
enum DIR
{
	LEFT,
	RIGHT,
	DIR_MAX
};