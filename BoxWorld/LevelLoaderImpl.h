#pragma once
#include "LevelLoader.h"
#include "SinglePlayerLevel.h"

class LevelLoaderImpl final : public LevelLoader
{
public:
    LevelLoaderImpl() = default;
    [[nodiscard]] std::shared_ptr<Level> Load(std::string) const override;
};
