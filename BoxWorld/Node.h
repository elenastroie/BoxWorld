#pragma once
#include "State.h"
#include <string>
#include <memory>

class Node
{
public:
	Node() = default;
	Node(const State& state, std::shared_ptr<Node> parent, int cost, const std::string& move);
	[[nodiscard]] const State& GetState() const;
    [[nodiscard]] const std::shared_ptr<Node>& GetParent() const;
    [[nodiscard]] int GetCost() const;
    [[nodiscard]] const std::string& GetMove() const;
	bool operator==(const Node& other) const;
	bool operator<(const Node& other) const;
	bool operator>(const Node& other) const;
	
private:
	State m_state;
	std::shared_ptr<Node> m_parent;
	int m_cost{};
	std::string m_move;
};

