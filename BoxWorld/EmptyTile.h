#pragma once
#include "GameObject.h" 

class EmptyTile final : public GameObject
{
public:
    EmptyTile() =default;

    EmptyTile(const EmptyTile& other) = default;
    EmptyTile(EmptyTile&& other) = default;
    EmptyTile& operator=(const EmptyTile& other) = default;
    EmptyTile& operator=(EmptyTile&& other) noexcept = default;

    bool CanPlayerMoveThrough() const override;
    bool CanBeMovedByPlayer() const override;

    void LoadTexture() override;
    ~EmptyTile() override = default;
};
