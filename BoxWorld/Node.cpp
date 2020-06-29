#include "stdafx.h"
#include "Node.h"
#include <string>
#include <utility>

Node::Node(const State& state, std::shared_ptr<Node> parent, const int cost, const std::string& move)
{
    m_parent = std::move(parent);
    m_state = state;
    m_cost = cost;
    m_move = move;
}

bool Node::operator==(const Node& other) const
{
    return m_state == other.m_state;
}

bool Node::operator<(const Node& other) const
{
    return m_cost < other.m_cost;
}

bool Node::operator>(const Node& other) const
{
    return m_cost > other.m_cost;
}

const State& Node::GetState() const
{
    return m_state;
}

const std::shared_ptr<Node>& Node::GetParent() const
{
    return m_parent;
}

int Node::GetCost() const
{
    return m_cost;
}

const std::string& Node::GetMove() const
{
    return m_move;
}
