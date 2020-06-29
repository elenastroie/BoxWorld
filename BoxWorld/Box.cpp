#include "stdafx.h"
#include "Box.h"
#include "GameManager.h"
#include "TextureManager.h"

Box::Box()
{
    m_isRed = false;
    LoadTexture();
}

void Box::LoadTexture()
{
    LoadTexture(m_isRed);
}

void Box::LoadTexture(const bool red)
{
    if (red)
    {
        setTexture(TextureManager::GetInstance().GetTexture("red_box.png"));
    }
    else
    {
        setTexture(TextureManager::GetInstance().GetTexture("yellow_box.png"));
    }
}

bool Box::CanPlayerMoveThrough() const { return false; }

bool Box::CanBeMovedByPlayer() const { return true; }

void Box::SetBoxRed(const bool red)
{
    m_isRed = red;
    LoadTexture(red);
}

bool Box::IsRed() const
{
    return m_isRed;
}
