#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>
#include "UIClass/Number.h"
#include "input/OprtKey.h"
#include "input/UseKey.h"
#include "ck/sound.h"

 //	システム用キー(now,old)
using sysKey = std::map <UseKey, std::pair<bool, bool>>;

enum LayerNumber
{
	BG,						//	バックグラウンド用レイヤー
	PL,						//	プレイヤー&攻撃用レイヤー
	EM,						//	エネミー&攻撃用レイヤー
	BW,						//	画面を暗くするレイヤー(ポーズ画面など)
	UI,						//	UI用レイヤー
	FG,						//	フロントグラウンド用レイヤー
	DB,						//	デバッグ用レイヤー
	LAYER_MAX
};

class GameMain : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

private:
	cocos2d::Layer * BGLayer;				//	バックグラウンド用レイヤー
	cocos2d::Layer * PLLayer;				//	プレイヤー用レイヤー
	cocos2d::Layer * EMLayer;				//	エネミー用レイヤー
	cocos2d::Layer * BWLayer;				//	画面を暗くするレイヤー(ポーズ画面など)
	cocos2d::Layer * UILayer;				//	UI用レイヤー
	cocos2d::Layer * FGLayer;				//	フロントグラウンド用レイヤー
	cocos2d::Layer * DBLayer;				//	デバッグ用レイヤー

	cocos2d::Camera* _camera;

	OprtState *_oprtState;					//	システム用の操作制御
	sysKey key;

	Number* time;							//	時間用

	void update(float d);

	void SetUI();

	//	画像の配置処理(画像本体,登録名,座標,透明度)
	void SetImage(cocos2d::Sprite* sp, const char* name, cocos2d::Vec2 pos, int op);

	void cameraUpdate();
	void keyUpdate();
	void timeUpdate();

	void startCounter(float d);				//	ゲーム開始のカウントを始める処理

	void startSchedule(float d);			//	開始時のカウント終了後に動き出すupdate処理
	void endSchedule();						//	ゲーム終了時にそれぞれのupdateを止める処理

	void screenUpdate();					//	ゲーム終了時やポーズ時の画面処理
	void pause(cocos2d::Layer* layer);		//	ポーズ
	void darkScreen();						//	ポーズ時の画面の暗転処理

	void ResultScene(float d);				//	リザルト処理
	void gameEnd();							//	ゲームを終了し、タイトルに戻る処理

	cocos2d::Size confScSize;				//	設定上の画面サイズ
	cocos2d::Size scSize;					//	実際の画面サイズ

	int timeCount;							//	残り時間

	float resultTime;						//	リザルト用時間計測

	Number *startNumber;					//	スタート時のカウント用
	bool startFlag;							//	スタート時のカウント終了フラグ

	bool pauseFlag;
	bool gameEndFlag;
	
	bool shakeLR;							//	画面を揺らす際の左右フラグ
	int shakeTime;							//	画面を揺らす際の時間計測用
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
};

#endif // __HELLOWORLD_SCENE_H__
