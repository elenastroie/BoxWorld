#include "stdafx.h"
#include "MultiplayerGameManager.h"
#include "MultiPlayerLevel.h"
#include "Utils.h"
#include "../Logging/Log.h"

MultiplayerGameManager::MultiplayerGameManager(LevelLoader& levelLoader, SoundManager& soundManager):
    GameManager(levelLoader, soundManager)
{
    LoadLevel(99);
}

void MultiplayerGameManager::MoveRemotePlayerTowardsDirection(const MoveDirection moveDirection) const
{
    auto& foreground = m_currentLevel->GetForeground();
    auto& background = m_currentLevel->GetBackground();
    const auto multiplayerLevel = std::dynamic_pointer_cast<MultiPlayerLevel>(m_currentLevel);
    const auto initialPlayerPosition =multiplayerLevel->GetRemotePlayer()->GetMatrixPosition();
    const auto player = foreground.GetItem(initialPlayerPosition);

    MatrixPosition newPlayerPositon;
    switch (moveDirection)
    {
    case MoveDirection::Top:
        newPlayerPositon = initialPlayerPosition.Top();
        break;
    case MoveDirection::Right:
        newPlayerPositon = initialPlayerPosition.Right();
        break;
    case MoveDirection::Bottom:
        newPlayerPositon = initialPlayerPosition.Bottom();
        break;
    case MoveDirection::Left:
        newPlayerPositon = initialPlayerPosition.Left();
        break;
    default:
        throw std::exception();
    }
    const auto firstObject = foreground.GetItem(newPlayerPositon);

    if (CanMove(player, foreground, moveDirection))
    {
        m_currentLevel->GetPlayer()->SetDirection(moveDirection);
        Utils::SetPosition(player, foreground, newPlayerPositon);
        Utils::SetPosition(firstObject, foreground, initialPlayerPosition);
        m_soundManager.PlayWalkSound();
        m_currentLevel->IncreaseCurrentSolution();
        Log::Info("RemotePlayer moved to " + Utils::GetString(moveDirection));
    }
    else if (firstObject->CanBeMovedByPlayer())
    {
        const auto secondObject = foreground.GetItem(newPlayerPositon.Move(moveDirection));
        if (secondObject->CanPlayerMoveThrough())
        {
            m_currentLevel->GetPlayer()->SetDirection(moveDirection);
            Utils::SetPosition(player, foreground, firstObject->GetMatrixPosition());
            Utils::SetPosition(firstObject, foreground, secondObject->GetMatrixPosition());
            Utils::SetPosition(secondObject, foreground, initialPlayerPosition);
            auto const gameObject = background.GetItem(firstObject->GetMatrixPosition());
            CheckBoxOnTarget(firstObject);
            m_soundManager.PlayWalkSound();
            m_currentLevel->IncreaseCurrentSolution();
            Log::Info("Player moved the box to " + Utils::GetString(moveDirection));
        }
    }
}

void MultiplayerGameManager::RestartLevel()
{
    std::cout << "You can't restart on multiplayer" << std::endl;
}
