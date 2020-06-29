#pragma once
#include "Screen.h"
#include "ScreenStatus.h"
class PlayerInfoScreen final : public Screen
{
public:
    PlayerInfoScreen();
    PlayerInfoScreen(const PlayerInfoScreen& other) = default;
    PlayerInfoScreen(PlayerInfoScreen&& other) noexcept = default;
    PlayerInfoScreen& operator=(const PlayerInfoScreen&) = default;
    PlayerInfoScreen& operator=(PlayerInfoScreen&& other) = default;
    ScreenStatus Run(sf::RenderWindow&) override;
    ~PlayerInfoScreen() = default;
private:
    void DrawElements(sf::RenderWindow& window) const;
    void InitializeTexts();
    void LoadFont();
private:
    sf::Font m_font;
    sf::String m_playerInput;
    sf::Text m_playerText;
    sf::Text m_screenText;
    sf::Text m_warningText;

    static const int FONT_SIZE = 30;
    static const int MAX_LENGHT = 16;
};

