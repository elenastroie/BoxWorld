#pragma once
#include<SFML/Graphics.hpp>
#include"Screen.h"

class MenuScreen final : public Screen
{
public:
    MenuScreen();
    MenuScreen(const MenuScreen& other) = default;
    MenuScreen(MenuScreen&& other) noexcept = default;
    MenuScreen& operator=(const MenuScreen&) = default;
    MenuScreen& operator=(MenuScreen&& other) = default;
    ScreenStatus Run(sf::RenderWindow&) override;
    ~MenuScreen() = default;

private:
    void SwitchOption(uint8_t);
    void DrawElements(sf::RenderWindow& window) const;
    void InitializeTexts();
    void LoadTextures();
    void LoadFont();

private:
    sf::Texture m_backgroundTexture;
    sf::Sprite background;
    sf::Font m_font;
    sf::Text m_playOption;
    sf::Text m_restartLevel;
    sf::Text m_exitOption;
    sf::Text m_multiplayerOption;
    sf::Text m_instructionsOption;
    sf::Text m_highscoreOption;


    static const int FONT_SIZE = 33;
};
