#include "stdafx.h"
#include "Level.h"
#include "Wall.h"
#include "Grid.h"
#include "Utils.h"

const Grid<std::shared_ptr<GameObject>>& Level::GetForeground() const { return m_foregroundObjects; }

const Grid<std::shared_ptr<GameObject>>& Level::GetBackground() const { return m_backgroundObjects; }

Grid<std::shared_ptr<GameObject>>& Level::GetForeground() { return m_foregroundObjects; }

Grid<std::shared_ptr<GameObject>>& Level::GetBackground() { return m_backgroundObjects; }


void Level::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    for (size_t row = 0, rows = m_foregroundObjects.GetRows(); row < rows; ++row)
    {
        for (size_t col = 0, cols = m_foregroundObjects.GetColumns(); col < cols; ++col)
        {
            const auto& backgroundObject = m_backgroundObjects.GetItem(row, col);
            if (backgroundObject)
            {
                target.draw(*backgroundObject, states);
            }

            const auto& foregroundObject = m_foregroundObjects.GetItem(row, col);
            if (foregroundObject)
            {
                target.draw(*foregroundObject, states);
            }
        }
    }
}

std::shared_ptr<Player>& Level::GetPlayer() { return m_player; }


void Level::SetPlayer(const std::shared_ptr<Player>& player) { m_player = player; }


Level::Level(const size_t rows, const size_t columns) :
    m_foregroundObjects(rows, columns), m_backgroundObjects(rows, columns), m_bestSolution(0), m_currentSolution(0), m_levelHighscore(1000),m_highscorePlayer(0)
{
}

std::vector<std::shared_ptr<GameObject>> Level::GetObjectsNeighbors(const MatrixPosition& matrixPosition) const
{
    std::vector<std::shared_ptr<GameObject>> neighbors;
    neighbors.push_back(m_foregroundObjects.GetItem(matrixPosition.Top()));
    neighbors.push_back(m_foregroundObjects.GetItem(matrixPosition.Bottom()));
    neighbors.push_back(m_foregroundObjects.GetItem(matrixPosition.Right()));
    neighbors.push_back(m_foregroundObjects.GetItem(matrixPosition.Left()));
    return neighbors;
}

std::vector<std::shared_ptr<Box>>& Level::GetBoxes()
{
    return m_boxes;
}

std::vector<std::shared_ptr<Target>>& Level::GetTargets()
{
    return m_targets;
}


uint16_t Level::GetBestSolution() const
{
    return m_bestSolution;
}

void Level::SetBestSolution(const uint16_t bestSolution)
{
    m_bestSolution = bestSolution;
}

uint16_t Level::GetCurrentSolution() const
{
    return m_currentSolution;
}

void Level::IncreaseCurrentSolution()
{
    ++m_currentSolution;
}

bool Level::IsBestSolution() const
{
    return m_bestSolution >= m_currentSolution;
}

void Level::SetEndLevelHighscore(bool isBestSolution)
{
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    int numberOfPlayers;
    std::string nameOfPlayer;
    int highscorePlayer;
    if (ifstream.peek() != std::ifstream::traits_type::eof()) {
        ifstream >> numberOfPlayers;
        ifstream >> nameOfPlayer;
        ifstream >> highscorePlayer;
        ifstream.close();
    }
    if (isBestSolution) {
        highscorePlayer += +1000;
        m_highscorePlayer = highscorePlayer;
    }
    else
    {
        m_levelHighscore = 500 / ((GetBestSolution() / 2) + 1) * (GetCurrentSolution() - GetBestSolution());
        if (m_levelHighscore >= 500)
            m_levelHighscore = 0;
        highscorePlayer += 500 + m_levelHighscore;
        m_highscorePlayer = highscorePlayer;
    }
    auto ofstream = std::ofstream("Assets/Player/player_info.txt");
    ofstream << numberOfPlayers << " " << nameOfPlayer << " " << highscorePlayer;
    ofstream.close();
}

void Level::SetStartLevelHighscore()
{
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    int numberOfPlayers;
    std::string nameOfPlayer;
    int highscorePlayer;
    if (ifstream.peek() != std::ifstream::traits_type::eof()) {
        ifstream >> numberOfPlayers;
        ifstream >> nameOfPlayer;
        ifstream >> m_highscorePlayer;
        ifstream.close();
    }
    else
        m_highscorePlayer = 0;
}

uint16_t Level::GetHighscorePlayer() const
{
    return m_highscorePlayer;
}
