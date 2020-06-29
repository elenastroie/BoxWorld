#pragma once
#include <unordered_set>
#include "MatrixPosition.h"
#include "State.h"


class Heuristic
{
public:
	Heuristic() = default;
    explicit Heuristic(const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& targets);
    [[nodiscard]] double GetHeuristic(const State& state) const;

private:
    [[nodiscard]] int Manhattan(const MatrixPosition& matrixPosition1, const MatrixPosition& matrixPosition2) const;
    [[nodiscard]] double GetDist(const MatrixPosition& matrixPosition, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& matrixPositions) const;
    [[nodiscard]] double Calculate(const State& state) const;
	
private:
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_targets;
};

