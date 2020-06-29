#pragma once
#include "GameObject.h"

class SimpleTile final : public GameObject
{
public:
    SimpleTile();
    SimpleTile(const SimpleTile&) = default;
    SimpleTile(SimpleTile&&) = default;
    SimpleTile& operator=(const SimpleTile&) = default;
    SimpleTile& operator=(SimpleTile&&) noexcept = default;

    bool CanPlayerMoveThrough() const override;
    bool CanBeMovedByPlayer() const override;

    ~SimpleTile() override = default;

protected:
    void LoadTexture() override;
};
