#pragma once
#include <SFML/Window/Event.hpp>
#include "Level.h"
#include "LevelLoader.h"
#include "MoveDirection.h"
#include "SoundManager.h"

class GameManager
{
public:
    virtual ~GameManager() = default;
    GameManager() = delete;
    GameManager(LevelLoader&, SoundManager&);

    [[nodiscard]] const std::shared_ptr<Level>& GetCurrentLevel() const;
    void MovePlayerTowardsDirection(MoveDirection moveDirection) const;
    void ProcessEvent(const sf::Event&) const;
    [[nodiscard]] bool IsLevelCompleted() const;
    [[nodiscard]] uint8_t GetLevelNumber() const;
    void LoadNextLevel();
    void LoadLevel(uint8_t levelIndex);
    virtual void RestartLevel() = 0;
    static GameManager& GetInstance();
    [[nodiscard]] LevelLoader& GetLevelLoader() const;
    [[nodiscard]] SoundManager& GetSoundManager() const;

protected:
    using TGrid = Grid<std::shared_ptr<GameObject>>;
    using TObject = std::shared_ptr<GameObject>;
    bool CanMove(const TObject&, TGrid&, MoveDirection) const;

public:
    void CheckBoxesOnTarget() const;
    void CheckBoxOnTarget(const std::shared_ptr<GameObject>&) const;

protected:
    LevelLoader& m_levelLoader;
    SoundManager& m_soundManager;
    std::shared_ptr<Level> m_currentLevel{};
    uint8_t m_levelNumber{};
    static GameManager* s_instance;
};
