#include "stdafx.h"
#include "Target.h"
#include "GameManager.h"
#include "TextureManager.h"

Target::Target()
{
    LoadTexture();
}

bool Target::CanPlayerMoveThrough() const { return true; }

bool Target::CanBeMovedByPlayer() const { return false; }

void Target::LoadTexture()
{
    setTexture(TextureManager::GetInstance().GetTexture("target.png"));
}
