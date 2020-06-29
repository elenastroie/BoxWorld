#pragma once
#include<SFML/Graphics.hpp>
#include"Screen.h"
class HighscoreScreen final : public Screen
{
public:
    HighscoreScreen();
    HighscoreScreen(const HighscoreScreen& other) = default;
    HighscoreScreen(HighscoreScreen&& other) noexcept = default;
    HighscoreScreen& operator=(const HighscoreScreen&) = default;
    HighscoreScreen& operator=(HighscoreScreen&& other) = default;
    ScreenStatus Run(sf::RenderWindow&) override;
    ~HighscoreScreen() = default;

private:
    void DrawElements(sf::RenderWindow& window) const;
    void InitializeTexts();
    void InitializeHighscores();
    void LoadFont();
    void LoadHighscores();
    std::vector<std::string> GetHighscores();
    std::vector<std::string> GetBestHighscores();
    void SortHighscores();

private:
    static const int FONT_TITLE = 28;
    static const int FONT_SCORE = 20;
    static const int MAX_SCORES = 5;

    sf::Font m_font;
    sf::Text m_singleplayerBoard;
    sf::Text m_boardColumns[3];
    sf::Text m_singleplayerHighscores[MAX_SCORES];
    sf::Text m_multiplayerBoard;
    std::vector<std::string> m_highscores;
};


