#pragma once
#include "GameObject.h"

class Box final : public GameObject
{
public:
    Box();
   
    Box(const Box& other) = default;
    Box(Box&& other) noexcept = default;
    Box& operator=(const Box& other) = default;
    Box& operator=(Box&& other) noexcept = default;

    bool CanPlayerMoveThrough() const override;
    bool CanBeMovedByPlayer() const override;
    void SetBoxRed(bool);
    bool IsRed() const;
    ~Box() = default;

protected:
    void LoadTexture() override;

private:
    bool m_isRed;

    void LoadTexture(bool);
};
