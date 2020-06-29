#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "MatrixPosition.h"

class HintTile final : public sf::Sprite
{
public:
    HintTile();
    explicit HintTile(MatrixPosition);
    void SetAlpha(sf::Uint8);
};
