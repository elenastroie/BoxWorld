#include "stdafx.h"
#include "MenuScreen.h"
#include "GameManager.h"
#include "../Logging/Log.h"

void MenuScreen::InitializeTexts()
{
    m_playOption.setFont(m_font);
    m_playOption.setCharacterSize(FONT_SIZE);
    m_playOption.setString("Play");
    m_playOption.setPosition({382.f, 585.f});

    m_restartLevel.setFont(m_font);
    m_restartLevel.setCharacterSize(FONT_SIZE);
    m_restartLevel.setString("Restart");
    m_restartLevel.setPosition({338.f, 635.f});

    m_highscoreOption.setFont(m_font);
    m_highscoreOption.setCharacterSize(FONT_SIZE);
    m_highscoreOption.setString("Highscore");
    m_highscoreOption.setPosition({ 315.f, 685.f });

    m_multiplayerOption.setFont(m_font);
    m_multiplayerOption.setCharacterSize(FONT_SIZE);
    m_multiplayerOption.setString("Multiplayer");
    m_multiplayerOption.setPosition({ 280.f, 735.f });

    m_instructionsOption.setFont(m_font);
    m_instructionsOption.setCharacterSize(FONT_SIZE);
    m_instructionsOption.setString("Instructions");
    m_instructionsOption.setPosition({265.f, 785.f});

    m_exitOption.setFont(m_font);
    m_exitOption.setCharacterSize(FONT_SIZE);
    m_exitOption.setString("Exit");
    m_exitOption.setPosition(382.f, 835.f);
}

void MenuScreen::LoadTextures()
{
    if (!m_backgroundTexture.loadFromFile("Assets/Backgrounds/Background1.png"))
    {
        throw std::exception("Background.png not found!");
    }
    background.setTexture(m_backgroundTexture);
}

void MenuScreen::LoadFont()
{
    if (!m_font.loadFromFile("Assets/Fonts/Font.ttf"))
    {
        throw std::exception("Font.ttf not found!");
    }
}

MenuScreen::MenuScreen()
{
    LoadTextures();
    LoadFont();
    InitializeTexts();
}

void MenuScreen::SwitchOption(const uint8_t option)
{
    switch (option)
    {
    case 0:
        m_playOption.setFillColor(sf::Color::Cyan);
        m_restartLevel.setFillColor(sf::Color::Black);
        m_highscoreOption.setFillColor(sf::Color::Black);
        m_multiplayerOption.setFillColor(sf::Color::Black);
        m_instructionsOption.setFillColor(sf::Color::Black);
        m_exitOption.setFillColor(sf::Color::Black);
        break;
    case 1:
        m_playOption.setFillColor(sf::Color::Black);
        m_restartLevel.setFillColor(sf::Color::Cyan);
        m_multiplayerOption.setFillColor(sf::Color::Black);
        m_highscoreOption.setFillColor(sf::Color::Black);
        m_instructionsOption.setFillColor(sf::Color::Black);
        m_exitOption.setFillColor(sf::Color::Black);
        break;
    case 2:
        m_playOption.setFillColor(sf::Color::Black);
        m_restartLevel.setFillColor(sf::Color::Black);
        m_highscoreOption.setFillColor(sf::Color::Cyan);
        m_multiplayerOption.setFillColor(sf::Color::Black);
        m_instructionsOption.setFillColor(sf::Color::Black);
        m_exitOption.setFillColor(sf::Color::Black);
        break;
    case 3:
        m_playOption.setFillColor(sf::Color::Black);
        m_restartLevel.setFillColor(sf::Color::Black);
        m_highscoreOption.setFillColor(sf::Color::Black);
        m_multiplayerOption.setFillColor(sf::Color::Cyan);
        m_instructionsOption.setFillColor(sf::Color::Black);
        m_exitOption.setFillColor(sf::Color::Black);
        break;
    case 4:
        m_playOption.setFillColor(sf::Color::Black);
        m_restartLevel.setFillColor(sf::Color::Black);
        m_highscoreOption.setFillColor(sf::Color::Black);
        m_multiplayerOption.setFillColor(sf::Color::Black);
        m_instructionsOption.setFillColor(sf::Color::Cyan);
        m_exitOption.setFillColor(sf::Color::Black);
        break;
    case 5:
        m_playOption.setFillColor(sf::Color::Black);
        m_restartLevel.setFillColor(sf::Color::Black);
        m_multiplayerOption.setFillColor(sf::Color::Black);
        m_highscoreOption.setFillColor(sf::Color::Black);
        m_instructionsOption.setFillColor(sf::Color::Black);
        m_exitOption.setFillColor(sf::Color::Cyan);
        break;
    default:
        break;
    }
}

void MenuScreen::DrawElements(sf::RenderWindow& window) const
{
    window.clear();
    window.draw(background);
    window.draw(m_playOption);
    window.draw(m_exitOption);
    window.draw(m_restartLevel);
    window.draw(m_multiplayerOption);
    window.draw(m_instructionsOption);
    window.draw(m_highscoreOption);
    window.display();
}

ScreenStatus MenuScreen::Run(sf::RenderWindow& window)
{
    auto& gameManager = GameManager::GetInstance();
    sf::Event event{};
    uint8_t menu = 0;
    constexpr uint8_t numberOfOptions = 6;
    const float initialAspectRatio = window.getSize().x / window.getSize().y;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return ScreenStatus::EXIT;
            }
            if (event.type == sf::Event::Resized)
            {
                resizeScreen(event, window, initialAspectRatio);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                auto& manager = GameManager::GetInstance();
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu = (menu - 1 + numberOfOptions) % numberOfOptions;
                    break;
                case sf::Keyboard::Down:
                    menu = (menu + 1) % numberOfOptions;
                    break;
                case sf::Keyboard::Return:
                    switch (menu)
                    {
                    case 0:
                        Log::Info("Play pressed");
                        return ScreenStatus::PLAY;
                    case 1:
                        Log::Info("Restart pressed");
                        if (&manager != nullptr)
                        {
                            manager.RestartLevel();
                        }
                        return ScreenStatus::RESTART;
                    case 2:
                        Log::Info("Highscore pressed");
                        return ScreenStatus::HIGHSCORE;
                    case 3:
                        Log::Info("Multiplayer pressed");
                        return ScreenStatus::CONNECTION_SCREEN;
                    case 4:
                        Log::Info("Informations pressed");
                        return ScreenStatus::INSTRUCTIONS;
                    case 5:
                        Log::Info("Exit pressed");
                        return ScreenStatus::EXIT;
                    default:
                        break;
                    }
                default:
                    break;
                }
            }
        }
        SwitchOption(menu % numberOfOptions);
        DrawElements(window);
    }

    return ScreenStatus::EXIT;
}
