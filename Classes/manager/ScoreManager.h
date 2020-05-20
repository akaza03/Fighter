#pragma once
#include "cocos2d.h"
#include "UIClass/Number.h"

#define lpScoreMng ScoreManager::GetInstance()

class ScoreManager
{
public:
	static ScoreManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new ScoreManager();
		}
		return *s_Instance;
	}
	~ScoreManager();

	void InitNumber();

	void SetNumber(cocos2d::Layer* layer);

	int GetScore();
	void SetScore(int number);

	void PlusScore(int number);
	void ResetScore(cocos2d::Layer* layer);

	void update();

private:
	ScoreManager();

	int score;				//	ÉXÉRÉA
	
	Number* number;

	static ScoreManager* s_Instance;
};
