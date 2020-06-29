#include "stdafx.h"
#include "TextureManagerImpl.h"
#include <SFML/Graphics/Texture.hpp>

TextureManagerImpl& TextureManagerImpl::operator=(TextureManagerImpl&& other) noexcept
{
    std::swap(*this, other);
    return *this;
}

void TextureManagerImpl::LoadTexture(const std::string& textureName)
{
    const auto it = m_loadedTextures.find(textureName);
    if (it == m_loadedTextures.end())
    {
        const auto path = "Assets/Sprites/" + textureName;
        // ReSharper disable once CppNonReclaimedResourceAcquisition
        auto texture = new sf::Texture();
        if (!texture->loadFromFile(path))
        {
            throw std::exception(("Texture " + textureName + " couldn't be loaded.").c_str());
        }
        m_loadedTextures.try_emplace(textureName, texture);
    }
}

const sf::Texture& TextureManagerImpl::GetTexture(const std::string& textureName)
{
    const auto it = m_loadedTextures.find(textureName);
    if (it == m_loadedTextures.end())
    {
        throw std::exception(("Texture " + textureName + " was not loaded. Call TextureManager::LoadTexture first.").c_str());
    }

    return *it->second;
}

TextureManagerImpl::~TextureManagerImpl()
{
    for (const auto& pair : m_loadedTextures)
    {
        delete pair.second;
    }
}
