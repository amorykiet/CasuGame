#include "AudioManager.h"
#include "ResourceManager.h"
#include "../core/Sound.h"
#include "../core/Music.h"
#include "../core/AudioDevice.h"

void AudioManager::Init()
{
	RAudioDevice::Init();
}

void AudioManager::Update()
{
	if (m_currentMusic)
	{
		m_currentMusic->Update();
	}
}

void AudioManager::Close()
{
	RAudioDevice::Close();
}

void AudioManager::PlaySound(const std::string& path)
{
	RSound* sound = ResourceManager::GetInstance()->GetResource<RSound>(path);
	if (sound)
	{
		sound->Play();
	}
}

void AudioManager::PlayMusic(const std::string& path)
{
	RMusic* music = ResourceManager::GetInstance()->GetResource<RMusic>(path);
	if (music != nullptr)
	{
		music->Play();
		m_currentMusic = music;
	}
}

bool AudioManager::IsPlayingMusic()
{
	if (m_currentMusic)
	{
		return m_currentMusic->IsPlaying();
	}
	return false;
}

void AudioManager::StopMusic()
{
	if (m_currentMusic)
	{
		m_currentMusic->Stop();
	}
}

void AudioManager::PauseMusic()
{
	if (m_currentMusic)
	{
		m_currentMusic->Pause();
	}
}

void AudioManager::ResumeMusic()
{
	if (m_currentMusic)
	{
		m_currentMusic->Resume();
	}
}


