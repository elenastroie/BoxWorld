#pragma once
#include<SFML/Graphics.hpp>
#include"Screen.h"

class InstructionsScreen final : public Screen
{
 public:
    InstructionsScreen();
    InstructionsScreen(const InstructionsScreen& other) = default;
    InstructionsScreen(InstructionsScreen&& other) noexcept = default;
    InstructionsScreen& operator=(const InstructionsScreen& other) = default;
    InstructionsScreen& operator=(InstructionsScreen&& other) = default;

    ScreenStatus Run(sf::RenderWindow&) override;

    ~InstructionsScreen() = default;

private:
    void DrawElements(sf::RenderWindow& window) const;
    void InitializeText();
    void LoadTextures();
    void LoadFonts();


private:
    sf::Texture m_instrBackgroundTexture;
    sf::Sprite m_instrBackground;
    sf::Font m_instrFont;
    sf::Text m_instructions;
    sf::Text m_arrows;
    sf::Text m_title;
    sf::Text m_hintInstr;
    sf::Text m_hint;

    static const int FONT_SIZE = 37;
};
