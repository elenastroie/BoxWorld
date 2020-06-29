#pragma once
#include "GameObject.h"

class Wall final : public GameObject
{
public:
    Wall();
    Wall(const Wall&) = default;
    Wall(Wall&&) noexcept = default;
    Wall& operator=(const Wall&) = default;
    Wall& operator=(Wall&&) noexcept = default;

    bool CanPlayerMoveThrough() const override;
    bool CanBeMovedByPlayer() const override;

    virtual ~Wall() = default;

protected:
    void LoadTexture() override;
};
