#include "TitleScene.h"
#include "input/OprtTouch.h"
#include "GameMain.h"

//#pragma execution_character_set("utf-8")

USING_NS_CC;

cocos2d::Scene * TitleScene::createScene()
{
	return TitleScene::create();
}

bool TitleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	creditLayer = Layer::create();
	this->addChild(creditLayer, 1, "creditLayer");

	SetCredit();
	for (auto obj:creditLayer->getChildren())
	{
		obj->setOpacity(0);
	}

	auto BGSP = Sprite::create(RES_ID("Title"));
	BGSP->setAnchorPoint(Vec2(0, 0));
	BGSP->setPosition(Vec2(0, 0));
	this->addChild(BGSP, 0, "Title");


	SetUI();

	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}

	lpAudioManager.SetSound("titleBGM.cks");

	//	操作イベントの作成
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(), this);

	this->scheduleUpdate();

	return true;
}

void TitleScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void TitleScene::update(float d)
{
	if (!GameMoveFlag)
	{
		auto oldButtonFlag = gameButtonFlag;
		auto touchFlag = false;

		//	Audioの更新
		lpAudioManager.update();

		for (auto checkKey : _oprtState->GetKeyList())
		{
			key[checkKey.first].first = checkKey.second;
		}

		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		cocos2d::Sprite* startButton = (cocos2d::Sprite*)nowScene->getChildByName("GameStart");
		cocos2d::Sprite* creditButton = (cocos2d::Sprite*)nowScene->getChildByName("credit");

		//	クレジット表記画面以外での処理
		if (!creditFlag)
		{
			//	プラットフォームごとのモード切替
			if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
			{
				if ((key[UseKey::K_UP].first && !key[UseKey::K_UP].second) || (key[UseKey::K_DOWN].first && !key[UseKey::K_DOWN].second))
				{
					if (gameButtonFlag)
					{
						gameButtonFlag = false;
					}
					else
					{
						gameButtonFlag = true;
					}
				}
			}
			else
			{
				if (_oprtState->firstTouch())
				{
					cocos2d::Rect spriteRect = cocos2d::Rect(startButton->getPosition().x - startButton->getContentSize().width / 2,
						startButton->getPosition().y - startButton->getContentSize().height / 2,
						startButton->getContentSize().width,
						startButton->getContentSize().height);
					if (spriteRect.containsPoint(_oprtState->GetTouchPoint()))
					{
						gameButtonFlag = true;
						touchFlag = true;
					}
					else
					{
						spriteRect = cocos2d::Rect(creditButton->getPosition().x - creditButton->getContentSize().width / 2,
							creditButton->getPosition().y - creditButton->getContentSize().height / 2,
							creditButton->getContentSize().width,
							creditButton->getContentSize().height);
						if (spriteRect.containsPoint(_oprtState->GetTouchPoint()))
						{
							gameButtonFlag = false;
							touchFlag = true;
						}
					}
				}
			}
			//	Buttonの明るさ切り替え
			if (gameButtonFlag != oldButtonFlag)
			{
				if (gameButtonFlag)
				{
					startButton->setColor(cocos2d::Color3B(255, 255, 255));
					creditButton->setColor(cocos2d::Color3B(150, 150, 150));
				}
				else
				{
					startButton->setColor(cocos2d::Color3B(150, 150, 150));
					creditButton->setColor(cocos2d::Color3B(255, 255, 255));
				}
			}
		}
		else
		{
			touchFlag = _oprtState->firstTouch();
		}


		auto fadeTime = 2.0f;

		if (key[UseKey::K_ENTER].first && !key[UseKey::K_ENTER].second || touchFlag)
		{
			//	ゲーム開始
			if (gameButtonFlag)
			{
				lpAudioManager.ResetAudio();
				lpAudioManager.SetSound("click");

				auto scene = GameMain::createScene();

				//Director::getInstance()->replaceScene(scene);
				GameMoveFlag = true;

				auto fade = TransitionFade::create(fadeTime, scene);
				Director::getInstance()->replaceScene(fade);
			}
			else
			{
				lpAudioManager.SetSound("click");
				auto TitleBG = nowScene->getChildByName("Title");
				if (creditFlag)
				{
					creditFlag = false;
					TitleBG->setColor(cocos2d::Color3B(255, 255, 255));
					SetUI();
					for (auto obj : creditLayer->getChildren())
					{
						obj->setOpacity(0);
					}
					gameButtonFlag = true;

				}
				else
				{
					creditFlag = true;
					TitleBG->setColor(cocos2d::Color3B(150, 150, 150));

					this->removeChildByName("logo");
					this->removeChildByName("GameStart");
					this->removeChildByName("credit");

					for (auto obj : creditLayer->getChildren())
					{
						obj->setOpacity(255);
					}
				}
			}
		}

		for (auto itrKey : UseKey())
		{
			key[itrKey].second = key[itrKey].first;
		}
	}
}

void TitleScene::SetCredit()
{
	//	間の補正用
	int cor = 10;
#if CK_PLATFORM_ANDROID
	SetCrText("お借りした素材等", 60, cor, T_Center);
	cor += 50;
	SetCrText("Cricket Audio", 30, cor, T_L);
	SetCrText("www.crickettechnology.com", 20, cor, T_L);
	SetCrText("Effekseer", 30, cor, T_L);
	SetCrText("https://effekseer.github.io/jp/", 20, cor, T_L);
	SetCrText("itch.io", 30, cor, T_L);
	SetCrText("https://itch.io/game-assets/free", 20, cor, T_L);
	SetCrText("KENNEY", 30, cor, T_L);
	SetCrText("https://www.kenney.nl/assets/shooting-gallery", 20, cor, T_L);
	SetCrText("晴耕雨読記", 30, cor, T_L);
	SetCrText("http://10grove.moo.jp/blog/post-840/", 20, cor, T_L);

	cor = 100;

	SetCrText("ゆるドラシル RPGツクール素材提供サイト", 30, cor, T_R);
	SetCrText("http://yurudora.com/tkool/", 20, cor, T_R);
	SetCrText("小樽総合デザイン事務局", 30, cor, T_R);
	SetCrText("https://otarunet.com/it/webdesign/comic-material-effect01/", 20, cor, T_R);
	SetCrText("魔王魂", 30, cor, T_R);
	SetCrText("https://maoudamashii.jokersounds.com/", 20, cor, T_R);
	SetCrText("効果音ラボ", 30, cor, T_R);
	SetCrText("https://soundeffect-lab.info/", 20, cor, T_R);
	SetCrText("まるもじフォント(二コモジ)配布所", 30, cor, T_R);
	SetCrText("http://nicofont.pupu.jp/nicomoji-plus.html", 20, cor, T_R);
#else
	SetCrText(u8"お借りした素材等", 60, cor, T_Center);
	cor += 50;
	SetCrText("Cricket Audio", 30, cor, T_L);
	SetCrText("www.crickettechnology.com", 20, cor, T_L);
	SetCrText("Effekseer", 30, cor, T_L);
	SetCrText("https://effekseer.github.io/jp/", 20, cor, T_L);
	SetCrText("itch.io", 30, cor, T_L);
	SetCrText("https://itch.io/game-assets/free", 20, cor, T_L);
	SetCrText("KENNEY", 30, cor, T_L);
	SetCrText("https://www.kenney.nl/assets/shooting-gallery", 20, cor, T_L);
	SetCrText(u8"晴耕雨読記", 30, cor, T_L);
	SetCrText("http://10grove.moo.jp/blog/post-840/", 20, cor, T_L);

	cor = 100;

	SetCrText(u8"ゆるドラシル RPGツクール素材提供サイト", 30, cor, T_R);
	SetCrText("http://yurudora.com/tkool/", 20, cor, T_R);
	SetCrText(u8"小樽総合デザイン事務局", 30, cor, T_R);
	SetCrText("https://otarunet.com/it/webdesign/comic-material-effect01/", 20, cor, T_R);
	SetCrText(u8"魔王魂", 30, cor, T_R);
	SetCrText("https://maoudamashii.jokersounds.com/", 20, cor, T_R);
	SetCrText(u8"効果音ラボ", 30, cor, T_R);
	SetCrText("https://soundeffect-lab.info/", 20, cor, T_R);
	SetCrText(u8"まるもじフォント(二コモジ)配布所", 30, cor, T_R);
	SetCrText("http://nicofont.pupu.jp/nicomoji-plus.html", 20, cor, T_R);
#endif
}

void TitleScene::SetCrText(std::string str, int size, int &cor, TextDIR dir)
{
	cor += 40;
	auto scSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	CCLabelTTF *text = CCLabelTTF::create(str, "Arial", size);

	auto textPos = cocos2d::Vec2(scSize.width / 2, scSize.height - cor);
	if (dir == TextDIR::T_L)
	{
		textPos = cocos2d::Vec2(scSize.width / 4, scSize.height - cor);
	}
	else if (dir == TextDIR::T_R)
	{
		textPos = cocos2d::Vec2(scSize.width - scSize.width / 3.5, scSize.height - cor);
	}

	text->setPosition(textPos);
	creditLayer->addChild(text);
}

void TitleScene::SetUI()
{
	auto scSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	auto BGSP = Sprite::create(RES_ID("logo"));
	BGSP->setPosition(scSize.width / 2, scSize.height / 2 + 50);
	this->addChild(BGSP, 1, "logo");

	BGSP = Sprite::create(RES_ID("GameStart"));
	BGSP->setPosition(scSize.width / 2, scSize.height / 2 - 120);
	this->addChild(BGSP, 1, "GameStart");

	BGSP = Sprite::create(RES_ID("credit"));
	BGSP->setPosition(scSize.width / 2, scSize.height / 2 - 120 - BGSP->getContentSize().height * 1.2);
	BGSP->setColor(cocos2d::Color3B(150, 150, 150));
	this->addChild(BGSP, 1, "credit");
}

