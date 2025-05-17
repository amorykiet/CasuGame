#include "ResourceManager.h"

void ResourceManager::LoadResources()
{
	// Load all resources if need
	// This function is empty because the resources are loaded on demand
	// when they are requested for the first time.
	// You can implement a preloading mechanism here if needed.
}

void ResourceManager::UnloadResources()
{
	for (auto& pair : m_textures)
	{
		pair.second.reset();
	}
	m_textures.clear();
	for (auto& pair : m_fonts)
	{
		pair.second.reset();
	}
	m_fonts.clear();
	for (auto& pair : m_sounds)
	{
		pair.second.reset();
	}
	m_sounds.clear();
	for (auto& pair : m_music)
	{
		pair.second.reset();
	}
	m_music.clear();
	for (auto& pair : m_shaders)
	{
		pair.second.reset();
	}
}