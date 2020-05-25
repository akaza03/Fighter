#pragma once
#include "cocos2d.h"
#include "input/OprtKey.h"
#include "input/UseKey.h"

//	システム用キー(now,old)
using systemKey = std::map <UseKey, std::pair<bool, bool>>;

class TitleScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	void update(float d);
	void SetCredit();
	void SetCrText(std::string str, int size, int &cor);

	void SetUI();

	OprtState *_oprtState;					//	システム用の操作制御

	systemKey key;

	cocos2d::Layer * creditLayer;

	bool gameButtonFlag = true;				//	trueならゲームスタート、falseならクレジット
	bool creditFlag = false;				//	クレジット表記中ならtrue
	bool GameMoveFlag = false;

	CREATE_FUNC(TitleScene);
};

