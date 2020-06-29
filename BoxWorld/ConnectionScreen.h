#pragma once
#include "Screen.h"
class ConnectionScreen final : public Screen
{
public:
    ConnectionScreen();
    ScreenStatus Run(sf::RenderWindow&) override;
    const std::string& GetValidIp() const;

private:
    void DrawElements(sf::RenderWindow& window) const;
    void InitializeTexts();
    void LoadFont();
    std::vector<std::string> Split(const std::string& string, char delim);
    bool IsNumber(const std::string& string);
    bool IsValidIp(const std::string& ip);

private:
    sf::Font m_font;
    sf::String m_playerInput;
    sf::Text m_playerText;
    sf::Text m_screenText;
    sf::Text m_warningText;
    std::string m_validIp;

    static const int FONT_SIZE = 30;
    static const int MAX_LENGHT = 16;
};

