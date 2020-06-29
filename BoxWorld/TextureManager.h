#pragma once
#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
public:
    TextureManager();
    TextureManager(const TextureManager&) = default;
    TextureManager(TextureManager&&) noexcept = default;
    TextureManager& operator=(const TextureManager&) = default;
    TextureManager& operator=(TextureManager&&) noexcept = default;

    virtual void LoadTexture(const std::string&) = 0;
    void LoadAllTextures(const std::vector<std::string>&);
    virtual const sf::Texture& GetTexture(const std::string&) = 0;
    virtual ~TextureManager() = default;
    static TextureManager& GetInstance();
protected:
    static TextureManager* s_instance;
};
