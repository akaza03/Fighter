#include "EffManager.h"
#include "ResourceManager.h"

EffManager* EffManager::s_Instance = nullptr;

EffManager::EffManager()
{
	//effectMng.reset(efk::EffectManager::create(cocos2d::Director::getInstance()->getVisibleSize()));
	//EffectListInit();
}

void EffManager::EffectListInit()
{
	//effectList[RES_ID("changeEff")] = efk::Effect::create(RES_ID("changeEff"));
	//effectList[RES_ID("hitEff")] = efk::Effect::create(RES_ID("hitEff"));
	//effectList[RES_ID("deathEff")] = efk::Effect::create(RES_ID("deathEff"));

	//for (auto &itr : effectList)
	//{
	//	itr.second->retain();
	//}
}


EffManager::~EffManager()
{
	//for (auto &itr : effectList)
	//{
	//	itr.second->release();
	//}
	//effectMng->release();
}

void EffManager::update(cocos2d::Camera* camera)
{
	//(*effectMng).update();
	////	カメラ関連の更新
	//(*effectMng).setCameraMatrix(camera->getViewMatrix());
	//(*effectMng).setProjectionMatrix(camera->getProjectionMatrix());
}

void EffManager::SetEffect(const char* pass, const char* layer, bool mask, cocos2d::Vec2 pos, int scale, bool playEnter)
{
	//auto effect = effectList[pass];

	//if (effect != nullptr)
	//{
	//	//effect->retain();

	//	auto emitter = efk::EffectEmitter::create(effectMng.get());
	//	emitter->setEffect(effect);
	//	emitter->setPlayOnEnter(true);
	//	emitter->setPosition(pos);
	//	emitter->setScale(scale);
	//	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	//	auto nowLayer = nowScene->getChildByName(layer);

	//	if (mask)
	//	{
	//		emitter->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1), true);
	//	}
	//	nowLayer->addChild(emitter, 0);
	//}
}
