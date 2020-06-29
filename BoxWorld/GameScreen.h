#pragma once
#include "Screen.h"
#include "GameManager.h"
#include "ScreenStatus.h"

class GameScreen final : public Screen
{
public:
    GameScreen();
    GameScreen(const GameScreen&) = default;
    GameScreen(GameScreen&&) noexcept = default;
    GameScreen& operator=(const GameScreen&) = default;
    GameScreen& operator=(GameScreen&&) noexcept = default;

    ScreenStatus Run(sf::RenderWindow&) override;
    void ResetElapesLevelTime();

    ~GameScreen() = default;

private:
    void InitializeTexts();
    void InitializeSprites();
    void LoadFont();
    void UpdateTexts(GameManager& gameManager);
    void DrawElements(sf::RenderWindow& window, sf::Clock& clock, GameManager& gameManager);

private:
    sf::Sprite m_bestSolutionSprite;
    sf::Sprite m_notBestSolutionSprite;
    sf::Sprite m_wallBg;
    sf::Sprite m_pathIndicator;
    sf::Sprite m_scoreBg;
    sf::Font m_font;
    sf::Text m_currentSolution;
    sf::Text m_bestSolution;
    sf::Text m_remainingHints;
    sf::Text m_timeElapsed;
    sf::Text m_solutionTime;
    float m_elapsedLevelTime{};
    std::string m_textTime;
    sf::Text m_highscorePlayer;

    static const int FONT_SIZE = 24;
};
