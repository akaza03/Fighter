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

		if (feverCount >= 300)
		{
			feverCount = 300;
			feverFlag = true;
		}
	}

	//	�t�B�[�o�[�p�o�[�̍X�V
	auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
	cocos2d::Sprite* FBar = (cocos2d::Sprite*) layer->getChildByName("feverBar");
	//	�ő�HP���猩�����݂�HP�̊���
	float Percent = feverCount / 300;
	//	��U�߂�
	auto oldSize = FBar->getScaleX();
	float ImageSizeX = FBar->getContentSize().width * (1 - oldSize);
	FBar->setPosition(FBar->getPosition().x + ImageSizeX / 2, FBar->getPosition().y);

	//	HP�o�[�̊g��k��(X���W�̂�)
	FBar->setScale(Percent, 1);
	//	�����������̈ʒu�␳
	ImageSizeX = FBar->getContentSize().width * (1 - Percent);
	FBar->setPosition(FBar->getPosition().x - ImageSizeX / 2, FBar->getPosition().y);
}