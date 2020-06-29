#pragma once
#include "GameManager.h"

class SinglePlayerGameManager final : public GameManager
{
public:
    SinglePlayerGameManager(LevelLoader& levelLoader, SoundManager& soundManager);
    void RestartLevel() override;
};
