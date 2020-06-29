#pragma once
#include <vector>
#include "MatrixPosition.h"

template
<typename T>
class Grid
{
public:
    Grid() = delete;

    Grid(const size_t rows, const size_t columns): m_rows{rows}, m_columns{columns}
    {
        m_vector = std::vector<T>(rows * columns);
    }

    Grid(const Grid& other): m_rows{other.m_rows},
                             m_columns{other.m_columns}
    {
        std::copy(other.m_vector.begin(), other.m_vector.end(), std::back_inserter(m_vector));
    }

    Grid& operator=(const Grid& other)
    {
        if (this != &other)
        {
            m_rows = other.m_rows;
            m_columns = other.m_columns;
            std::copy(other.m_vector.begin(), other.m_vector.end(), std::back_inserter(m_vector));
        }

        return *this;
    }

    Grid(Grid&& other) noexcept: m_rows{other.m_rows},
                                 m_columns{other.m_columns},
                                 m_vector{std::move(other.m_vector)} { }

    Grid& operator=(Grid&& other) noexcept
    {
        if (this != &other)
        {
            m_rows = other.m_rows;
            m_columns = other.m_columns;
            m_vector = std::move(other.m_vector);
        }

        return *this;
    }

    size_t GetRows() const noexcept { return m_rows; }

    size_t GetColumns() const noexcept { return m_columns; }

    T& GetItem(const size_t row, const size_t column)
    {
        ThrowIfOutOfRange(row, column);

        return m_vector[m_columns * row + column];
    }

    const T& GetItem(const size_t row, const size_t column) const
    {
        ThrowIfOutOfRange(row, column);

        return m_vector[m_columns * row + column];
    }

    T& GetItem(const MatrixPosition& matrixPosition)
    {
        const auto row = matrixPosition.GetRowIndex();
        const auto column = matrixPosition.GetColumnIndex();

        return GetItem(row, column);
    }

    const T& GetItem(const MatrixPosition& matrixPosition) const
    {
        const auto row = matrixPosition.GetRowIndex();
        const auto column = matrixPosition.GetColumnIndex();

        return GetItem(row, column);
    }

    std::vector<T>& GetVector()
    {
        return m_vector;
    }

    void SetItem(const size_t row, const size_t column, const T& item)
    {
        ThrowIfOutOfRange(row, column);

        m_vector[m_columns * row + column] = item;
    }

    void SetItem(const MatrixPosition& matrixPosition, const T& item)
    {
        const auto row = matrixPosition.GetRowIndex();
        const auto col = matrixPosition.GetColumnIndex();

        SetItem(row, col, item);
    }

    ~Grid() = default;

private:
    void ThrowIfOutOfRange(const size_t row, const size_t column) const
    {
        if (row < 0 || row >= m_rows)
            throw std::exception("Row index out of range");
        if (column < 0 || column >= m_columns)
            throw std::exception("Column index out of range");
    }

    size_t m_rows;
    size_t m_columns;
    std::vector<T> m_vector;
};
