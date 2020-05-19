#pragma once
#include <cocos2d.h>


class Number:public cocos2d::Sprite
{
public:
	void setPrefix(std::string prefix);		//	数字の画像ファイルのセット
	void setSpan(int span);
	void setAlignCenter();
	void setNumber(int num);				//	数字のセット
	void remove(void);
	bool init()override;
	CREATE_FUNC(Number);
private:
	void CreateNumber(int num);				//	数字オブジェクトの作成
	void RemoveNumber(void);				//	数字をクリア

	int _num;
	int _span;
	bool _alignCenter;

	cocos2d::SpriteFrameCache* cache;		//	数字画像キャッシュ
};

