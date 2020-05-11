#pragma once
#include <map>
#include "cocos2d.h"

#define RES_ID(KEY) ResourceManager::GetInstance().GetID(KEY)

class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new ResourceManager();
		}
		return *s_Instance;
	}
	~ResourceManager();

	std::string GetID(std::string key);
	std::string SetID(std::string key,std::string filePass);
private:
	ResourceManager();
	void LoadInit();

	std::map<std::string, std::string> resMap;
	static ResourceManager* s_Instance;
};

