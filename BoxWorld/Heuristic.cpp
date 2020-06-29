#include "stdafx.h"
#include "Heuristic.h"
#include <unordered_set>

Heuristic::Heuristic(const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& targets) : m_targets(targets)
{
    m_targets = targets;
}

int Heuristic::Manhattan(const MatrixPosition& matrixPosition1, const MatrixPosition& matrixPosition2) const
{
    return abs(static_cast<int>(matrixPosition1.GetRowIndex()) - static_cast<int>(matrixPosition2.GetRowIndex())) + abs(static_cast<int>(matrixPosition1.GetColumnIndex()) - static_cast<int>(matrixPosition2.GetColumnIndex()));
}

double Heuristic::GetDist(const MatrixPosition& matrixPosition, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& matrixPositions) const
{
    double minDist = INT_MAX;

    //For each coordinate in a unordered_set, calculate the distance according to given heuristic choice
    for (const MatrixPosition& currentMatrixPosition : matrixPositions)
    {
        const double dist = Manhattan(matrixPosition, currentMatrixPosition);
        if (dist < minDist)
        {
            minDist = dist;
        }
    }
    return minDist;
}

double Heuristic::Calculate(const State& state) const
{
    const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& boxes = state.GetBoxes();
    double sum = 0;

    //get distance from player to boxes, and add to sum
    const MatrixPosition player = state.GetPlayer();
    const double playerMin = GetDist(player, boxes);
    sum += playerMin;

    //get distance from boxes to goals, add each minimum distance to the sum
    for (MatrixPosition currentBox : boxes)
    {
        const double boxMin = GetDist(currentBox, m_targets);
        sum += boxMin;
    }

    return sum;
}

double Heuristic::GetHeuristic(const State& state) const
{
    return Calculate(state);
}
