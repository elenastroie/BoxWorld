#include "stdafx.h"
#include "Player.h"
#include "GameManager.h"
#include "TextureManager.h"

Player::Player() : m_id(-1)
{
    LoadTexture();
}


bool Player::CanPlayerMoveThrough() const { return false; }

bool Player::CanBeMovedByPlayer() const { return false; }

void Player::Update(const sf::Time deltaTime)
{
    UpdateTexture(deltaTime);
}

void Player::SetId(const int8_t id)
{
    m_id = id;
}
int8_t Player::GetId() const
{
    return m_id;
}

void Player::UpdateTexture(const sf::Time deltaTime)
{
    const auto oldFrame = m_animFrame;
    m_animTime += deltaTime.asSeconds();
    const auto deltaFrames = static_cast<unsigned>(m_animTime / ANIM_FRAME_DURATION);
    m_animFrame = (m_animFrame + deltaFrames) % ANIM_FRAMES;
    m_animTime -= deltaFrames * ANIM_FRAME_DURATION;

    if (m_animFrame != oldFrame)
    {
        const auto textureName = "player_" + std::to_string(static_cast<unsigned>(m_direction)) +
            std::to_string(m_animFrame) + ".png";
        setTexture(TextureManager::GetInstance().GetTexture(textureName));
    }
}

MoveDirection Player::GetDirection() const { return m_direction; }

void Player::SetDirection(const MoveDirection moveDirection)
{
    if (m_direction != moveDirection)
    {
        m_direction = moveDirection;
        m_animFrame = ANIM_FRAMES;
        m_animTime = 0;
    }
}

void Player::LoadTexture() {}
