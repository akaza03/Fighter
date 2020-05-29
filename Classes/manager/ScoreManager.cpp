#include "ScoreManager.h"

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

	number = Number::create();
	number->setPosition(confScSize.width - 60, confScSize.height - 40);
	number->setSpan(40);
	number->setPrefix("number");

	//	デバッグ用
	feverNumber = Number::create();
	feverNumber->setPosition(120, confScSize.height - 40);
	feverNumber->setSpan(40);
	feverNumber->setPrefix("number");
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
	if (feverCount <= 0)
	{
		feverCount = 0;
		if (feverFlag)
		{
			feverFlag = false;
		}
	}
	if (!feverFlag)
	{

		if (feverCount >= 100)
		{
			feverCount = 100;
			feverFlag = true;
		}
	}

	//	デバッグ用
	feverNumber->setNumber(feverCount);
}