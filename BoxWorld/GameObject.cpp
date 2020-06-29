#include "stdafx.h"
#include "GameObject.h"

MatrixPosition GameObject::GetMatrixPosition() const { return m_matrixPosition; }

void GameObject::SetMatrixPosition(const MatrixPosition& matrixPosition) { m_matrixPosition = matrixPosition; }
