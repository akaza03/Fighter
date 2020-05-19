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

	//	map�f�[�^�̃p�X,map��ǉ����郌�C���[,�ǉ����̖��O
	void SetMap(const std::string &pass, cocos2d::Layer *addLayer, const std::string &name);
	//	�摜�p�X,�w�i��ǉ����郌�C���[
	void SetBackImage(const std::string &pass, cocos2d::Layer *addLayer);
	//	�L�����N�^�[�̃^�C�v,�L�����N�^�[��ǉ����郌�C���[,�L�����N�^�[��ǉ�����V�[��
	void SetChara(CharaType type, cocos2d::Layer *addLayer, cocos2d::Scene *scene);
	//	�摜�p�X,���W,�X�P�[��,�����x,�摜��ǉ����郌�C���[,�ǉ����̖��O
	void SetImage(const std::string &pass, cocos2d::Vec2 pos, float scale, float trans, cocos2d::Layer *addLayer, const std::string &name);
	//	���W,�^�C����T�����C���[
	int GetTile(cocos2d::Vec2 pos, cocos2d::TMXLayer * layer);

	//	�G�̎��S���ɐV���ɓG���o��������
	void SetEnemy(int charaID, DIR dir);

	cocos2d::Size GetMapSize();
private:
	MapMaker();

	int transEnemyID(int id);									//	�}�b�vID���G�l�~�[ID�ɕϊ�����

	cocos2d::Vec2 Ppos = cocos2d::Vec2(0, 0);

	cocos2d::Size mapSize = cocos2d::Size(0,0);
	cocos2d::TMXTiledMap* tiledMap;

	static MapMaker* s_Instance;
};

