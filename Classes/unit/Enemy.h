#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	void update(float d);
	CREATE_FUNC(Enemy);
private:
	void typeUpdate(ActData &act);					//	charaID‚²‚Æ‚Ìˆ—
};

