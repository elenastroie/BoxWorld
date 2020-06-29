#pragma once
#include "TextureManager.h"
#include <unordered_map>

class TextureManagerImpl final : public TextureManager
{
public:
    TextureManagerImpl() = default;
    TextureManagerImpl(const TextureManagerImpl&) = default;
    TextureManagerImpl(TextureManagerImpl&&) noexcept = default;
    TextureManagerImpl& operator=(const TextureManagerImpl&) = default;
    TextureManagerImpl& operator=(TextureManagerImpl&&) noexcept;

    void LoadTexture(const std::string&) override;
    const sf::Texture& GetTexture(const std::string&) override;

    ~TextureManagerImpl() override;

private:
    std::unordered_map<std::string, const sf::Texture*> m_loadedTextures;
};
