#include "stdafx.h"
#include "PlayerInfoScreen.h"
#include "ScreenStatus.h"
PlayerInfoScreen::PlayerInfoScreen()
{
    LoadFont();
    InitializeTexts();
}

ScreenStatus PlayerInfoScreen::Run(sf::RenderWindow& window)
{
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    std::ofstream ofstream;
    int numberPlayers;
    ifstream >> numberPlayers;
    ifstream.close();
    sf::Event event{};
    const float initialAspectRatio = window.getSize().x / window.getSize().y;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                if (m_playerInput.getSize() == 0)
                {
                    m_warningText.setString("You must enter a name!");
                }
                else
                {
                    return ScreenStatus::MENU;
                }
            }
            if (event.type == sf::Event::Resized) {
                resizeScreen(event, window, initialAspectRatio);
            }
            if (event.type == sf::Event::TextEntered)
            {
                bool validKey = false;
                m_warningText.setString("");
                if (isalnum(event.text.unicode) && m_playerInput.getSize() < MAX_LENGHT)
                {
                    m_playerInput += event.text.unicode;
                    m_playerText.setString(m_playerInput);
                    validKey = true;
                }
                if (event.key.code == '\b' && m_playerInput.getSize() > 0)
                {
                    m_playerInput.erase(m_playerInput.getSize() - 1, 1);
                    m_playerText.setString(m_playerInput);
                    validKey = true;
                }
                if (event.key.code == '\r' || event.key.code == '\n')
                {
                    validKey = true;
                    if (m_playerInput.getSize() > 0)
                    {
                        ofstream.open("Assets/Player/player_info.txt");
                        ofstream << numberPlayers << " " << m_playerInput.toAnsiString() << " " << "0";
                        ofstream.close();
                        m_playerInput.erase(0, m_playerInput.getSize());
                        m_playerText.setString(m_playerInput);
                        return ScreenStatus::INFO_PLAYER;
                    }
                }
                if (event.key.code == 27)
                {
                    validKey = true;
                }
                if (validKey == false)
                {
                    if (m_playerInput.getSize() < MAX_LENGHT)
                    {
                        m_warningText.setString("Invalid character entered!");
                    }
                    else
                    {
                        m_warningText.setString("Limit reached! MAX 8 CHARACTERS");
                    }

                }
            }
        }
        DrawElements(window);
    }
    return ScreenStatus::EXIT;
}

void PlayerInfoScreen::DrawElements(sf::RenderWindow& window) const
{
    window.clear();
    window.draw(m_screenText);
    window.draw(m_playerText);
    window.draw(m_warningText);
    window.display();
}

void PlayerInfoScreen::InitializeTexts()
{
    m_screenText.setFont(m_font);
    m_screenText.setCharacterSize(FONT_SIZE);
    m_screenText.setString("Enter player name:");
    m_screenText.setPosition({ 896 / 7.0f, 896 / 4.0f });

    m_playerText.setFont(m_font);
    m_playerText.setCharacterSize(FONT_SIZE);
    m_playerText.setPosition({ 896 / 7.0f + 20, 896 / 4.0f + 70 });

    m_warningText.setFont(m_font);
    m_warningText.setCharacterSize(FONT_SIZE - 10);
    m_warningText.setFillColor(sf::Color::Red);
    m_warningText.setPosition({ 896 / 7.0f, 896 / 4.0f + 130 });
}

void PlayerInfoScreen::LoadFont()
{
    if (!m_font.loadFromFile("Assets/Fonts/Font.ttf"))
    {
        throw std::exception("Font.ttf not found!");
    }
}
