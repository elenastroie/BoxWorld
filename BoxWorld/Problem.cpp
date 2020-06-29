#include "stdafx.h"
#include "Problem.h"


Problem::Problem(const State& initialState, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& walls, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& targets)
{
    m_initialState = initialState;
    m_walls = walls;
    m_targets = targets;
}

/**
 * simple check to see if any of the boxes are in a deadlock state:
 *  #  or  #####  or  ##
 * #$      #X$X#      $$
 * 
 */

bool Problem::IsUnsolvable(const State& state) const
{
    for (const MatrixPosition& box : state.GetBoxes())
    {
        const int row = box.GetRowIndex();
        const int col = box.GetColumnIndex();
        if (!Utils::UnorderedContains(m_targets, row, col))
        {
            if (Utils::UnorderedContains(m_walls, row - 1, col) && Utils::UnorderedContains(m_walls, row, col - 1))
            {
                return true; //top & left
            }
            if (Utils::UnorderedContains(m_walls, row - 1, col) && Utils::UnorderedContains(m_walls, row, col + 1))
            {
                return true; //top & right
            }
            if (Utils::UnorderedContains(m_walls, row + 1, col) && Utils::UnorderedContains(m_walls, row, col - 1))
            {
                return true; //bottom & left
            }
            if (Utils::UnorderedContains(m_walls, row + 1, col) && Utils::UnorderedContains(m_walls, row, col + 1))
            {
                return true; //bottom & right
            }

            if (Utils::UnorderedContains(m_walls, row - 1, col - 1) && Utils::UnorderedContains(m_walls, row - 1, col) &&
                Utils::UnorderedContains(m_walls, row - 1, col + 1) && Utils::UnorderedContains(m_walls, row, col - 2) &&
                Utils::UnorderedContains(m_walls, row, col + 2) && (!Utils::UnorderedContains(m_targets, row, col - 1)) &&
                !Utils::UnorderedContains(m_targets, row, col + 1))
            {
                return true; //top & sides
            }
            if (Utils::UnorderedContains(m_walls, row + 1, col - 1) && Utils::UnorderedContains(m_walls, row + 1, col) &&
                Utils::UnorderedContains(m_walls, row + 1, col + 1) && Utils::UnorderedContains(m_walls, row, col - 2) &&
                Utils::UnorderedContains(m_walls, row, col + 2) && (!Utils::UnorderedContains(m_targets, row, col - 1)) &&
                (!Utils::UnorderedContains(m_targets, row, col + 1)))
            {
                return true; //bottom & sides
            }
            if (Utils::UnorderedContains(m_walls, row - 1, col - 1) && Utils::UnorderedContains(m_walls, row, col - 1) &&
                Utils::UnorderedContains(m_walls, row + 1, col - 1) && Utils::UnorderedContains(m_walls, row - 2, col) &&
                Utils::UnorderedContains(m_walls, row + 2, col) && (!Utils::UnorderedContains(m_targets, row - 1, col)) &&
                (!Utils::UnorderedContains(m_targets, row + 1, col)))
            {
                return true; //left & vertical
            }
            if (Utils::UnorderedContains(m_walls, row - 1, col + 1) && Utils::UnorderedContains(m_walls, row, col + 1) &&
                Utils::UnorderedContains(m_walls, row + 1, col + 1) && Utils::UnorderedContains(m_walls, row - 2, col) &&
                Utils::UnorderedContains(m_walls, row + 2, col) && (!Utils::UnorderedContains(m_targets, row - 1, col)) &&
                (!Utils::UnorderedContains(m_targets, row + 1, col)))
            {
                return true; //right & top/bottom
            }
        }
    }
    return false;
}

bool Problem::GoalTest(const State& state) const
{
    for (const MatrixPosition& box : state.GetBoxes())
    {
        if (!Utils::UnorderedContains(m_targets, box)) //std::find(m_targets.begin(), m_targets.end(), box) != m_targets.end())
        {
            return false;
        }
    }
    return true;
}


std::vector<std::string> Problem::AddAction(const State& state) const
{
    std::vector<std::string> actionList;
    const int row = state.GetPlayer().GetRowIndex();
    const int col = state.GetPlayer().GetColumnIndex();
    const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& boxes = state.GetBoxes();

    //checking if moving up, right, down, left is valid
    //for each, check if next player move is a wall
    //if next move has a box, check next box move does not overlap with wall or another box
    MatrixPosition newPlayer(row - 1, col);
    MatrixPosition newBox(row - 2, col);
    if (!Utils::UnorderedContains(m_walls, newPlayer))
    {
        if (Utils::UnorderedContains(boxes, newPlayer) && (Utils::UnorderedContains(boxes, newBox) || Utils::UnorderedContains(m_walls, newBox)));
        else
        {
            actionList.emplace_back("u");
        }
    }

    newPlayer = MatrixPosition(row, col + 1);
    newBox = MatrixPosition(row, col + 2);
    if (!Utils::UnorderedContains(m_walls, newPlayer))
    {
        if (Utils::UnorderedContains(boxes, newPlayer) && (Utils::UnorderedContains(boxes, newBox) || Utils::UnorderedContains(m_walls, newBox)));
        else
        {
            actionList.emplace_back("r");
        }
    }

    newPlayer = MatrixPosition(row + 1, col);
    newBox = MatrixPosition(row + 2, col);
    if (!Utils::UnorderedContains(m_walls, newPlayer))
    {
        if (Utils::UnorderedContains(boxes, newPlayer) && (Utils::UnorderedContains(boxes, newBox) || Utils::UnorderedContains(m_walls, newBox)));
        else
        {
            actionList.emplace_back("d");
        }
    }

    newPlayer = MatrixPosition(row, col - 1);
    newBox = MatrixPosition(row, col - 2);
    if (!Utils::UnorderedContains(m_walls, newPlayer))
    {
        if (Utils::UnorderedContains(boxes, newPlayer) && (Utils::UnorderedContains(boxes, newBox) || Utils::UnorderedContains(m_walls, newBox)));
        else
        {
            actionList.emplace_back("l");
        }
    }

    return actionList;
}

const State& Problem::GetInitialState() const
{
    return m_initialState;
}
