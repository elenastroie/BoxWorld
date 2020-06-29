#pragma once
#include "Heuristic.h"
#include "Problem.h"
#include "Node.h"

class Search
{
public:
	Search() = default;
	std::string PrioritySearch(Problem& problem) const;
	std::string BreadthFirstSearch(Problem& problem) const;

public:
	class AStarComparator
	{
	public:
		bool operator()(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) const;
	};
	
private:
	[[nodiscard]] std::string GetSolution(std::shared_ptr<Node> node) const;
	std::shared_ptr<Node> GetChild(const std::shared_ptr<Node>& node, std::string& action) const;

private:
	static Heuristic s_heuristic;
};


