#pragma once
#include "MoveDirection.h"

class MatrixPosition
{
public:
    MatrixPosition() = default;
    MatrixPosition(size_t, size_t);

    [[nodiscard]] size_t GetRowIndex() const;
    [[nodiscard]] size_t GetColumnIndex() const;
    void SetRowIndex(size_t);
    void SetColumnIndex(size_t);

    MatrixPosition operator+(const MatrixPosition&) const;
    MatrixPosition operator-(const MatrixPosition&) const;
    MatrixPosition operator-() const;
    bool operator==(const MatrixPosition&) const;
    bool operator!=(const MatrixPosition&) const;

    [[nodiscard]] MatrixPosition Top() const;
    [[nodiscard]] MatrixPosition Right() const;
    [[nodiscard]] MatrixPosition Bottom() const;
    [[nodiscard]] MatrixPosition Left() const;
    [[nodiscard]] MatrixPosition Move(MoveDirection) const;

public:
    class HashCode
    {
    public:
        size_t operator()(const MatrixPosition& matrixPosition) const;
    };

private:
    size_t m_rowIndex{};
    size_t m_columnIndex{};
};
