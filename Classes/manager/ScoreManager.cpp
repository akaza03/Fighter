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

void ScoreManager::ResetScore(cocos2d::Layer* layer)
{
	//layer->removeChildByName("enemyCounter");
}

void ScoreManager::update()
{
	number->setNumber(score);
}
