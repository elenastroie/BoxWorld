#pragma once
#include "GameObject.h"

class Target final : public GameObject
{
public:
    Target();

    Target(const Target&) = default;
    Target(Target&&) noexcept = default;
    Target& operator=(const Target&) = default;
    Target& operator=(Target&&) noexcept = default;

    bool CanPlayerMoveThrough() const override;
    bool CanBeMovedByPlayer() const override;

    ~Target() = default;

protected:
    void LoadTexture() override;
};
