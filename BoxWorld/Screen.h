#pragma once
#include<SFML/Graphics.hpp>
#include "ScreenStatus.h"

class Screen
{
public:
    Screen() = default;

    Screen(const Screen&) = default;
    Screen(Screen&&) noexcept = default;
    Screen& operator=(const Screen&) = default;
    Screen& operator=(Screen&&) noexcept = default;

    virtual ~Screen() = default;

    virtual ScreenStatus Run(sf::RenderWindow&) = 0;
    static void resizeScreen(sf::Event event, sf::RenderWindow& window, const float initialAspectRatio);
};
