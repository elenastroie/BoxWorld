#pragma once
#include "Level.h"

class LevelLoader
{
public:
    LevelLoader(const LevelLoader&) = default;
    LevelLoader(LevelLoader&&) noexcept = default;
    LevelLoader& operator=(const LevelLoader&) = default;
    LevelLoader& operator=(LevelLoader&&) noexcept = default;

    [[nodiscard]] virtual  std::shared_ptr<Level> Load(std::string) const = 0;

    virtual ~LevelLoader() = default;

protected:
    LevelLoader() = default;

protected:
    static const char WALL = 'W';
    static const char BOX = 'B';
    static const char TARGET = 'T';
    static const char PLAYER = 'P';
    static const char EMPTY = '_';
    static const char RED_BOX = 'R';
    static constexpr char VALID_CHARACTERS[] = { WALL, BOX, TARGET, PLAYER, EMPTY, RED_BOX };
};
