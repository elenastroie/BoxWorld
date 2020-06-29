#pragma once
#include "MatrixPosition.h"
#include <unordered_set>

class State
{
public:
	State() = default;
	State(const MatrixPosition& player, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& boxes);
	bool operator==(const State& other) const;
    [[nodiscard]] const MatrixPosition& GetPlayer() const;
    [[nodiscard]] const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& GetBoxes() const;

public:
	class HashCode
	{
	public:
		size_t operator()(const State& state) const;
	};

	
private:
	MatrixPosition m_player;
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_boxes;
};

