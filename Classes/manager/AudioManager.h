#pragma once
#include <memory>
#include <cocos2d.h>

class CkSound;

#define lpAudioManager AudioManager::GetInstance()

enum SoundType
{
	S_BGM,
	S_SE,
	S_MAX
};

using AudioList = std::map < std::string, CkSound* >;

class AudioManager
{
public:
	static AudioManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AudioManager();
		}
		return *s_Instance;
	}
	~AudioManager();

	void update();

	//	音の再生(ストリーミングの場合はファイル名、オンメモリの場合はサウンド名)
	void SetSound(const std::string name);

	//	音を全停止(Scene切り替え時などに呼ぶ)
	void ResetAudio();

	//	指定した音を停止させる
	void StopSound(const std::string name);

	//	バックグラウンド時などBGMを一時停止させる
	void PauseAudio();

	//	BGMを再開させる
	void ReStartAudio();

private:
	AudioManager();
	static AudioManager* s_Instance;

	void AudioListInit();																	//	ファイルの初回一括読み込み
	void SetBank(const std::string &name, const std::string &soundName, SoundType type);	//	オンメモリ再生
	void SetStream(const std::string &name, SoundType type);								//	ストリーミング再生

	AudioList audioList;
};

