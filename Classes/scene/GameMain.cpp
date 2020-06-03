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

#include "GameMain.h"
#include "TitleScene.h"
#include "map/MapMaker.h"
#include "unit/Player.h"
#include "input/OprtKey.h"
#include "input/OprtTouch.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameMain::createScene()
{
    return GameMain::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	confScSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	scSize = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize();
	lpScoreMng.InitNumber();
	lpScoreMng.SetScore(0);
	lpScoreMng.SetFeverCnt(0);
	lpScoreMng.SetFever(false);
	gameEndFlag = false;

	BGLayer = Layer::create();
	this->addChild(BGLayer, LayerNumber::BG, "BGLayer");
	PLLayer = Layer::create();
	this->addChild(PLLayer, LayerNumber::PL, "PLLayer");
	EMLayer = Layer::create();
	this->addChild(EMLayer, LayerNumber::EM, "EMLayer");
	FGLayer = Layer::create();
	this->addChild(FGLayer, LayerNumber::FG, "FGLayer");
	UILayer = Layer::create();
	this->addChild(UILayer, LayerNumber::UI, "UILayer");
	BWLayer = Layer::create();
	this->addChild(BWLayer, LayerNumber::BW, "BWLayer");

	lpMapMaker.SetMap("map.tmx", BGLayer, "stageMap");

	SetUI();

	//	プレイヤーの作成
	lpMapMaker.SetChara(CharaType::PLAYER, PLLayer, this);
	//	敵の作成
	lpMapMaker.SetChara(CharaType::ENEMY, EMLayer, this);

	lpScoreMng.SetNumber(UILayer);

	//	背景画像をまとめて表示する用
	lpMapMaker.SetBackImage(RES_ID("MainBack"), BGLayer);

	//	カメラのセット
	_camera = Camera::createOrthographic(confScSize.width, confScSize.height, 0, 1000);
	cameraUpdate();

	this->addChild(_camera);
	_camera->setCameraFlag(CameraFlag::USER1);

	BGLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	PLLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	EMLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	FGLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);

	//	BGMの設定
	lpAudioManager.SetSound("mainBGM.cks");

	//	操作イベントの作成
	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), this);

	this->scheduleOnce(schedule_selector(GameMain::startSchedule), 2.1f);

    return true;
}

void GameMain::update(float d)
{
	//	Audioの更新
	lpAudioManager.update();
	//	スコアの更新
	lpScoreMng.update();
	//	キーの更新
	keyUpdate();
	//	cameraの更新
	cameraUpdate();
	//	エフェクトの更新
	lpEffectManager.update(_camera);
	//	制限時間の更新
	timeUpdate();
	//	ゲームクリア判断
	screenUpdate();

	//	keyOldの更新
	for (auto itrKey : UseKey())
	{
		key[itrKey].second = key[itrKey].first;
	}
}

void GameMain::SetUI()
{
	//	ポーズ時用の黒い幕
	auto fadeImage = Sprite::create();
	fadeImage->setTextureRect(Rect(0, 0, scSize.width * 2, scSize.height * 2));
	fadeImage->setPosition(0, 0);
	fadeImage->setColor(Color3B(0, 0, 0));
	fadeImage->setOpacity(0);
	BWLayer->addChild(fadeImage, 0, "fade");

	//	フィーバー用画像
	auto feImage = Sprite::create(RES_ID("feverBase"));
	feImage->setPosition(feImage->getContentSize().width, feImage->getContentSize().height);
	feImage->setOpacity(150);
	UILayer->addChild(feImage, 1, "feverBase");

	feImage = Sprite::create(RES_ID("feverBar"));
	feImage->setPosition(feImage->getContentSize().width, feImage->getContentSize().height);
	feImage->setOpacity(200);
	UILayer->addChild(feImage, 1, "feverBar");

	feImage = Sprite::create(RES_ID("feverFront"));
	feImage->setPosition(feImage->getContentSize().width, feImage->getContentSize().height);
	UILayer->addChild(feImage, 1, "feverFront");

	//	時間用画像
	time = Number::create();
	time->setPosition(confScSize.width / 2, confScSize.height - 40);
	time->setSpan(40);
	time->setPrefix("number");
	UILayer->addChild(time, 1, "timeCounter");
	timeCount = 200 * 10 + 10;
	timeUpdate();
}

void GameMain::cameraUpdate()
{
	Player* player = (Player*)this->getChildByName("PLLayer")->getChildByName("player");

	if (player->GetDamageCnt() <= 0)
	{
		auto playerPos = player->getPosition();
		//	マップのサイズ
		auto mapSize = BGLayer->getChildByName("stageMap")->getContentSize();

		//	プレイヤーからカメラの左端までの距離
		auto leftDis = playerPos.x - confScSize.width / 2;
		//	カメラの右端からプレイヤーまでの距離
		auto rightDis = mapSize.width - playerPos.x;

		//	左端処理
		if (leftDis < 0)
		{
			_camera->setPosition3D(Vec3(0, 0, 0));
		}
		//	右端処理
		else if (rightDis < confScSize.width / 2)
		{
			_camera->setPosition3D(Vec3(mapSize.width - confScSize.width, 0, 0));
		}
		//	通常のスクロール
		else
		{
			_camera->setPosition3D(Vec3(playerPos.x - confScSize.width / 2, 0, 0));
		}
	}
}

void GameMain::keyUpdate()
{
	for (auto checkKey : _oprtState->GetKeyList())
	{
		key[checkKey.first].first = checkKey.second;
	}
}

void GameMain::timeUpdate()
{
	if (timeCount > 0 && !pauseFlag)
	{
		for (auto obj : PLLayer->getChildren())
		{
			Character* pl = (Character*)obj;

			//	プレイヤーがダメージを受けた場合は時間を減らす
			if (pl->GetDamage() != 0)
			{
				timeCount -= 100;
			}
		}

		timeCount--;
		time->setNumber(timeCount / 10);
	}
}

void GameMain::startSchedule(float d)
{
	this->scheduleUpdate();

	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	//	プレイヤーのスケジュールセット
	auto layer = nowScene->getChildByName("PLLayer");
	for (auto obj : layer->getChildren())
	{
		obj->scheduleUpdate();
	}

	//	エネミーのスケジュールセット
	layer = nowScene->getChildByName("EMLayer");
	for (auto obj : layer->getChildren())
	{
		obj->scheduleUpdate();
	}
}

void GameMain::endSchedule()
{
	this->unscheduleAllSelectors();

	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

	//	プレイヤーのスケジュール削除
	auto layer = nowScene->getChildByName("PLLayer");
	for (auto obj : layer->getChildren())
	{
		obj->unscheduleAllSelectors();
	}

	//	エネミーのスケジュール削除
	layer = nowScene->getChildByName("EMLayer");
	for (auto obj : layer->getChildren())
	{
		obj->unscheduleAllSelectors();
	}
}

void GameMain::screenUpdate()
{
	Character* player = (Character*)PLLayer->getChildByName("player");
	//	ゲームクリアorゲームオーバー処理
	if (player->GetAnim() == AnimState::DIE || timeCount / 10 <= 0)
	{
		if (!gameEndFlag)
		{
			//	プレイヤーとエネミーにゲーム終了の合図を送る
			auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
			auto layer = nowScene->getChildByName("PLLayer");
			for (auto obj : layer->getChildren())
			{
				Character* chara = (Character*)obj;
				chara->SetGameEnd(true);
			}

			layer = nowScene->getChildByName("EMLayer");
			for (auto obj : layer->getChildren())
			{
				Character* chara = (Character*)obj;
				chara->SetGameEnd(true);
			}

			pause(BGLayer);
			pause(FGLayer);
			darkScreen();

			lpAudioManager.StopSound("mainBGM.cks");
			lpAudioManager.SetSound("gameEnd");

			gameEndFlag = true;
		}

		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || _oprtState->firstTouch())
		{
			endSchedule();

			auto fadeTime = 2.0f;
			lpAudioManager.ResetAudio();
			lpAudioManager.SetSound("click");
			auto scene = TitleScene::createScene();

			lpScoreMng.SetScore(0);
			lpScoreMng.SetFeverCnt(0);
			lpScoreMng.SetFever(false);
			auto fade = TransitionFade::create(fadeTime, scene);
			Director::getInstance()->replaceScene(fade);
		}
	}
	else
	{
		//	ポーズ画面
		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second)
		{
			pause(PLLayer);
			pause(EMLayer);
			pause(BGLayer);
			pause(FGLayer);
			darkScreen();
		}
	}
}

void GameMain::pause(cocos2d::Layer* layer)
{
	auto scSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	for (auto* childs : layer->getChildren())
	{
		//	ポーズ解除
		if (pauseFlag)
		{
			childs->resumeSchedulerAndActions();
		}
		//	ポーズ開始
		else
		{
			childs->pauseSchedulerAndActions();
		}
	}
}

void GameMain::darkScreen()
{
	if (pauseFlag)
	{
		BWLayer->removeChildByName("pauseText");
		BWLayer->getChildByName("fade")->setOpacity(0);
		pauseFlag = false;
	}
	else
	{
		BWLayer->getChildByName("fade")->setOpacity(120);
		pauseFlag = true;
	}
}

void GameMain::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}