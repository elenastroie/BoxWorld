#pragma once
#include "GameManager.h"

class MultiplayerGameManager final : public GameManager
{
public:
    MultiplayerGameManager(LevelLoader& levelLoader, SoundManager& soundManager);
    void MoveRemotePlayerTowardsDirection(const MoveDirection moveDirection) const;
    void RestartLevel() override;
};
