#pragma once
#include "cocos2d.h"
#include "unit/charaStruct.h"

class MapMaker
{
public:
	MapMaker();
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

	cocos2d::Size GetMapSize();
private:
	int transEnemyID(int id);									//	マップIDをエネミーIDに変換する

	cocos2d::Vec2 Ppos = cocos2d::Vec2(0, 0);

	cocos2d::Size mapSize = cocos2d::Size(0,0);
	cocos2d::TMXTiledMap* tiledMap;
};

