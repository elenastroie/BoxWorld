#include "stdafx.h"
#include "SinglePlayerGameManager.h"
SinglePlayerGameManager::SinglePlayerGameManager(LevelLoader& levelLoader, SoundManager& soundManager):
     GameManager(levelLoader, soundManager)
{
    LoadNextLevel();
}

void SinglePlayerGameManager::RestartLevel()
{
    if (m_levelNumber != 0)
    {
        LoadLevel(m_levelNumber);
    }
}
