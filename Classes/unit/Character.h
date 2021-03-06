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

//	現在のキー,1フレーム前のキー,登録されているかどうか
using keyList = std::map<UseKey, std::tuple<bool, bool, bool>>;

//	キャラクターの情報用
struct ActData
{
	int HP = 1;										//	体力
	int MaxHP = 1;									//	最大HP
	int damage = 0;									//	受けたダメージ
	int damageCnt = 0;								//	ダメージを受けた時の硬直時間
	float speed = 0;								//	移動速度
	cocos2d::Vec2 distance = cocos2d::Vec2(0,0);	//	移動する距離
	float totalDis = 0;								//	合計移動距離
	bool moveFlag = false;							//	敵の移動用フラグ
	bool atkFlag = false;							//	攻撃中かどうか
	bool atkHit = false;							//	攻撃が当たったかどうか
	bool atkMiss = false;							//	攻撃が外れたかどうか
	cocos2d::Vec2 touchPos;							//	タッチ座標
	bool dirInver = false;							//	方向転換する場合はtrue
	DIR dir = DIR::RIGHT;							//	現在の向き
	keyList key;									//	どのキーを押したら処理するのか(List)
	AnimState anim;									//	自身のアニメーション
	AnimState nowAnim = AnimState::IDLE;			//	現在のアニメーション
	CharaType cType;								//	キャラクターのタイプ
	int charaID;									//	キャラクターのID
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;
	bool SetInit(int id, cocos2d::Vec2 pos, int hp, float speed, DIR dir, cocos2d::Scene *scene);

	AnimState GetAnim();							//	現在のアニメーションを取得

	//	ダメージのセットゲット
	void SetDamage(int number);
	int GetDamage();

	//	ダメージ時の硬直時間のセットゲット
	void SetDamageCnt(int number);
	int GetDamageCnt();

	//	敵用の移動フラグのセット
	void SetMoveFlag(bool flag);

	//	攻撃が当たったかどうかの確認
	bool GetAtkMiss();

	//	ゲーム終了のセット
	void SetGameEnd(bool flag);

private:
	void InitActData();								//	ActDataの初期化
protected:
	OprtState *_oprtState;							//	操作制御
	ActData _actData;								//	キャラクターの情報用
	std::map<const char *,ActData> _charaList;		//	キャラクターの情報用リスト

	cocos2d::Vec2 oldTouchPos;
	bool deathFlag = false;							//	死亡フラグ
	bool gameEndFlag = false;						//	ゲーム終了フラグ

	char *nowAnimName(AnimState animName);

	AnimMap _animMap;

	void unitUpdate(ActData & act);					//	unit共通のupdate処理

};
