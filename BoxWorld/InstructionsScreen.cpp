#include "stdafx.h"
#include "InstructionsScreen.h"
#include "../Logging/Log.h"

InstructionsScreen::InstructionsScreen()
{
    LoadTextures();
    LoadFonts();
    InitializeText();
}

void InstructionsScreen::LoadTextures()
{
    if (!m_instrBackgroundTexture.loadFromFile("Assets/Backgrounds/BackgroundInstr1.png"))
    {
        throw std::exception("InstrBackground.png not found!");
    }
    m_instrBackground.setTexture(m_instrBackgroundTexture);
}

void InstructionsScreen::LoadFonts()
{
    if (!m_instrFont.loadFromFile("Assets/Fonts/Font.ttf"))
    {
        throw std::exception("Fonst.ttf not found!");
    }
}

void InstructionsScreen::InitializeText()
{
    m_title.setFont(m_instrFont);
    m_title.setCharacterSize(35);
    m_title.setString("Player Controls");
    m_title.setPosition(200.f, 290);
    m_title.setFillColor(sf::Color::Black);

    m_instructions.setFont(m_instrFont);
    m_instructions.setCharacterSize(24);
    m_instructions.setString("To move in game press:");
    m_instructions.setPosition(182.f,607.f);
    m_instructions.setFillColor(sf::Color::Black);

    m_arrows.setFont(m_instrFont);
    m_arrows.setCharacterSize(24);
    m_arrows.setString("Up, Down, Left, Right arrows");
    m_arrows.setPosition(110.f,640.f);
    m_arrows.setFillColor(sf::Color::Black);

    m_hint.setFont(m_instrFont);
    m_hint.setCharacterSize(24);
    m_hint.setString("For hints press: H");
    m_hint.setPosition(190.f,690.f);
    m_hint.setFillColor(sf::Color::Black);
}

ScreenStatus InstructionsScreen::Run(sf::RenderWindow& window)
{
    sf::Event event{};

    const float initialAspectRatio = window.getSize().x / window.getSize().y;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
            {
                Log::Info("Returned to menu");
                return ScreenStatus::MENU;
            }
            if(event.type == sf::Event::Resized)
            {
                resizeScreen(event, window, initialAspectRatio);
            }
        }
        DrawElements(window);
    }

    return ScreenStatus::EXIT;
}

void InstructionsScreen::DrawElements(sf::RenderWindow& window) const
{
    window.clear();
    window.draw(m_instrBackground);
    window.draw(m_title);
    window.draw(m_instructions);
    window.draw(m_arrows);
    window.draw(m_hint);
    window.display();
}
