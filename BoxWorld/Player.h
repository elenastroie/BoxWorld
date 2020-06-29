#pragma once
#include "GameObject.h"
#include <SFML/System/Time.hpp>

class Player final : public GameObject
{
public:
    Player();
    Player(const Player&) = default;
    Player(Player &&) noexcept = default;
    Player& operator=(const Player&) = default;
    Player& operator=(Player&&) noexcept = default;

    bool CanPlayerMoveThrough() const override;
    bool CanBeMovedByPlayer() const override;
    void Update(sf::Time);
    void SetId(int8_t);
    [[nodiscard]] int8_t GetId() const;
    MoveDirection GetDirection() const;
    void SetDirection(MoveDirection);

    ~Player() = default;

protected:
    void LoadTexture() override;

private:
    float m_animTime{};
    unsigned m_animFrame{ANIM_FRAMES};
    MoveDirection m_direction{};
    constexpr static float ANIM_FRAME_DURATION = 0.5f;
    constexpr static unsigned ANIM_FRAMES = 2;
    int8_t m_id;
    void UpdateTexture(sf::Time);
};
