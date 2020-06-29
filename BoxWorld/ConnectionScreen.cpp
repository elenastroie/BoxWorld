#include "stdafx.h"
#include "ConnectionScreen.h"
#include "ScreenStatus.h"
#include "Game.h"

ConnectionScreen::ConnectionScreen()
{
    LoadFont();
    InitializeTexts();
}

ScreenStatus ConnectionScreen::Run(sf::RenderWindow& window)
{
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    std::ofstream ofstream;
    if (!ifstream.is_open())
    {
        throw std::exception("file not found");
    }
    int numberPlayers;
    ifstream >> numberPlayers;
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
                    m_warningText.setString("You must enter a valid ip!");
                }
                else
                {
                    return ScreenStatus::MENU;
                }
            }
            if (event.type == sf::Event::Resized)
            {
                resizeScreen(event, window, initialAspectRatio);
            }
            if (event.type == sf::Event::TextEntered)
            {
                bool validKey = false;
                m_warningText.setString("");
                if ((isdigit(event.text.unicode) || event.key.code == '.') && m_playerInput.getSize() < MAX_LENGHT)
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
                        if (IsValidIp(m_playerInput.toAnsiString()))
                        {
                            Game::GetInstance().InitializeMultiplayer(m_playerInput);
                            return ScreenStatus::MULTIPLAYER;
                        }
                        m_warningText.setString("Invalid ip!");
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

const std::string& ConnectionScreen::GetValidIp() const
{
    return m_validIp;
}

void ConnectionScreen::DrawElements(sf::RenderWindow& window) const
{
    window.clear();
    window.draw(m_screenText);
    window.draw(m_playerText);
    window.draw(m_warningText);
    window.display();
}

void ConnectionScreen::InitializeTexts()
{
    m_screenText.setFont(m_font);
    m_screenText.setCharacterSize(FONT_SIZE);
    m_screenText.setString("Insert ip:");
    m_screenText.setPosition({896 / 7.0f, 896 / 4.0f});

    m_playerText.setFont(m_font);
    m_playerText.setCharacterSize(FONT_SIZE);
    m_playerText.setPosition({896 / 7.0f + 20, 896 / 4.0f + 70});

    m_warningText.setFont(m_font);
    m_warningText.setCharacterSize(FONT_SIZE - 10);
    m_warningText.setFillColor(sf::Color::Red);
    m_warningText.setPosition({896 / 7.0f, 896 / 4.0f + 130});
}

void ConnectionScreen::LoadFont()
{
    if (!m_font.loadFromFile("Assets/Fonts/Font.ttf"))
    {
        throw std::exception("Font.ttf not found!");
    }
}

std::vector<std::string> ConnectionScreen::Split(const std::string& string, char delim)
{
    auto i = 0;
    std::vector<std::string> vector;

    auto pos = string.find(delim);

    while (pos != std::string::npos)
    {
        vector.push_back(string.substr(i, pos - i));
        i = ++pos;
        pos = string.find(delim, pos);
    }

    vector.push_back(string.substr(i, string.length()));

    return vector;
}

bool ConnectionScreen::IsNumber(const std::string& string)
{
    return !string.empty() && (string.find_first_not_of("[0123456789]") == std::string::npos);
}

bool ConnectionScreen::IsValidIp(const std::string& ip)
{
    auto vector = Split(ip, '.');

    if (vector.size() != 4)
    {
        return false;
    }

    for (const auto& str : vector)
    {
        if (!IsNumber(str) || stoi(str) > 255 || stoi(str) < 0)
        {
            return false;
        }
    }
    return true;
}
