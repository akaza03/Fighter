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

	//	�v���C���[�̍쐬
	lpMapMaker.SetChara(CharaType::PLAYER, PLLayer, this);
	//	�G�̍쐬
	lpMapMaker.SetChara(CharaType::ENEMY, EMLayer, this);

	lpScoreMng.SetNumber(UILayer);

	//	�w�i�摜���܂Ƃ߂ĕ\������p
	lpMapMaker.SetBackImage(RES_ID("MainBack"), BGLayer);

	//	�J�����̃Z�b�g
	_camera = Camera::createOrthographic(confScSize.width, confScSize.height, 0, 1000);
	cameraUpdate();

	this->addChild(_camera);
	_camera->setCameraFlag(CameraFlag::USER1);

	BGLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	PLLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	EMLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);
	FGLayer->setCameraMask(static_cast<int>(CameraFlag::USER1), true);

	//	BGM�̐ݒ�
	lpAudioManager.SetSound("mainBGM.cks");

	//	����C�x���g�̍쐬
	//	�v���b�g�t�H�[���ɂ���đ�����@��ς���
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
	//	Audio�̍X�V
	lpAudioManager.update();
	//	�X�R�A�̍X�V
	lpScoreMng.update();
	//	�L�[�̍X�V
	keyUpdate();
	//	camera�̍X�V
	cameraUpdate();
	//	�G�t�F�N�g�̍X�V
	lpEffectManager.update(_camera);
	//	�������Ԃ̍X�V
	timeUpdate();
	//	�Q�[���N���A���f
	screenUpdate();

	//	keyOld�̍X�V
	for (auto itrKey : UseKey())
	{
		key[itrKey].second = key[itrKey].first;
	}
}

void GameMain::SetUI()
{
	//	�|�[�Y���p�̍�����
	auto fadeImage = Sprite::create();
	fadeImage->setTextureRect(Rect(0, 0, scSize.width * 2, scSize.height * 2));
	fadeImage->setPosition(0, 0);
	fadeImage->setColor(Color3B(0, 0, 0));
	fadeImage->setOpacity(0);
	BWLayer->addChild(fadeImage, 0, "fade");

	//	�t�B�[�o�[�p�摜
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

	//	���ԗp�摜
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
		//	�}�b�v�̃T�C�Y
		auto mapSize = BGLayer->getChildByName("stageMap")->getContentSize();

		//	�v���C���[����J�����̍��[�܂ł̋���
		auto leftDis = playerPos.x - confScSize.width / 2;
		//	�J�����̉E�[����v���C���[�܂ł̋���
		auto rightDis = mapSize.width - playerPos.x;

		//	���[����
		if (leftDis < 0)
		{
			_camera->setPosition3D(Vec3(0, 0, 0));
		}
		//	�E�[����
		else if (rightDis < confScSize.width / 2)
		{
			_camera->setPosition3D(Vec3(mapSize.width - confScSize.width, 0, 0));
		}
		//	�ʏ�̃X�N���[��
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

			//	�v���C���[���_���[�W���󂯂��ꍇ�͎��Ԃ����炷
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

	//	�v���C���[�̃X�P�W���[���Z�b�g
	auto layer = nowScene->getChildByName("PLLayer");
	for (auto obj : layer->getChildren())
	{
		obj->scheduleUpdate();
	}

	//	�G�l�~�[�̃X�P�W���[���Z�b�g
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

	//	�v���C���[�̃X�P�W���[���폜
	auto layer = nowScene->getChildByName("PLLayer");
	for (auto obj : layer->getChildren())
	{
		obj->unscheduleAllSelectors();
	}

	//	�G�l�~�[�̃X�P�W���[���폜
	layer = nowScene->getChildByName("EMLayer");
	for (auto obj : layer->getChildren())
	{
		obj->unscheduleAllSelectors();
	}
}

void GameMain::screenUpdate()
{
	Character* player = (Character*)PLLayer->getChildByName("player");
	//	�Q�[���N���Aor�Q�[���I�[�o�[����
	if (player->GetAnim() == AnimState::DIE || timeCount / 10 <= 0)
	{
		if (!gameEndFlag)
		{
			//	�v���C���[�ƃG�l�~�[�ɃQ�[���I���̍��}�𑗂�
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
		//	�|�[�Y���
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
		//	�|�[�Y����
		if (pauseFlag)
		{
			childs->resumeSchedulerAndActions();
		}
		//	�|�[�Y�J�n
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