#pragma once
#include "Level.h"
#include "LevelLoader.h"
#include<string>

class MultiplayerLevelLoader final : public LevelLoader
{
public:
    MultiplayerLevelLoader() = default;

    [[nodiscard]] std::shared_ptr<Level> Load(std::string) const override;
};
