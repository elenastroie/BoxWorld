#include "stdafx.h"
#include <fstream>
#include "Wall.h"
#include "Box.h"
#include "Utils.h"
#include "Target.h"
#include "Player.h"
#include "SimpleTile.h"
#include "EmptyTile.h"
#include "../Logging/Log.h"
#include "MultiplayerLevelLoader.h"
#include "MultiPlayerLevel.h"

std::shared_ptr<Level> MultiplayerLevelLoader::Load(const std::string levelName) const
{
    Log::Info("Loading " + levelName);
    auto ifstream = std::ifstream("Assets/Levels/" + levelName + ".txt");
    if (!ifstream.is_open())
    {
        throw std::exception("file not found");
    }
    size_t rows;
    size_t cols;
    ifstream >> rows >> cols;
    std::shared_ptr<MultiPlayerLevel> level = std::make_shared<MultiPlayerLevel>(rows, cols);
    auto& foreground = level->GetForeground();
    auto& background = level->GetBackground();
    const auto begin = std::begin(VALID_CHARACTERS);
    const auto end = std::end(VALID_CHARACTERS);
    uint8_t numberOfPlayers = 0;
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols;)
        {
            char ch;
            ifstream >> ch;
            const auto it = std::find(begin, end, ch);
            if (it != end)
            {
                switch (ch)
                {
                case WALL:
                    Utils::SetPosition(std::make_shared<Wall>(), foreground, { row, col });
                    Utils::SetPosition(std::make_shared<SimpleTile>(), background, { row, col });
                    break;
                case BOX:
                    Utils::SetPosition(std::make_shared<Box>(), foreground, { row, col });
                    Utils::SetPosition(std::make_shared<SimpleTile>(), background, { row, col });
                    break;
                case TARGET:
                    Utils::SetPosition(std::make_shared<Target>(), background, { row, col });
                    Utils::SetPosition(std::make_shared<EmptyTile>(), foreground, { row, col });
                    break;
                case PLAYER:
                    if (numberOfPlayers == 0)
                    {
                        level->SetPlayer(std::make_shared<Player>());
                        Utils::SetPosition(level->GetPlayer(), foreground, { row, col });
                        Utils::SetPosition(std::make_shared<SimpleTile>(), background, { row, col });
                        ++numberOfPlayers;
                    }
                    else if (numberOfPlayers == 1)
                    {
                        level->SetRemotePlayer(std::make_shared<Player>());
                        Utils::SetPosition(level->GetRemotePlayer(), foreground, { row, col });
                        Utils::SetPosition(std::make_shared<SimpleTile>(), background, { row, col });
                        ++numberOfPlayers;
                    }
                    else
                    {
                        throw std::exception("Max 2 players!");
                    }
                    break;
                case EMPTY:
                    Utils::SetPosition(std::make_shared<SimpleTile>(), background, { row, col });
                    Utils::SetPosition(std::make_shared<EmptyTile>(), foreground, { row, col });
                    break;
                case RED_BOX:
                {
                    auto box = std::make_shared<Box>();
                    box->SetBoxRed(true);
                    Utils::SetPosition(box, foreground, { row, col });
                }
                Utils::SetPosition(std::make_shared<Target>(), background, { row, col });
                break;
                default:
                    throw std::exception("Unknown character");
                }
                ++col;
            }
        }
    }
    uint16_t bestSolution;
    ifstream >> bestSolution;
    level->SetBestSolution(bestSolution);
    ifstream.close();

    return level;
}
