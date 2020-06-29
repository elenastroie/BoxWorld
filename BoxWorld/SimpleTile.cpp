#include "stdafx.h"
#include "SimpleTile.h"
#include "GameManager.h"
#include "TextureManager.h"

SimpleTile::SimpleTile()
{
    LoadTexture();
}

void SimpleTile::LoadTexture()
{
    setTexture(TextureManager::GetInstance().GetTexture("simple_tile.png"));
}

bool SimpleTile::CanPlayerMoveThrough() const { return true; }

bool SimpleTile::CanBeMovedByPlayer() const { return false; }
