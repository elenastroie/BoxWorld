#include "stdafx.h"
#include "Search.h"
#include "Node.h"
#include <queue>
#include <string>

Heuristic Search::s_heuristic{};

std::string Search::PrioritySearch(Problem& problem) const
{
    int totalNode = 1;
    int redundant = 0;
    const std::shared_ptr<Node> initial = std::make_shared<Node>(problem.GetInitialState(), nullptr, 0, "");
    std::unordered_set<State, State::HashCode> explored;
    std::vector<std::shared_ptr<Node>> fringe;
    std::make_heap(fringe.begin(), fringe.end(), AStarComparator());
    fringe.push_back(initial);
    std::push_heap(fringe.begin(), fringe.end(), AStarComparator());
    while (!fringe.empty())
    {
        std::shared_ptr<Node> currentNode = fringe.front();
        std::pop_heap(fringe.begin(), fringe.end(), AStarComparator());
        fringe.pop_back();
        if (problem.GoalTest(currentNode->GetState()))
        {
            return GetSolution(currentNode);
        }
        if (!problem.IsUnsolvable(currentNode->GetState()))
        {
            explored.insert(currentNode->GetState());
            std::vector<std::string> actions = problem.AddAction(currentNode->GetState());
            for (size_t index = 0; index < actions.size(); index++)
            {
                std::shared_ptr<Node> child = GetChild(currentNode, actions[index]);
                if (child != nullptr)
                {
                    totalNode++;
                    if (!Utils::UnorderedContains(explored, child->GetState()) && !Utils::SequenceContains(fringe, child))
                    {
                        fringe.push_back(child);
                        std::push_heap(fringe.begin(), fringe.end(), AStarComparator());
                    }
                    else
                    {
                        redundant++;
                    }
                }
            }
        }
    }
    return GetSolution(nullptr);
}

std::string Search::BreadthFirstSearch(Problem& problem) const
{
    int totalNode = 1;
    int redundant = 0;
    std::shared_ptr<Node> node = std::make_shared<Node>(problem.GetInitialState(), nullptr, 0, "");
    if (problem.GoalTest(node->GetState()))
    {
        return GetSolution(node);
    }

    std::unordered_set<State, State::HashCode> explored;
    std::list<std::shared_ptr<Node>> fringe;
    fringe.emplace_back(node);
    std::shared_ptr<Node> child = nullptr;
    while (!fringe.empty())
    {
        node = fringe.front();
        fringe.pop_front();
        explored.insert(node->GetState());

        std::vector<std::string> actions = problem.AddAction(node->GetState());
        for (auto& action : actions)
        {
            child = GetChild(node, action);
            if (child != nullptr)
            {
                totalNode++;
                if (!Utils::UnorderedContains(explored, child->GetState()) && !Utils::SequenceContains(fringe, child))
                {
                    std::string solution = GetSolution(child);
                    if (problem.GoalTest(child->GetState()))
                    {
                        return solution;
                    }
                    if (!problem.IsUnsolvable(child->GetState()))
                    {
                        fringe.emplace_back(child);
                    }
                }
                else
                {
                    redundant++;
                }
            }
        }
    }
    return GetSolution(nullptr);
}

std::string Search::GetSolution(std::shared_ptr<Node> node) const
{
    std::string result;
    int steps = 0;
    if (node == nullptr)
    {
        result = "Unsolvable";
        std::reverse(result.begin(), result.end());
    }
    else
    {
        while (node->GetParent() != nullptr)
        {
            result.append(node->GetMove());
            node = node->GetParent();
            steps++;
        }
    }
    std::reverse(result.begin(), result.end());
    result = Utils::AddSpaces(result);
    result = "\n(Best solution: " + std::to_string(steps) + " steps)\n" + "Follow this steps to solve the level: \n" + result;

    return result;
}


std::shared_ptr<Node> Search::GetChild(const std::shared_ptr<Node>& node, std::string& action) const
{
    std::unordered_set<MatrixPosition, MatrixPosition::HashCode> boxes(node->GetState().GetBoxes());
    const int row = node->GetState().GetPlayer().GetRowIndex();
    const int col = node->GetState().GetPlayer().GetColumnIndex();
    const int newCost = node->GetCost() + 1;
    MatrixPosition newPlayer = node->GetState().GetPlayer();
    const char choice = action[0];
    switch (choice)
    {
    case 'u':
        //update player coordinate
        newPlayer = MatrixPosition(row - 1, col);
        //check if player is pushing a box
        if (Utils::UnorderedContains(boxes, newPlayer))
        {
            const MatrixPosition newBox = MatrixPosition(row - 2, col);
            //update box coordinate
            boxes.erase(newPlayer);
            boxes.insert(newBox);
        }
        break;

    case 'd':
        //update player coordinate
        newPlayer = MatrixPosition(row + 1, col);
        //check if player is pushing a box
        if (Utils::UnorderedContains(boxes, newPlayer))
        {
            const MatrixPosition newBox = MatrixPosition(row + 2, col);
            //update box coordinate
            boxes.erase(newPlayer);
            boxes.insert(newBox);
        }
        break;

    case 'l':
        //update player coordinate
        newPlayer = MatrixPosition(row, col - 1);
        //check if player is pushing a box
        if (Utils::UnorderedContains(boxes, newPlayer))
        {
            const MatrixPosition newBox = MatrixPosition(row, col - 2);
            //update box coordinate
            boxes.erase(newPlayer);
            boxes.insert(newBox);
        }
        break;

    case 'r':
        //update player coordinate
        newPlayer = MatrixPosition(row, col + 1);
        //check if player is pushing a box
        if (Utils::UnorderedContains(boxes, newPlayer))
        {
            const MatrixPosition newBox = MatrixPosition(row, col + 2);
            //update box coordinate
            boxes.erase(newPlayer);
            boxes.insert(newBox);
        }
        break;

    default: ;
    }

    const std::string stringChoice(1, choice);
    return std::make_shared<Node>(State(newPlayer, boxes), node, newCost, stringChoice);
}

bool Search::AStarComparator::operator()(const std::shared_ptr<Node>& node1, const std::shared_ptr<Node>& node2) const
{
    return node1->GetCost() + s_heuristic.GetHeuristic(node1->GetState()) > node2->GetCost() + s_heuristic.GetHeuristic(node2->GetState());
}
