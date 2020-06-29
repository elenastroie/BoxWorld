#include "stdafx.h"
#include <SFML/System/Clock.hpp>
#include "GameScreen.h"
#include "GameManager.h"
#include "../Logging/Log.h"
#include "Solver.h"
#include "TextureManager.h"
#include "MultiPlayerLevel.h"
#include "SinglePlayerLevel.h"
#include "ScreenStatus.h"
#include "Game.h"
#include "Utils.h"
#include "MultiplayerGameManager.h"

void GameScreen::InitializeTexts()
{
    LoadFont();
    m_bestSolution.setFont(m_font);
    m_bestSolution.setCharacterSize(FONT_SIZE - 5);
    if (auto solution = GameManager::GetInstance().GetCurrentLevel()->GetBestSolution())
    {
        m_bestSolution.setString(std::to_string(GameManager::GetInstance().GetCurrentLevel()->GetBestSolution()));
    }
    m_bestSolution.setPosition({ 118, 840 });

    m_currentSolution.setFont(m_font);
    m_currentSolution.setCharacterSize(FONT_SIZE - 5);
    m_currentSolution.setPosition({ 118, 804 });

    m_remainingHints.setFont(m_font);
    m_remainingHints.setCharacterSize(FONT_SIZE - 5);
    m_remainingHints.setPosition({ 383,837 });

    m_timeElapsed.setFont(m_font);
    m_timeElapsed.setCharacterSize(FONT_SIZE);
    m_timeElapsed.setPosition({ 255,800 });

    m_solutionTime.setFont(m_font);
    m_solutionTime.setCharacterSize(FONT_SIZE - 3);
    m_solutionTime.setPosition(600.f, 594.f);
    m_solutionTime.setFillColor(sf::Color(220, 0, 0));
    m_solutionTime.setString(m_textTime);

    m_highscorePlayer.setFont(m_font);
    m_highscorePlayer.setCharacterSize(FONT_SIZE);
    m_highscorePlayer.setString("0");
    m_highscorePlayer.setPosition(650, 840);

}

void GameScreen::InitializeSprites()
{
    m_bestSolutionSprite.setTexture(TextureManager::GetInstance().GetTexture("best_solution.png"),
        true);
    m_bestSolutionSprite.setPosition(0, 450);

    m_notBestSolutionSprite.setTexture(
        TextureManager::GetInstance().GetTexture("not_best_solution.png"), true);
    m_notBestSolutionSprite.setPosition(0, 450);

    m_wallBg.setTexture(TextureManager::GetInstance().GetTexture("wall_bg.png"), true);
    m_wallBg.setPosition(0, 0);

    m_pathIndicator.setTexture(TextureManager::GetInstance().GetTexture("path_indicator.png"), true);
    m_scoreBg.setTexture(TextureManager::GetInstance().GetTexture("score_bg.png"), true);
    m_scoreBg.setPosition(0, 768);
}

void GameScreen::LoadFont()
{
    if (!m_font.loadFromFile("Assets/Fonts/Font.ttf"))
    {
        throw std::exception("Font.ttf not found!");
    }
}


GameScreen::GameScreen()
{
    InitializeSprites();
    InitializeTexts();
}


void GameScreen::UpdateTexts(GameManager& gameManager)
{
    m_highscorePlayer.setString(std::to_string(GameManager::GetInstance().GetCurrentLevel()->GetHighscorePlayer()));
    m_currentSolution.setString(std::to_string(gameManager.GetCurrentLevel()->GetCurrentSolution()));
    m_bestSolution.setString(std::to_string(gameManager.GetCurrentLevel()->GetBestSolution()));
    m_remainingHints.setString(std::to_string(gameManager.GetCurrentLevel()->GetNumberOfRemainingHints()));
}

void GameScreen::DrawElements(sf::RenderWindow& window, sf::Clock& clock, GameManager& gameManager)
{
    const auto deltaTime = clock.restart();
    if (!gameManager.IsLevelCompleted())
    {
        m_elapsedLevelTime += deltaTime.asSeconds();
        m_timeElapsed.setString(Utils::ConvertToFloatWithPrecision(m_elapsedLevelTime, 2));
    }
    else
    {
        m_solutionTime.setString(Utils::ConvertToFloatWithPrecision(m_elapsedLevelTime, 2) + " s");
    }
    window.clear();
    gameManager.GetCurrentLevel()->GetPlayer()->Update(deltaTime);
    if (const auto casted = std::dynamic_pointer_cast<MultiPlayerLevel>(gameManager.GetCurrentLevel()))
    {
        if (casted->GetRemotePlayer() != nullptr)
        {
            casted->GetRemotePlayer()->Update(deltaTime);
        }
    }
    window.draw(m_wallBg);
    window.draw(m_scoreBg);
    window.draw(*gameManager.GetCurrentLevel());

    UpdateTexts(gameManager);
    window.draw(m_currentSolution);
    window.draw(m_bestSolution);
    window.draw(m_remainingHints);
    window.draw(m_timeElapsed);
    window.draw(m_highscorePlayer);
}

ScreenStatus GameScreen::Run(sf::RenderWindow& window)
{
    sf::Event event{};
    sf::Clock clock{};
    auto& game = Game::GetInstance();
    auto& gameManager = GameManager::GetInstance();

    const float initialAspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    //m_elapsedLevelTime = 0;
    while (window.isOpen())
    {

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                return ScreenStatus::MENU;
            }
            if (event.type == sf::Event::Closed)
            {
                return ScreenStatus::EXIT;
            }
            if (!gameManager.IsLevelCompleted())
            {
                gameManager.ProcessEvent(event);
                if (event.type == sf::Event::Resized)
                {
                    resizeScreen(event, window, initialAspectRatio);
                }
                if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::H)
                {
                    if (gameManager.GetCurrentLevel()->CanTakeHint())
                    {
                        auto castedLevel = std::dynamic_pointer_cast<SinglePlayerLevel>(gameManager.GetCurrentLevel());
                        castedLevel->IncreaseNumberOfHintsTaken();
                        std::unique_ptr<Solver> solver = std::make_unique<Solver>(gameManager.GetCurrentLevel());
                        const auto result = solver->GetResult();
                        std::cout << result << std::endl;
                        if (result != "Unsolvable")
                        {
                            const auto index = result.find_last_of('\n') + 1;
                            const auto firstMove = result[index];
                            MoveDirection direction{};
                            switch (firstMove)
                            {
                            case 'l':
                                direction = MoveDirection::Left;
                                break;
                            case 'r':
                                direction = MoveDirection::Right;
                                break;
                            case 'd':
                                direction = MoveDirection::Bottom;
                                break;
                            case 'u':
                                direction = MoveDirection::Top;
                                break;
                            default:
                                throw;
                            }
                            gameManager.MovePlayerTowardsDirection(direction);
                        }
                        return ScreenStatus::PLAY;
                    }
                }
            }
        }
        game.Update();
        DrawElements(window, clock, gameManager);

        if (gameManager.IsLevelCompleted())
        {
            bool isBestSolution = false;
            if (gameManager.GetCurrentLevel()->IsBestSolution())
            {
                isBestSolution = true;
                window.draw(m_bestSolutionSprite);
                window.draw(m_solutionTime);
            }
            else
            {
                isBestSolution = false;
                window.draw(m_notBestSolutionSprite);
                window.draw(m_solutionTime);

            }
            if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                try
                {
                    m_textTime = Utils::ConvertToFloatWithPrecision(m_elapsedLevelTime, 2) + " seconds";
                    GameManager::GetInstance().GetCurrentLevel()->SetEndLevelHighscore(isBestSolution);
                    m_highscorePlayer.setString(std::to_string(gameManager.GetCurrentLevel()->GetHighscorePlayer()));
                    window.draw(m_highscorePlayer);

                    Log::Info("Loading next level");
                    Log::Info("Level solved in " + m_textTime + " seconds");
                    m_elapsedLevelTime = 0;
                    gameManager.LoadNextLevel();
                    GameManager::GetInstance().GetCurrentLevel()->SetStartLevelHighscore();

                }
                catch (std::exception & exception)
                {
                    Log::Info("***************************************************\n");
                    Log::Info("You completed the game, no more levels available\n");
                    Log::Info("***************************************************\n");
                    gameManager.LoadLevel(1);
                    auto& multiplayerGameManager = dynamic_cast<MultiplayerGameManager&>(GameManager::GetInstance());
                    if (&multiplayerGameManager != nullptr)
                    {
                        Game::GetInstance().Disconnect();
                    }
                    return ScreenStatus::MENU;
                }
            }
        }

        window.display();
    }
    return ScreenStatus::EXIT;
}

void GameScreen::ResetElapesLevelTime()
{
    m_elapsedLevelTime = 0;
}
