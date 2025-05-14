#pragma once
#include "../core/Singleton.h"
#include "../core/Texture.h"
#include "../core/Font.h"
#include "../core/Sound.h"
#include "../core/Music.h"
#include <string>
#include <unordered_map>
#include <memory>

class ResourceManager : public Singleton<ResourceManager>
{
public:
    void LoadResources();
    void UnloadResources();

    template<typename T>
    T* GetResource(const std::string& path);

    template<typename T>
    T* LoadResource(const std::string& path);

    template<typename T>
    void UnloadResource(const std::string& path);

private:
    std::unordered_map<std::string, std::shared_ptr<RTexture>> m_textures;
    std::unordered_map<std::string, std::shared_ptr<RFont>> m_fonts;
    std::unordered_map<std::string, std::shared_ptr<RSound>> m_sounds;
    std::unordered_map<std::string, std::shared_ptr<RMusic>> m_music;
};

template<typename T>
inline T* ResourceManager::GetResource(const std::string& path)
{
	if constexpr (std::is_same_v<T, RTexture>)
	{
		auto it = m_textures.find(path);
		if (it != m_textures.end())
		{
			return it->second.get();
		}
	}
	else if constexpr (std::is_same_v<T, RFont>)
	{
		auto it = m_fonts.find(path);
		if (it != m_fonts.end())
		{
			return it->second.get();
		}
	}
	else if constexpr (std::is_same_v<T, RSound>)
	{
		auto it = m_sounds.find(path);
		if (it != m_sounds.end())
		{
			return it->second.get();
		}
	}
	else if constexpr (std::is_same_v<T, RMusic>)
	{
		auto it = m_music.find(path);
		if (it != m_music.end())
		{
			return it->second.get();
		}
	}
	return LoadResource<T>(path);
}

template<typename T>
inline T* ResourceManager::LoadResource(const std::string& path)
{
	if constexpr (std::is_same_v<T, RTexture>)
	{
		auto it = m_textures.find(path);
		if (it != m_textures.end())
		{
			return it->second.get();
		}
		else
		{
			auto texture = std::make_shared<RTexture>(path);
			m_textures[path] = texture;
			return texture.get();
		}
	}
	else if constexpr (std::is_same_v<T, RFont>)
	{
		auto it = m_fonts.find(path);
		if (it != m_fonts.end())
		{
			return it->second.get();
		}
		else
		{
			auto font = std::make_shared<RFont>(path);
			m_fonts[path] = font;
			return font.get();
		}
	}
	else if constexpr (std::is_same_v<T, RSound>)
	{
		auto it = m_sounds.find(path);
		if (it != m_sounds.end())
		{
			return it->second.get();
		}
		else
		{
			auto sound = std::make_shared<RSound>(path);
			m_sounds[path] = sound;
			return sound.get();
		}
	}
	else if constexpr (std::is_same_v<T, RMusic>)
	{
		auto it = m_music.find(path);
		if (it != m_music.end())
		{
			return it->second.get();
		}
		else
		{
			auto music = std::make_shared<RMusic>(path);
			m_music[path] = music;
			return music.get();
		}
	}
	return nullptr;
}

template<typename T>
inline void ResourceManager::UnloadResource(const std::string& path)
{
	if constexpr (std::is_same_v<T, Texture>)
	{
		auto it = m_textures.find(path);
		if (it != m_textures.end())
		{
			m_textures.erase(it);
		}
	}
	else if constexpr (std::is_same_v<T, Font>)
	{
		auto it = m_fonts.find(path);
		if (it != m_fonts.end())
		{
			m_fonts.erase(it);
		}
	}
	else if constexpr (std::is_same_v<T, Sound>)
	{
		auto it = m_sounds.find(path);
		if (it != m_sounds.end())
		{
			m_sounds.erase(it);
		}
	}
	else if constexpr (std::is_same_v<T, Music>)
	{
		auto it = m_music.find(path);
		if (it != m_music.end())
		{
			m_music.erase(it);
		}
	}
}
