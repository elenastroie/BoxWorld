#include "stdafx.h"
#include "HintTile.h"
#include "GameManager.h"
#include "TextureManager.h"

HintTile::HintTile()
{
    setTexture(TextureManager::GetInstance().GetTexture("path_indicator.png"));
}

HintTile::HintTile(const MatrixPosition position) : HintTile()
{
    setPosition(GameObject::TEXTURE_SIZE * position.GetColumnIndex(),  GameObject::TEXTURE_SIZE * position.GetRowIndex());
}

void HintTile::SetAlpha(const sf::Uint8 alpha)
{
    auto color = getColor();
    color.a = alpha;
    setColor(color);
}
