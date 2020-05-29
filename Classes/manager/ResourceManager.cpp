#include "ResourceManager.h"

ResourceManager *ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager()
{
	LoadInit();
}

ResourceManager::~ResourceManager()
{
}
std::string ResourceManager::GetID(std::string key)
{
	if (resMap.find(key) == resMap.end())
	{
		return "null";
	}
	return resMap[key];
}

std::string ResourceManager::SetID(std::string key, std::string filePass)
{
	if (resMap.find(key) == resMap.end())
	{
		resMap[key] = filePass;
	}
	return resMap[key];
}

void ResourceManager::LoadInit()
{
	//	�^�C�g���摜
	SetID("logo", "image/logo.png");
	SetID("GameStart", "image/UI/GameStart.png");
	SetID("GameClear", "image/UI/GameClear.png");
	SetID("GameOver", "image/UI/GameOver.png");
	SetID("credit", "image/UI/credit.png");
	//	���j�b�g�摜
	SetID("p0unit", "image/player/00-unit.png");
	SetID("e0unit", "image/enemy/00-unit.png");
	SetID("e1unit", "image/enemy/01-unit.png");
	SetID("e2unit", "image/enemy/02-unit.png");
	SetID("e3unit", "image/enemy/03-unit.png");
	//	�w�i
	SetID("Title", "image/title(kari).png");
	//	�G�t�F�N�g
	SetID("changeEff", "effect/Laser01.efk");
	SetID("hitEff", "effect/hit.efk");
	SetID("deathEff", "effect/death.efk");

	//	�t�B�[�o�[�p�o�[
	SetID("feverBase", "image/UI/BarBase.png");
	SetID("feverBar", "image/UI/Bar.png");
	SetID("feverFront", "image/UI/BarFront.png");
}