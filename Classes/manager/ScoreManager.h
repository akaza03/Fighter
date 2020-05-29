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

	//	スコア関連
	int GetScore();
	void SetScore(int number);

	void PlusScore(int number);

	//	フィーバー関連
	float GetFeverCnt();
	void SetFeverCnt(float number);

	void PlusFeverCnt(float number);

	bool GetFever();
	void SetFever(bool flag);

	void update();

	void SetFeverNumber(cocos2d::Layer* layer);

private:
	ScoreManager();

	int score;				//	スコア
	float feverCount;		//	フィーバー用カウント
	bool feverFlag;			//	フィーバー中かどうか

	void feverUpdate();
	
	Number* number;

	Number* feverNumber;

	static ScoreManager* s_Instance;
};
