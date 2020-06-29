#include "stdafx.h"
#include "HighscoreScreen.h"

ScreenStatus HighscoreScreen::Run(sf::RenderWindow& window)
{
    LoadHighscores();
    auto bestHigscore = GetBestHighscores();
    InitializeHighscores();
    sf::Event event{};
    const float initialAspectRatio = window.getSize().x / window.getSize().y;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return ScreenStatus::EXIT;
            }
            if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                return ScreenStatus::MENU;
            }
            if (event.type == sf::Event::Resized)
            {
                resizeScreen(event, window, initialAspectRatio);
            }
        }
        DrawElements(window);
    }
    return ScreenStatus::EXIT;
}

void HighscoreScreen::DrawElements(sf::RenderWindow& window) const
{
    window.clear();
    window.draw(m_singleplayerBoard);
    for (int i = 0; i < MAX_SCORES; ++i) {
        window.draw(m_singleplayerHighscores[i]);
    }
    for (int i = 0; i < 3; ++i) {
        window.draw(m_boardColumns[i]);
    }
    window.display();
}

void HighscoreScreen::InitializeTexts()
{
    m_singleplayerBoard.setFont(m_font);
    m_singleplayerBoard.setCharacterSize(FONT_TITLE);
    m_singleplayerBoard.setFillColor(sf::Color::Yellow);
    m_singleplayerBoard.setString("SINGLEPLAYER HIGHSCORE");
    m_singleplayerBoard.setPosition({ 140.f, 50.f });

    m_boardColumns[0].setFont(m_font);
    m_boardColumns[0].setCharacterSize(FONT_SCORE + 5);
    m_boardColumns[0].setString("RANK");
    m_boardColumns[0].setPosition({ 210.f, 150.f });

    m_boardColumns[1].setFont(m_font);
    m_boardColumns[1].setCharacterSize(FONT_SCORE + 5);
    m_boardColumns[1].setString("NAME");
    m_boardColumns[1].setPosition({ 375.f, 150.f });

    m_boardColumns[2].setFont(m_font);
    m_boardColumns[2].setCharacterSize(FONT_SCORE + 5);
    m_boardColumns[2].setString("SCORE");
    m_boardColumns[2].setPosition({ 530.f, 150.f });
}
void HighscoreScreen::InitializeHighscores()
{
    auto positionX = 240.f;
    auto positionY = 200.f;
    auto delimiter = 50.f;
    auto bestHigscore = GetBestHighscores();
    for (int i = 0; i < bestHigscore.size(); ++i)
    {
        if(i==0)
        {
            m_singleplayerHighscores[i].setFillColor(sf::Color::Yellow);
        }
        m_singleplayerHighscores[i].setFont(m_font);
        m_singleplayerHighscores[i].setCharacterSize(FONT_TITLE);
        m_singleplayerHighscores[i].setString(bestHigscore.at(i));
        m_singleplayerHighscores[i].setPosition(positionX, positionY);
        positionY += delimiter;
    }
}
void HighscoreScreen::LoadFont()
{
    if (!m_font.loadFromFile("Assets/Fonts/Font.ttf"))
    {
        throw std::exception("Font.ttf not found!");
    }
}

std::vector<std::string> HighscoreScreen::GetHighscores()
{
    auto ifstream = std::ifstream("Assets/Player/highscore.txt");
    if (ifstream.is_open())
    {
        std::string playerInfo;
        while (std::getline(ifstream, playerInfo))
        {
            m_highscores.push_back(playerInfo);
        }
    }
    SortHighscores();
    return m_highscores;
}

std::vector<std::string> HighscoreScreen::GetBestHighscores()
{
    std::vector<std::string> bestHigscores;
    auto size = MAX_SCORES;
    if (m_highscores.size() <= MAX_SCORES) {
        size = m_highscores.size();
    }
    for (int i = 0; i < size; ++i)
    {
        bestHigscores.push_back(std::to_string(i + 1) + "   " + m_highscores.at(i).substr(m_highscores.at(i).find(" ") + 1));
    }
    return bestHigscores;
}

void HighscoreScreen::SortHighscores()
{
    for (int i = 0; i < m_highscores.size(); ++i)
    {
        for (int j = i; j < m_highscores.size(); ++j) {
            if (std::stoi(m_highscores.at(i).substr(m_highscores.at(i).find(" >") + 2)) <
                std::stoi(m_highscores.at(j).substr(m_highscores.at(j).find(" >") + 2)))
            {
                std::swap(m_highscores.at(i), m_highscores.at(j));
            }
        }
    }
}
void HighscoreScreen::LoadHighscores()
{
    m_highscores = GetHighscores();
    auto ofstream = std::ofstream("Assets/Player/highscore.txt");
    if (!ofstream.is_open())
    {
        ofstream.open("Assets/Player/highscore.txt");
    }
    for (std::string infoPlayer : m_highscores)
    {
        ofstream << infoPlayer << '\n';
    }
    ofstream.close();
}

HighscoreScreen::HighscoreScreen()
{
    LoadFont();
    InitializeTexts();
}
