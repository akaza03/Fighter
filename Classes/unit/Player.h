#pragma once
#include "Character.h"

class Player
	:public Character
{
public:
	Player();
	~Player();
	void update(float d);

	bool GetEnemyKill();
	void SetEnemyKill(bool flag);

	CREATE_FUNC(Player);
private:
	bool enemyKill;			//	“G‚ð“|‚µ‚½Žž—p‚Ìƒtƒ‰ƒO
};
