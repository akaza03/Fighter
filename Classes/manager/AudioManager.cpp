#include "cricket/inc/ck/ck.h"
#include "cricket/inc/ck/config.h"
#include "cricket/inc/ck/bank.h"
#include "cricket/inc/ck/sound.h"
#include "AudioManager.h"

AudioManager* AudioManager::s_Instance = nullptr;

AudioManager::AudioManager()
{
#if CK_PLATFORM_ANDROID
	//CkConfig config(cocos2d::JniHelper::getEnv(), cocos2d::JniHelper::getActivity());
#else
	CkConfig config;
	CkInit(&config);
#endif

	AudioListInit();
}


AudioManager::~AudioManager()
{
	for (auto &itr : audioList)
	{
		itr.second->destroy();
	}
	audioList.erase(audioList.begin(), audioList.end());

	CkShutdown();
}

void AudioManager::AudioListInit()
{
	//	まずここで音を登録
	SetStream("titleBGM.cks", SoundType::S_BGM);
	SetStream("music.cks", SoundType::S_BGM);
	SetStream("clearBGM.cks", SoundType::S_BGM);
	SetStream("gameoverBGM.cks", SoundType::S_BGM);
	SetBank("Sound.ckb", "click", SoundType::S_SE);
	SetBank("Sound.ckb", "shot", SoundType::S_SE);
	SetBank("Sound.ckb", "damage", SoundType::S_SE);
}

void AudioManager::update()
{
	CkUpdate();
}

void AudioManager::SetSound(const std::string name)
{
	auto sound = audioList[name];
	if (sound != nullptr)
	{
		//sound->play();
	}
}

void AudioManager::StopSound(const std::string name)
{
	auto sound = audioList[name];
	if (sound != nullptr)
	{
		sound->stop();
	}
}

void AudioManager::ResetAudio()
{
	for (auto &itr : audioList)
	{
		itr.second->stop();
	}
}

void AudioManager::PauseAudio()
{
	CkSuspend();
}

void AudioManager::ReStartAudio()
{
	CkResume();
}


void AudioManager::SetBank(const std::string &name, const std::string &soundName, SoundType type)
{
	std::string pass;
#if CK_PLATFORM_ANDROID
	if (type == SoundType::S_BGM)
	{
		pass = "Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Audio/SE/" + name;
	}
#else
	if (type == SoundType::S_BGM)
	{
		pass = "Resources/Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Resources/Audio/SE/" + name;
	}
#endif
	//	ckbファイルの指定
	CkBank* bank = CkBank::newBank(pass.c_str());
	if (bank != nullptr)
	{
		//	再生したい音の名前を指定
		CkSound* sound = CkSound::newBankSound(bank, soundName.c_str());
		if (sound != nullptr)
		{
			audioList[soundName] = sound;
		}
	}
}

void AudioManager::SetStream(const std::string &name, SoundType type)
{
	std::string pass;
#if CK_PLATFORM_ANDROID
	if (type == SoundType::S_BGM)
	{
		pass = "Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Audio/SE/" + name;
	}
#else
	if (type == SoundType::S_BGM)
	{
		pass = "Resources/Audio/BGM/" + name;
	}
	else if (type == SoundType::S_SE)
	{
		pass = "Resources/Audio/SE/" + name;
	}
#endif

	CkSound* _music = CkSound::newStreamSound(pass.c_str());
	if (_music != nullptr)
	{
		_music->setLoopCount(-1);
		audioList[name] = _music;
	}
}
