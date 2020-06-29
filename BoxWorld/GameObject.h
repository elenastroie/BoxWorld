#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "MatrixPosition.h"

class GameObject : public sf::Sprite
{
public:
    GameObject() = default;

    GameObject(const GameObject&) = default;
    GameObject(GameObject&&) noexcept = default;
    GameObject& operator=(const GameObject&) = default;
    GameObject& operator=(GameObject&&) noexcept = default;

    MatrixPosition GetMatrixPosition() const;
    void SetMatrixPosition(const MatrixPosition&);
    virtual bool CanPlayerMoveThrough() const = 0;
    virtual bool CanBeMovedByPlayer() const = 0;

    virtual ~GameObject() = default;

    constexpr static float TEXTURE_SIZE = 64;

protected:
    virtual void LoadTexture() = 0;
    MatrixPosition m_matrixPosition{};
};
