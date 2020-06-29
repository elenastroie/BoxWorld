#include "stdafx.h"
#include "TextureManager.h"

TextureManager* TextureManager::s_instance = nullptr;

TextureManager::TextureManager()
{
    s_instance = this;
}

void TextureManager::LoadAllTextures(const std::vector<std::string>& textures)
{
    for (const auto& texture : textures)
    {
        LoadTexture(texture);
    }
}

TextureManager& TextureManager::GetInstance()
{
    return *s_instance;
}
