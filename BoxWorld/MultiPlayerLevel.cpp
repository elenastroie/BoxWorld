#include "stdafx.h"
#include "MultiPlayerLevel.h"
#include "Utils.h"
#include "SimpleTile.h"
#include "GameManager.h"
#include "MultiplayerGameManager.h"
#include "Wall.h"
MultiPlayerLevel::MultiPlayerLevel(const size_t row, const size_t col) : Level(row, col) {}

void MultiPlayerLevel::FetchBoxes()
{
    std::vector<std::shared_ptr<GameObject>> uncastedBoxes;
    std::copy_if(m_foregroundObjects.GetVector().begin(), m_foregroundObjects.GetVector().end(),
                 std::back_inserter(uncastedBoxes), [](auto gameObject)
                 {
                     return std::dynamic_pointer_cast<Box>(gameObject);
                 });

    std::transform(uncastedBoxes.begin(), uncastedBoxes.end(), std::back_inserter(m_boxes), [](auto uncastedBox)
    {
        return std::dynamic_pointer_cast<Box>(uncastedBox);
    });
}

void MultiPlayerLevel::FetchTargets()
{
    std::vector<std::shared_ptr<GameObject>> uncastedTargets;
    std::copy_if(m_backgroundObjects.GetVector().begin(), m_backgroundObjects.GetVector().end(),
                 std::back_inserter(uncastedTargets), [](auto gameObject)
                 {
                     return std::dynamic_pointer_cast<Target>(gameObject);
                 });

    std::transform(uncastedTargets.begin(), uncastedTargets.end(), std::back_inserter(m_targets),
                   [](auto uncastedTarget)
                   {
                       return std::dynamic_pointer_cast<Target>(uncastedTarget);
                   });
}

uint8_t MultiPlayerLevel::GetNumberOfRemainingHints()
{
    return 0;
}

bool MultiPlayerLevel::CanTakeHint()
{
    return false;
}

void MultiPlayerLevel::SetRemotePlayer(const std::shared_ptr<Player>& remotePlayer)
{
    m_remotePlayer = remotePlayer;
}

std::shared_ptr<Player> MultiPlayerLevel::GetRemotePlayer() const
{
    return m_remotePlayer;
}

void MultiPlayerLevel::MoveRemotePlayer(const MoveDirection moveDirection)
{
    const auto newMatrixPosition = m_remotePlayer->GetMatrixPosition().Move(moveDirection);
    Utils::SetPosition(m_remotePlayer, m_foregroundObjects, newMatrixPosition);
}

void MultiPlayerLevel::MoveRemotePlayer(const MatrixPosition& newRemotePlayerPosition)
{
    const auto swithcedObject = m_foregroundObjects.GetItem(newRemotePlayerPosition);
    const auto initialRemotePlayerPosition = m_remotePlayer->GetMatrixPosition();
    if(m_player->GetMatrixPosition() == newRemotePlayerPosition)
    {
        Utils::SetPosition(m_player, m_foregroundObjects, newRemotePlayerPosition);
    }
    if(std::dynamic_pointer_cast<Box>(swithcedObject))
    {
        Utils::SetPosition(m_remotePlayer, m_foregroundObjects, newRemotePlayerPosition);
        const auto moveDirection = GetMoveDirection(initialRemotePlayerPosition, newRemotePlayerPosition);
        Utils::SetPosition(swithcedObject, m_foregroundObjects, swithcedObject->GetMatrixPosition().Move(moveDirection));
        const auto third = std::dynamic_pointer_cast<Wall>(m_foregroundObjects.GetItem(swithcedObject->GetMatrixPosition().Move(moveDirection)));
        if (third==nullptr)
        {
            Utils::SetPosition(m_foregroundObjects.GetItem(swithcedObject->GetMatrixPosition().Move(moveDirection)), m_foregroundObjects, initialRemotePlayerPosition);
        }
    }
    else
    {
        Utils::SetPosition(m_remotePlayer, m_foregroundObjects, newRemotePlayerPosition);
        Utils::SetPosition(swithcedObject, m_foregroundObjects, initialRemotePlayerPosition);
    }
    GameManager::GetInstance().CheckBoxOnTarget(swithcedObject);
}

void MultiPlayerLevel::MoveRemoteBox(const std::shared_ptr<Box>& box, const MatrixPosition& matrixPosition)
{
    if(!(m_remotePlayer->GetMatrixPosition() == matrixPosition || m_player->GetMatrixPosition() == matrixPosition))
    {
        const auto swithcedObject = m_foregroundObjects.GetItem(matrixPosition);
        const auto initialBoxPosition =box->GetMatrixPosition();
        Utils::SetPosition(box, m_foregroundObjects, matrixPosition);
        Utils::SetPosition(swithcedObject, m_foregroundObjects, initialBoxPosition);
    }
}


MoveDirection MultiPlayerLevel::GetMoveDirection(const MatrixPosition& initial, const MatrixPosition& toMoveIn)
{
    if (initial.Top() == toMoveIn)
    {
        return MoveDirection::Top;
    }
    if (initial.Bottom() == toMoveIn)
    {
        return MoveDirection::Bottom;
    }
    if (initial.Right() == toMoveIn)
    {
        return MoveDirection::Right;
    }
    if(initial.Left() == toMoveIn)
    {
        return MoveDirection::Left;
    }
    throw std::exception("Unable to determine moveDirection");
}
