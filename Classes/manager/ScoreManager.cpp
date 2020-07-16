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

	//	�X�R�A�̃Z�b�g
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
	//	�X�R�A�̌��������߂�
	while (num != 0)
	{
		num /= 10;
		digit++;
	}
	//	�����ɂ��␳�p
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
	//	�t�B�[�o�[�̏I��
	if (feverCount <= 0)
	{
		feverCount = 0;
		if (feverFlag)
		{
			//	�t�B�[�o�[�p�̉摜���\����
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
		//	�t�B�[�o�[�̊J�n
		if (feverCount >= 200)
		{
			//	�t�B�[�o�[�p�̉摜�\��
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

	//	�t�B�[�o�[�p�o�[�̍X�V
	auto layer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("UILayer");
	cocos2d::Sprite* FBar = (cocos2d::Sprite*) layer->getChildByName("feverBar");
	//	�ő�HP���猩�����݂�HP�̊���
	float Percent = feverCount / 200;
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