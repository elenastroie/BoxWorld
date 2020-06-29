#include "stdafx.h"
#include "MatrixPosition.h"
#include <typeindex>

MatrixPosition::MatrixPosition(const size_t rowIndex, const size_t columnIndex)
{
    m_rowIndex = rowIndex;
    m_columnIndex = columnIndex;
}

size_t MatrixPosition::GetRowIndex() const
{
    return m_rowIndex;
}

size_t MatrixPosition::GetColumnIndex() const
{
    return m_columnIndex;
}

void MatrixPosition::SetRowIndex(const size_t rowIndex)
{
    m_rowIndex = rowIndex;
}

void MatrixPosition::SetColumnIndex(const size_t columnIndex)
{
    m_columnIndex = columnIndex;
}

MatrixPosition MatrixPosition::operator+(const MatrixPosition& other) const
{
    return { m_rowIndex + other.m_rowIndex, m_columnIndex + other.m_columnIndex };
}

MatrixPosition MatrixPosition::operator-(const MatrixPosition& other) const
{
    return { m_rowIndex - other.m_rowIndex, m_columnIndex - other.m_columnIndex };
}

MatrixPosition MatrixPosition::operator-() const
{
    return { static_cast<size_t>(-static_cast<const int>(m_rowIndex)), static_cast<size_t>(-static_cast<const int>(m_columnIndex)) };
}

bool MatrixPosition::operator==(const MatrixPosition& other) const
{
    return m_rowIndex == other.m_rowIndex && m_columnIndex == other.m_columnIndex;
}

bool MatrixPosition::operator!=(const MatrixPosition& other) const
{
    if(this == &other)
    {
        return true;
    }
    if(m_rowIndex != other.m_rowIndex || m_columnIndex != other.m_columnIndex)
    {
        return true;
    }
    return false;
}


MatrixPosition MatrixPosition::Top() const
{
    return *this - MatrixPosition(1, 0);
}

MatrixPosition MatrixPosition::Right() const
{
    return *this + MatrixPosition(0, 1);
}

MatrixPosition MatrixPosition::Bottom() const
{
    return *this + MatrixPosition(1, 0);
}

MatrixPosition MatrixPosition::Left() const
{
    return *this - MatrixPosition(0, 1);
}

MatrixPosition MatrixPosition::Move(const MoveDirection moveDirection) const
{
    switch (moveDirection)
    {
    case MoveDirection::Top:
        return this->Top();

    case MoveDirection::Bottom:
        return this->Bottom();

    case MoveDirection::Left:
        return this->Left();

    case MoveDirection::Right:
        return this->Right();
    }
    throw;
}

size_t MatrixPosition::HashCode::operator()(const MatrixPosition& matrixPosition) const
{
    return std::hash<size_t>()(matrixPosition.GetRowIndex() * 1000 + matrixPosition.GetColumnIndex());
}
