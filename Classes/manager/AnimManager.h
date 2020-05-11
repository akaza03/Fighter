#pragma once
#include <map>
#include "cocos2d.h"
#include "unit/charaStruct.h"
#include "unit/Character.h"

#define lpAnimMng AnimManager::GetInstance()

using AnimMap = std::map < std::string, cocos2d::Action* >;

class Character;

class AnimManager
{
public:
	static AnimManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AnimManager();
		}
		return *s_Instance;
	}
	~AnimManager();

	//	アニメーションの登録
	//	画像パス,画像全体の分割数,分割開始ID,アニメーションの分割数,フレーム数,ループするかどうか
	cocos2d::Animation* AnimationCreate(std::string imagePass, cocos2d::Vec2 divCnt, cocos2d::Vec2 startID, int animCntMax, float frame, bool loop);
	
	//	アニメーションの開始
	void AnimRun(cocos2d::Sprite* sprite, AnimState anim, CharaType type, AnimMap &charaAnim);

	//	キャラクターにアニメーション情報を渡す
	bool SetAnim(CharaType type, int id, AnimMap &anim);
private:
	AnimManager();
	void AnimationInit();										//	アニメーションの登録用

	std::string GetAnimName(AnimState anim);					//	アニメーション開始時のアニメーション名取得用

	void AnimCountPlus(AnimMap &anim);							//	参照カウントを増やす

	std::map < std::string, cocos2d::Animation* > _animMap;		//	アニメーション情報を収納

	static AnimManager* s_Instance;
};
