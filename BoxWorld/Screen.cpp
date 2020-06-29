#include "stdafx.h"
#include "Screen.h"

void Screen::resizeScreen(sf::Event event,sf::RenderWindow& window, const float initialAspectRatio)
{
    const auto windowWidth = event.size.width;
    const auto windowHeight = event.size.height;

    const auto newWidth = initialAspectRatio * windowHeight;
    const auto newHeight = windowWidth / initialAspectRatio;

    const auto offsetWidth = (windowWidth - newWidth) / 2.0;
    const auto offsetHeight = (windowHeight - newHeight) / 2.0;

    sf::View view = window.getDefaultView();

    if (windowWidth >= initialAspectRatio * windowHeight) {
        view.setViewport(sf::FloatRect(offsetWidth / windowWidth, 0.0, newWidth / windowWidth, 1.0));
    }
    else {
        view.setViewport(sf::FloatRect(0.0, offsetHeight / windowHeight, 1.0, newHeight / windowHeight));
    }

    window.setView(view);
}
