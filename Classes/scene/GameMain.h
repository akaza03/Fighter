/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "manager/ResourceManager.h"

enum LayerNumber
{
	BG,						//	バックグラウンド用レイヤー
	PL,						//	プレイヤー&攻撃用レイヤー
	EM,						//	エネミー&攻撃用レイヤー
	AT,
	UI,						//	UI用レイヤー
	BW,						//	画面を暗くするレイヤー(ポーズ画面など)
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
	cocos2d::Layer * PLLayer;				//	プレイヤー&攻撃用レイヤー
	cocos2d::Layer * EMLayer;				//	エネミー&攻撃用レイヤー
	cocos2d::Layer * ATKLayer;
	cocos2d::Layer * UILayer;				//	UI用レイヤー
	cocos2d::Layer * BWLayer;				//	画面を暗くするレイヤー(ポーズ画面など)
	cocos2d::Layer * FGLayer;				//	フロントグラウンド用レイヤー
	cocos2d::Layer * DBLayer;				//	デバッグ用レイヤー

	cocos2d::Camera* _camera;

	void update(float d);

	void cameraUpdate();

	void startSchedule(float d);
	void endSchedule(float d);

	cocos2d::Size confScSize;				//	設定上の画面サイズ
	cocos2d::Size scSize;					//	実際の画面サイズ
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
};

#endif // __HELLOWORLD_SCENE_H__
