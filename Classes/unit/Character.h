#pragma once
#include <functional>
#include "cocos2d.h"
#include "module/ActSet.h"
#include "module/ActModule.h"
#include "manager/ResourceManager.h"
#include "manager/AnimManager.h"
#include "input/UseKey.h"
#include "input/OprtState.h"

class OprtState;

using AnimMap = std::map < std::string, cocos2d::Action* >;

//	現在のキー,1フレーム前のキー,登録されているかどうか
using keyList = std::map<UseKey, std::tuple<bool, bool, bool>>;

//	キャラクターの情報用
struct ActData
{
	int HP = 1;									//	体力
	int MaxHP = 1;								//	最大HP
	float speed = 0;							//	移動速度
	float distance = 0;
	bool atkFlag = false;						//	攻撃中かどうか
	cocos2d::Vec2 touchPos;						//	タッチ座標
	int damageCnt = 0;							//	ダメージを受けた時の硬直時間
	bool dirInver = false;						//	方向転換する場合はtrue
	DIR dir = DIR::RIGHT;						//	現在の向き
	keyList key;								//	どのキーを押したら処理するのか(List)
	AnimState anim;								//	自身のアニメーション
	AnimState nowAnim = AnimState::IDLE;		//	現在のアニメーション
	CharaType cType;							//	キャラクターのタイプ
	int charaID;
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;
	bool SetInit(int id, cocos2d::Vec2 pos, int hp, float speed, cocos2d::Scene *scene);

	int GetDamageCnt();																//	硬直時のカメラ制御用

private:
	void InitActData();										//	ActDataの初期化
protected:
	OprtState *_oprtState;									//	操作制御
	ActData _actData;										//	キャラクターの情報用
	std::map<const char *,ActData> _charaList;				//	キャラクターの情報用リスト

	cocos2d::Vec2 oldTouchPos;

	char *nowAnimName(AnimState animName);

	AnimMap _animMap;

	void unitUpdate(ActData & act);							//	unit共通のupdate処理

};
