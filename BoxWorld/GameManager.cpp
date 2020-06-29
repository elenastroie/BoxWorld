#include "stdafx.h"
#include "GameManager.h"
#include "Utils.h"
#include "EmptyTile.h"
#include "Target.h"
#include "Box.h"
#include "../Logging/Log.h"

GameManager* GameManager::s_instance = nullptr;

GameManager::GameManager(LevelLoader& levelLoader, SoundManager& soundManager) :
    m_levelLoader(levelLoader), m_soundManager(soundManager)
{
    s_instance = this;
    m_levelNumber = 0;
}

const std::shared_ptr<Level>& GameManager::GetCurrentLevel() const { return m_currentLevel; }

void GameManager::MovePlayerTowardsDirection(const MoveDirection moveDirection) const
{
    auto& foreground = m_currentLevel->GetForeground();
    auto& background = m_currentLevel->GetBackground();
    const auto initialPlayerPosition = m_currentLevel->GetPlayer()->GetMatrixPosition();
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
        Log::Info("Player moved to " + Utils::GetString(moveDirection));
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

void GameManager::ProcessEvent(const sf::Event& event) const
{
    switch (event.type)
    {
    case sf::Event::KeyReleased:
        {
            MoveDirection moveDirection;
            MatrixPosition newPlayerPositon;
            switch (event.key.code)
            {
            case sf::Keyboard::Left:
                moveDirection = MoveDirection::Left;
                break;
            case sf::Keyboard::Right:
                moveDirection = MoveDirection::Right;
                break;
            case sf::Keyboard::Up:
                moveDirection = MoveDirection::Top;
                break;
            case sf::Keyboard::Down:
                moveDirection = MoveDirection::Bottom;
                break;
            default:
                return;
            }
            MovePlayerTowardsDirection(moveDirection);
            break;
        }
    default: ;
    }
}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool GameManager::CanMove(const TObject& object, TGrid& grid, const MoveDirection direction) const
{
    const auto& position = object->GetMatrixPosition();
    const auto row = position.GetRowIndex();
    const auto column = position.GetColumnIndex();
    MatrixPosition movePosition;
    switch (direction)
    {
    case MoveDirection::Top:
        if (column == 0)
            return false;
        movePosition = position.Top();
        break;
    case MoveDirection::Right:
        if (row == grid.GetRows() - 1)
            return false;
        movePosition = position.Right();
        break;
    case MoveDirection::Bottom:
        if (column == grid.GetColumns() - 1)
            return false;
        movePosition = position.Bottom();
        break;
    case MoveDirection::Left:
        if (row == 0)
            return false;
        movePosition = position.Left();
        break;
    default:
        throw;
    }

    const auto& item = grid.GetItem(movePosition);
    return !item || item->CanPlayerMoveThrough();
}

void GameManager::CheckBoxesOnTarget() const
{
    for (const auto& box : m_currentLevel->GetBoxes())
    {
        auto cast = std::dynamic_pointer_cast<Target>(m_currentLevel->GetBackground().GetItem(box->GetMatrixPosition()));
        box->SetBoxRed(cast != nullptr);
    }
}

void GameManager::CheckBoxOnTarget(const std::shared_ptr<GameObject>& gameObject) const
{
    auto const box = std::dynamic_pointer_cast<Box>(gameObject);
    if (box)
    {
        const auto target = std::dynamic_pointer_cast<Target>(
            m_currentLevel->GetBackground().GetItem(box->GetMatrixPosition()));
        box->SetBoxRed(target != nullptr);
    }
}

bool GameManager::IsLevelCompleted() const
{
    for (const auto& box : m_currentLevel->GetBoxes())
    {
        if (!box->IsRed())
        {
            return false;
        }
    }
    return true;
}

uint8_t GameManager::GetLevelNumber() const
{
    return m_levelNumber;
}

void GameManager::LoadNextLevel()
{
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    ++m_levelNumber;
    m_currentLevel = m_levelLoader.Load("Level" + std::to_string(m_levelNumber));
    if (m_levelNumber != 1)
    {
        m_soundManager.PlayWinSound();
    }
    m_currentLevel->FetchBoxes();
    m_currentLevel->FetchTargets();
}

void GameManager::LoadLevel(const uint8_t levelIndex)
{
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    m_levelNumber = levelIndex;
    m_currentLevel = m_levelLoader.Load("Level" + std::to_string(m_levelNumber));
    m_currentLevel->FetchBoxes();
    m_currentLevel->FetchTargets();
}


GameManager& GameManager::GetInstance()
{
    return *s_instance;
}

LevelLoader& GameManager::GetLevelLoader() const { return m_levelLoader; }

SoundManager& GameManager::GetSoundManager() const { return m_soundManager; }
