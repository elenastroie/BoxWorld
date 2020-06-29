#pragma once
#include "stdafx.h"
#include "State.h"
#include "Utils.h"
#include <unordered_set>

class Problem
{
public:
	Problem() = default;
	Problem(const State& initialState, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& walls, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& targets);
	[[nodiscard]] bool GoalTest(const State& state) const;
    [[nodiscard]] bool IsUnsolvable(const State& state) const;
    [[nodiscard]] std::vector<std::string> AddAction(const State& state) const;
    [[nodiscard]] const State& GetInitialState() const;
	
private:
	State m_initialState;
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_walls;
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_targets;
};

