#include "MapMaker.h"
#include "unit/Player.h"
#include "unit/Enemy.h"

MapMaker* MapMaker::s_Instance = nullptr;


MapMaker::MapMaker()
{
}


MapMaker::~MapMaker()
{
}

MapMaker * MapMaker::create()
{
	return new MapMaker();
}

void MapMaker::SetMap(const std::string & pass, cocos2d::Layer *addLayer, const std::string & name)
{
	tiledMap = cocos2d::TMXTiledMap::create(pass);
	if (tiledMap != nullptr)
	{
		addLayer->addChild(tiledMap, 1, name);
		mapSize = tiledMap->getContentSize();
	}
}

void MapMaker::SetBackImage(const std::string & pass, cocos2d::Layer * addLayer)
{
	auto spNode = cocos2d::SpriteBatchNode::create(pass);
	if (spNode != nullptr)
	{
		addLayer->addChild(spNode, 0);
		for (int i = 0; i <= 5; i++)
		{
			auto BGSP = cocos2d::Sprite::createWithTexture(spNode->getTexture());
			//	アンカーポイントを真ん中から左下に変更
			BGSP->setAnchorPoint(cocos2d::Vec2(0, 0));
			BGSP->setPosition(cocos2d::Vec2(BGSP->getContentSize().width * i, 0));
			spNode->addChild(BGSP);
		}
	}
}

void MapMaker::SetChara(CharaType type, cocos2d::Layer * addLayer, cocos2d::Scene *scene)
{
	if (tiledMap != nullptr)
	{
		if (type == CharaType::PLAYER)
		{
			auto player = Player::create();
			//	playerLayerを読み込み、プレイヤーの座標を決定する
			cocos2d::TMXLayer* layer = tiledMap->getLayer("player");
			//	プレイヤーの座標
			for (int y = 0; y < layer->getLayerSize().height; y++)
			{
				for (int x = 0; x < layer->getLayerSize().width; x++)
				{
					if (layer->getTileGIDAt(cocos2d::Vec2(x, y)) != 0)
					{
						Ppos = cocos2d::Vec2(x * layer->getMapTileSize().width + layer->getMapTileSize().height / 2,
							layer->getLayerSize().height * layer->getMapTileSize().height - y * layer->getMapTileSize().height - layer->getMapTileSize().height / 2);
						layer->removeFromParentAndCleanup(true);
					}
				}
			}

			if (player->SetInit(0, Ppos, 1000, 3, DIR::RIGHT, scene))
			{
				addLayer->addChild(player, 0, "player");
			}
		}
		else if (type == CharaType::ENEMY)
		{
			cocos2d::TMXLayer* eLayer = tiledMap->getLayer("enemy");
			//	エネミーの座標
			cocos2d::Vec2 Epos;
			for (int y = 0; y < eLayer->getLayerSize().height; y++)
			{
				for (int x = 0; x < eLayer->getLayerSize().width; x++)
				{
					auto tileID = GetTile(cocos2d::Vec2(x, y), eLayer);
					if (tileID != 0)
					{
						Epos = cocos2d::Vec2(x * eLayer->getMapTileSize().width + eLayer->getMapTileSize().height / 2,
							eLayer->getLayerSize().height * eLayer->getMapTileSize().height - y * eLayer->getMapTileSize().height - eLayer->getMapTileSize().height / 2);
						auto Enemy = Enemy::create();

						//	敵のIDによってステータスを変更しながら登録
						auto enemyID = transEnemyID(tileID);

						DIR dir = DIR::LEFT;

						if (Epos.x < Ppos.x)
						{
							dir = DIR::RIGHT;
						}

						auto hp = 1;
						switch (enemyID)
						{
						case 0:
							hp = 1;
							break;
						case 2:
							hp = 3;
							enemyID = 1;
							break;
						default:
							break;
						}

						if (Enemy->SetInit(enemyID, Epos, hp, 16, dir, scene))
						{
							addLayer->addChild(Enemy, 0);
						}
					}
				}
			}
			eLayer->removeFromParentAndCleanup(true);
		}
	}
}

void MapMaker::SetImage(const std::string & pass, cocos2d::Vec2 pos, float scale, float trans, cocos2d::Layer * addLayer, const std::string & name)
{
	auto image = cocos2d::Sprite::create(pass);
	if (image != nullptr)
	{
		image->setPosition(pos);
		image->setScale(scale);
		image->setOpacity(trans);
		addLayer->addChild(image, 1, name);
	}
}

int MapMaker::GetTile(cocos2d::Vec2 pos, cocos2d::TMXLayer * layer)
{
	//	取得場所が画面外の場合は0を返す
	if (pos.x > 0 && pos.x < layer->getLayerSize().width
		&&	pos.y > 0 && pos.y < layer->getLayerSize().height)
	{
		//	タイルの取得
		return layer->getTileGIDAt(pos);
	}
	return 0;
}

void MapMaker::SetEnemy(int charaID, DIR dir)
{
	auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
	auto layer = nowScene->getChildByName("EMLayer");

	auto enemy = Enemy::create();
	auto Epos = cocos2d::Vec2(tiledMap->getTileSize().width / 2,
		5 * tiledMap->getTileSize().height - tiledMap->getTileSize().height / 2);

	if (dir == DIR::LEFT)
	{
		Epos = cocos2d::Vec2(tiledMap->getMapSize().width * tiledMap->getTileSize().width - tiledMap->getTileSize().width / 2,
			5 * tiledMap->getTileSize().height - tiledMap->getTileSize().height / 2);
	}

	auto hp = 1;
	switch (charaID)
	{
	case 0:
		hp = 1;
		break;
	case 1:
		hp = 3;
		break;
	default:
		break;
	}

	if (enemy->SetInit(charaID, Epos, hp, 16, dir, nowScene))
	{
		layer->addChild(enemy, 0);
		//	カメラのセット
		enemy->setCameraMask(static_cast<int>(cocos2d::CameraFlag::USER1), true);
		//	enemyのupdateを走らせる
		enemy->scheduleUpdate();
	}
}

cocos2d::Size MapMaker::GetMapSize()
{
	if (tiledMap != nullptr)
	{
		return mapSize;
	}
	return cocos2d::Size(0);
}

int MapMaker::transEnemyID(int id)
{
	return id - 1;
}
