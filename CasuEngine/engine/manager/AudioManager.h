#pragma once

#include "../core/Singleton.h"
#include "../core/Music.h"

class AudioManager : public Singleton<AudioManager>
{
public:
	void Init();
	void Update();
	void Close();
	void PlaySound(const std::string& path);
	void PlayMusic(const std::string& path);
	bool IsPlayingMusic();
	void StopMusic();
	void PauseMusic();
	void ResumeMusic();

private:
	RMusic* m_currentMusic = nullptr;
};