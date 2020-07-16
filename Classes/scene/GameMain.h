#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <memory>
#include "UIClass/Number.h"
#include "input/OprtKey.h"
#include "input/UseKey.h"
#include "ck/sound.h"

 //	�V�X�e���p�L�[(now,old)
using sysKey = std::map <UseKey, std::pair<bool, bool>>;

enum LayerNumber
{
	BG,						//	�o�b�N�O���E���h�p���C���[
	PL,						//	�v���C���[&�U���p���C���[
	EM,						//	�G�l�~�[&�U���p���C���[
	BW,						//	��ʂ��Â����郌�C���[(�|�[�Y��ʂȂ�)
	UI,						//	UI�p���C���[
	FG,						//	�t�����g�O���E���h�p���C���[
	DB,						//	�f�o�b�O�p���C���[
	LAYER_MAX
};

class GameMain : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

private:
	cocos2d::Layer * BGLayer;				//	�o�b�N�O���E���h�p���C���[
	cocos2d::Layer * PLLayer;				//	�v���C���[�p���C���[
	cocos2d::Layer * EMLayer;				//	�G�l�~�[�p���C���[
	cocos2d::Layer * BWLayer;				//	��ʂ��Â����郌�C���[(�|�[�Y��ʂȂ�)
	cocos2d::Layer * UILayer;				//	UI�p���C���[
	cocos2d::Layer * FGLayer;				//	�t�����g�O���E���h�p���C���[
	cocos2d::Layer * DBLayer;				//	�f�o�b�O�p���C���[

	cocos2d::Camera* _camera;

	OprtState *_oprtState;					//	�V�X�e���p�̑��쐧��
	sysKey key;

	Number* time;							//	���ԗp

	void update(float d);

	void SetUI();

	//	�摜�̔z�u����(�摜�{��,�o�^��,���W,�����x)
	void SetImage(cocos2d::Sprite* sp, const char* name, cocos2d::Vec2 pos, int op);

	void cameraUpdate();
	void keyUpdate();
	void timeUpdate();

	void startCounter(float d);				//	�Q�[���J�n�̃J�E���g���n�߂鏈��

	void startSchedule(float d);			//	�J�n���̃J�E���g�I����ɓ����o��update����
	void endSchedule();						//	�Q�[���I�����ɂ��ꂼ���update���~�߂鏈��

	void screenUpdate();					//	�Q�[���I������|�[�Y���̉�ʏ���
	void pause(cocos2d::Layer* layer);		//	�|�[�Y
	void darkScreen();						//	�|�[�Y���̉�ʂ̈Ó]����

	void ResultScene(float d);				//	���U���g����
	void gameEnd();							//	�Q�[�����I�����A�^�C�g���ɖ߂鏈��

	cocos2d::Size confScSize;				//	�ݒ��̉�ʃT�C�Y
	cocos2d::Size scSize;					//	���ۂ̉�ʃT�C�Y

	int timeCount;							//	�c�莞��

	float resultTime;						//	���U���g�p���Ԍv��

	Number *startNumber;					//	�X�^�[�g���̃J�E���g�p
	bool startFlag;							//	�X�^�[�g���̃J�E���g�I���t���O

	bool pauseFlag;
	bool gameEndFlag;
	
	bool shakeLR;							//	��ʂ�h�炷�ۂ̍��E�t���O
	int shakeTime;							//	��ʂ�h�炷�ۂ̎��Ԍv���p
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
};

#endif // __HELLOWORLD_SCENE_H__
