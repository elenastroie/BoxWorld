#include "stdafx.h"
#include "State.h"
#include "Utils.h"

State::State(const MatrixPosition& player, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& boxes)
{
    m_player = player;
    m_boxes = boxes;
}

bool State::operator==(const State& other) const
{
    if (&other == this)
    {
        return true;
    }

    if (Utils::ContainsSameElements(m_boxes, other.m_boxes) && m_player == other.m_player)
    {
        return true;
    }

    return false;
}

const MatrixPosition& State::GetPlayer() const
{
    return m_player;
}

const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& State::GetBoxes() const
{
    return m_boxes;
}

size_t State::HashCode::operator()(const State& state) const
{
    auto result = 17;
    const auto primeNumber = 37;
    for (const MatrixPosition& matrixPosition : state.GetBoxes())
    {
        result = primeNumber * result + std::hash<int>()(matrixPosition.GetRowIndex() * 1000 + matrixPosition.GetColumnIndex());
    }
    result = primeNumber * result + std::hash<int>()(state.GetPlayer().GetRowIndex() * 1000 + state.GetPlayer().GetColumnIndex());
    return result;
}
