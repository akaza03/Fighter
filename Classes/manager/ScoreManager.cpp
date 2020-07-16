#include "ScoreManager.h"
#include "AudioManager.h"

ScoreManager* ScoreManager::s_Instance = nullptr;

ScoreManager::ScoreManager()
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::InitNumber()
{
	auto confScSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	//	スコアのセット
	number = Number::create();
	number->setPosition(confScSize.width - 60, confScSize.height - 40);
	number->setSpan(40);
	number->setPrefix("number");
}

void ScoreManager::SetNumber(cocos2d::Layer* layer)
{
	layer->addChild(number, 1, "enemyCounter");
}

int ScoreManager::GetScore()
{
	return score;
}

void ScoreManager::SetScore(int number)
{
	score = number;
}

void ScoreManager::PlusScore(int number)
{
	score += number;
}

void ScoreManager::ResultScore()
{
	auto confScSize = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
	
	auto num = score;
	int digit = -1;
	//	スコアの桁数を求める
	while (num != 0)
	{
		num /= 10;
		digit++;
	}
	//	桁数による補正用
	int dis = 40;

	number->setPosition(confScSize.width / 2 + dis * digit, confScSize.height / 2);
	number->setScale(2);
}

float ScoreManager::GetFeverCnt()
{
	return feverCount;
}

void ScoreManager::SetFeverCnt(float number)
{
	feverCount = number;
}

void ScoreManager::PlusFeverCnt(float number)
{
	if (!feverFlag || number <= 0)
	{
		feverCount += number;
	}
}

bool ScoreManager::GetFever()
{
	return feverFlag;
}

void ScoreManager::SetFever(bool flag)
{
	feverFlag = flag;
}

void ScoreManager::SetFeverNumber(cocos2d::Layer* layer)
{
	layer->addChild(feverNumber, 1, "enemyCounter");
}


void ScoreManager::update()
{
	if (score < 0)
	{
		score = 0;
	}
	number->setNumber(score);
	feverUpdate();
}

void ScoreManager::feverUpdate()
{
	//	フィーバーの終了
	if (feverCount <= 0)
	{
		feverCount = 0;
		if (feverFlag)
		{
			//	フィーバー用の画像を非表示に
			auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
			cocos2d::Sprite* feverSp = (cocos2d::Sprite*) layer->getChildByName("fever");
			feverSp->setOpacity(0);
			cocos2d::Sprite* fLineSp = (cocos2d::Sprite*) layer->getChildByName("fLine");
			fLineSp->setOpacity(0);

			feverFlag = false;
		}
	}
	if (!feverFlag)
	{
		//	フィーバーの開始
		if (feverCount >= 200)
		{
			//	フィーバー用の画像表示
			auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
			cocos2d::Sprite* feverSp = (cocos2d::Sprite*) layer->getChildByName("fever");
			feverSp->setOpacity(255);
			cocos2d::Sprite* fLineSp = (cocos2d::Sprite*) layer->getChildByName("fLine");
			fLineSp->setOpacity(255);

			feverCount = 200;
			lpAudioManager.SetSound("fever");
			feverFlag = true;
		}
	}

	//	フィーバー用バーの更新
	auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
	cocos2d::Sprite* FBar = (cocos2d::Sprite*) layer->getChildByName("feverBar");
	//	最大HPから見た現在のHPの割合
	float Percent = feverCount / 200;
	//	一旦戻す
	auto oldSize = FBar->getScaleX();
	float ImageSizeX = FBar->getContentSize().width * (1 - oldSize);
	FBar->setPosition(FBar->getPosition().x + ImageSizeX / 2, FBar->getPosition().y);

	//	HPバーの拡大縮小(X座標のみ)
	FBar->setScale(Percent, 1);
	//	増減した分の位置補正
	ImageSizeX = FBar->getContentSize().width * (1 - Percent);
	FBar->setPosition(FBar->getPosition().x - ImageSizeX / 2, FBar->getPosition().y);
}