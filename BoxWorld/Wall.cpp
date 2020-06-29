#include "stdafx.h"
#include "Wall.h"
#include "GameManager.h"
#include "TextureManager.h"

Wall::Wall()
{
    LoadTexture();
}

bool Wall::CanPlayerMoveThrough() const { return false; }

bool Wall::CanBeMovedByPlayer() const { return false; }

void Wall::LoadTexture()
{
    setTexture(TextureManager::GetInstance().GetTexture("wall.png"));
}
