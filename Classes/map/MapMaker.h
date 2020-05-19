#pragma once
#include "cocos2d.h"
#include "unit/charaStruct.h"

#define lpMapMaker MapMaker::GetInstance()

class MapMaker
{
public:
	static MapMaker& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new MapMaker();
		}
		return *s_Instance;
	}
	~MapMaker();

	static MapMaker* create();

	//	mapデータのパス,mapを追加するレイヤー,追加時の名前
	void SetMap(const std::string &pass, cocos2d::Layer *addLayer, const std::string &name);
	//	画像パス,背景を追加するレイヤー
	void SetBackImage(const std::string &pass, cocos2d::Layer *addLayer);
	//	キャラクターのタイプ,キャラクターを追加するレイヤー,キャラクターを追加するシーン
	void SetChara(CharaType type, cocos2d::Layer *addLayer, cocos2d::Scene *scene);
	//	画像パス,座標,スケール,透明度,画像を追加するレイヤー,追加時の名前
	void SetImage(const std::string &pass, cocos2d::Vec2 pos, float scale, float trans, cocos2d::Layer *addLayer, const std::string &name);
	//	座標,タイルを探すレイヤー
	int GetTile(cocos2d::Vec2 pos, cocos2d::TMXLayer * layer);

	//	敵の死亡時に新たに敵を出現させる
	void SetEnemy(int charaID, DIR dir);

	cocos2d::Size GetMapSize();
private:
	MapMaker();

	int transEnemyID(int id);									//	マップIDをエネミーIDに変換する

	cocos2d::Vec2 Ppos = cocos2d::Vec2(0, 0);

	cocos2d::Size mapSize = cocos2d::Size(0,0);
	cocos2d::TMXTiledMap* tiledMap;

	static MapMaker* s_Instance;
};

