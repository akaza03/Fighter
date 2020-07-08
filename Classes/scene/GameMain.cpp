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
	resultTime = 0;

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
	if (!gameEndFlag)
	{
		lpScoreMng.update();
	}
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
	SetImage(feImage, "feverBase", Vec2(feImage->getContentSize().width, feImage->getContentSize().height), 150);

	feImage = Sprite::create(RES_ID("feverBar"));
	SetImage(feImage, "feverBar", Vec2(feImage->getContentSize().width, feImage->getContentSize().height), 200);

	feImage = Sprite::create(RES_ID("feverFront"));
	SetImage(feImage, "feverFront", Vec2(feImage->getContentSize().width, feImage->getContentSize().height), 255);

	feImage = Sprite::create(RES_ID("fever"));
	SetImage(feImage, "fever", Vec2(feImage->getContentSize().width, feImage->getContentSize().height * 4), 0);

	feImage = Sprite::create(RES_ID("fLine"));
	SetImage(feImage, "fLine", Vec2(confScSize.width / 2, confScSize.height / 2), 0);

	//	リザルト画像
	feImage = Sprite::create(RES_ID("GameClear"));
	SetImage(feImage, "GameClear", Vec2(confScSize.width / 2, confScSize.height - feImage->getContentSize().height), 0);

	//	時間用画像
	time = Number::create();
	time->setPosition(confScSize.width / 2 + 50, confScSize.height - 40);
	time->setSpan(40);
	time->setPrefix("number");
	UILayer->addChild(time, 1, "timeCounter");
	timeCount = 200 * 10 + 10;

	//	残り時間の文字
	feImage = Sprite::create(RES_ID("Remain"));
	SetImage(feImage, "Remain", Vec2(confScSize.width / 2 - 100, confScSize.height - 40), 255);

	timeUpdate();
}

void GameMain::SetImage(cocos2d::Sprite* sp, const char* name, cocos2d::Vec2 pos, int op)
{
	sp->setPosition(pos);
	sp->setOpacity(op);
	UILayer->addChild(sp, 1, name);
}

void GameMain::cameraUpdate()
{
	Player* player = (Player*)this->getChildByName("PLLayer")->getChildByName("player");

	auto playerPos = player->getPosition();
	//	マップのサイズ
	auto mapSize = lpMapMaker.GetMapSize();

	//	プレイヤーからカメラの左端までの距離
	auto leftDis = playerPos.x - confScSize.width / 2;
	//	カメラの右端からプレイヤーまでの距離
	auto rightDis = mapSize.width - playerPos.x;

	//	画面を揺らすフラグ
	bool shakeFlag = false;

	if (player->GetEnemyKill())
	{
		shakeFlag = true;
		player->SetEnemyKill(false);
	}

	//	敵が死亡時に画面を揺らす
	if (shakeFlag)
	{
		if (shakeTime < 10)
		{
			if (shakeTime % 10 == 0)
			{
				auto shakePos = 10;
				if (shakeLR)
				{
					shakeLR = false;
				}
				else
				{
					shakePos = -shakePos;
					shakeLR = true;
				}
				_camera->setPosition3D(Vec3(playerPos.x - confScSize.width / 2 + shakePos, 0, 0));
			}
			shakeTime++;
		}
		else
		{
			shakeFlag = false;
		}
	}
	else
	{
		shakeTime = 0;
		shakeLR = false;
		_camera->setPosition3D(Vec3(playerPos.x - confScSize.width / 2, 0, 0));
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
		Character* player = (Character*)PLLayer->getChildByName("player");

		//	プレイヤーがダメージを受けた場合は時間を減らす
		if (player != nullptr && player->GetDamage() != 0)
		{
			timeCount -= 100;
		}

		timeCount--;
		time->setNumber(timeCount / 10);
	}
}

void GameMain::startSchedule(float d)
{
	this->scheduleUpdate();

	//	プレイヤーのスケジュールセット
	Character* player = (Character*)PLLayer->getChildByName("player");
	player->scheduleUpdate();

	//	エネミーのスケジュールセット
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("EMLayer");
	for (auto obj : layer->getChildren())
	{
		obj->scheduleUpdate();
	}
}

void GameMain::endSchedule()
{
	this->unscheduleAllSelectors();

	//	プレイヤーのスケジュール削除
	Character* player = (Character*)PLLayer->getChildByName("player");
	player->unscheduleAllSelectors();

	//	エネミーのスケジュール削除
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("EMLayer");
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
			player->SetGameEnd(true);
			auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
			auto layer = nowScene->getChildByName("EMLayer");
			for (auto obj : layer->getChildren())
			{
				Character* chara = (Character*)obj;
				chara->SetGameEnd(true);
			}

			//	一部レイヤーを止める
			pause(BGLayer);
			pause(FGLayer);
			pause(UILayer);
			darkScreen();

			//	メイン用BGMを止めてリザルト用BGMを流す
			lpAudioManager.StopSound("mainBGM.cks");
			lpAudioManager.SetSound("gameEnd");
			lpAudioManager.SetSound("resultBGM.cks");

			//	リザルト用画像表示
			UILayer->getChildByName("GameClear")->setOpacity(255);

			//	画像非表示
			UILayer->removeChildByName("timeCounter");
			UILayer->removeChildByName("feverBase");
			UILayer->removeChildByName("feverBar");
			UILayer->removeChildByName("feverFront");
			UILayer->removeChildByName("fever");
			UILayer->removeChildByName("fLine");
			UILayer->removeChildByName("Remain");

			//	スコアの表示
			lpScoreMng.ResultScore();

			gameEndFlag = true;
		}

		//	タイトルに戻る処理
		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || (_oprtState->firstTouch() && resultTime > 100))
		{
			gameEnd();
		}
		resultTime++;
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
			pause(UILayer);
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

void GameMain::gameEnd()
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

void GameMain::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}