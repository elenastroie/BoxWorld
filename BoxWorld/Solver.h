#pragma once
#include <string>
#include <unordered_set>
#include "MatrixPosition.h"
#include "Problem.h"
#include "Heuristic.h"
#include "Search.h"

class Solver
{
public:
    explicit Solver(const std::shared_ptr<Level>& level);
	std::string& GetResult();
    void WriteToFile(const std::shared_ptr<Level>& level) const;


private:
	void ReadLevel();
	void Solve();
	
private:
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_walls;
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_goals;
	std::unordered_set<MatrixPosition, MatrixPosition::HashCode> m_boxes;
	MatrixPosition m_player;
	Problem m_problem;
	Heuristic m_heuristic;
	Search m_search;
	std::string m_result;

    inline static const std::string PATH = "Assets/Solver/current_state.txt";
};

