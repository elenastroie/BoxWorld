#include "stdafx.h"
#include "Solver.h"
#include<fstream>
#include "Wall.h"

Solver::Solver(const std::shared_ptr<Level>& level)
{
    WriteToFile(level);
    ReadLevel();
    m_problem = Problem(State(m_player, m_boxes), m_walls, m_goals);
    m_heuristic = Heuristic(m_goals);
    m_search = Search();
}

void Solver::ReadLevel()
{
    uint8_t playerCount = 0;

    std::ifstream file(PATH);
    if (file.is_open())
    {
        std::string line;
        int rowIndex = 0;
        while (getline(file, line))
        {
            for (size_t columnIndex = 0; columnIndex < line.size(); ++columnIndex)
            {
                char c = line[columnIndex];
                if (c == '#') //walls
                {
                    m_walls.insert(MatrixPosition(rowIndex, columnIndex));
                }
                if (c == '@' || c == '+') //player
                {
                    m_player = MatrixPosition(rowIndex, columnIndex);
                    ++playerCount;
                }
                if (c == '.' || c == '+' || c == '*') //goals
                {
                    m_goals.insert(MatrixPosition(rowIndex, columnIndex));
                }
                if (c == '$' || c == '*') //boxes
                {
                    m_boxes.insert(MatrixPosition(rowIndex, columnIndex));
                }
            }
            ++rowIndex;
        }
        file.close();
    }
    else
    {
        throw std::exception("Unable to open current_state.txt");
    }

    if (playerCount != 1)
    {
       std::cout<< "Just 1 player allowed!" << std::endl;
       throw std::exception("Just 1 player allowed for AI!");
    }
}

void Solver::Solve()
{
   // m_result = m_search.BreadthFirstSearch(m_problem);
    m_result = m_search.PrioritySearch(m_problem);
}

std::string& Solver::GetResult()
{
    std::cout << "Solver started, please wait.";
    Solve();
    return m_result;
}

void Solver::WriteToFile(const std::shared_ptr<Level>& level) const
{
    std::ofstream file(PATH);
    if (file.bad())
    {
        throw std::exception("Unable to create current_state.txt");
    }
    const auto& foreground = level->GetForeground();
    const auto& background = level->GetBackground();
    for (size_t rowIndex = 0; rowIndex < foreground.GetRows(); ++rowIndex)
    {
        for (size_t colIndex = 0; colIndex < foreground.GetColumns(); ++colIndex)
        {
            if (std::dynamic_pointer_cast<Wall>(foreground.GetItem(rowIndex, colIndex)))
            {
                file << '#'; //Wall
            }
            else if (std::dynamic_pointer_cast<Player>(foreground.GetItem(rowIndex, colIndex)))
            {
                if (std::dynamic_pointer_cast<Target>(background.GetItem(rowIndex, colIndex)))
                {
                    file << "+"; //Player on target
                }
                else
                {
                    file << "@"; //Player on floor
                }
            }
            else if (std::dynamic_pointer_cast<Target>(background.GetItem(rowIndex, colIndex)))
            {
                if (std::dynamic_pointer_cast<Box>(foreground.GetItem(rowIndex, colIndex)))
                {
                    file << '*'; //Box on target 
                }
                else
                {
                    file << '.'; //Empty goal 
                }
            }
            else if (std::dynamic_pointer_cast<Box>(foreground.GetItem(rowIndex, colIndex)))
            {
                file << "$"; //Box on floor
            }
            else
            {
                file << " ";
            }
        }
        file << std::endl;
    }
    file.close();
}
