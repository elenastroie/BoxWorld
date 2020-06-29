#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <memory>
#include "Grid.h"
#include "GameObject.h"
#include "Player.h"
#include "Box.h"
#include "Target.h"

class Level : public sf::Drawable
{
public:
    Level() = delete;
    Level(size_t, size_t);

    Level(const Level&) = default;
    Level(Level&&) noexcept = default;
    Level& operator=(const Level&) = default;
    Level& operator=(Level&&) noexcept = default;

    [[nodiscard]] const Grid<std::shared_ptr<GameObject>>& GetForeground() const;
    [[nodiscard]] const Grid<std::shared_ptr<GameObject>>& GetBackground() const;
    Grid<std::shared_ptr<GameObject>>& GetForeground();
    Grid<std::shared_ptr<GameObject>>& GetBackground();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    std::shared_ptr<Player>& GetPlayer();
    void SetPlayer(const std::shared_ptr<Player>&);
    [[nodiscard]] std::vector<std::shared_ptr<GameObject>> GetObjectsNeighbors(const MatrixPosition&) const;
    std::vector<std::shared_ptr<Box>>& GetBoxes();
    std::vector<std::shared_ptr<Target>>& GetTargets();
    virtual void FetchBoxes() = 0;
    virtual void FetchTargets() = 0;
    virtual uint8_t GetNumberOfRemainingHints() = 0;
    virtual bool CanTakeHint() = 0;
    [[nodiscard]] uint16_t GetBestSolution() const;
    void SetBestSolution(uint16_t);
    [[nodiscard]] uint16_t GetCurrentSolution() const;
    void IncreaseCurrentSolution();
    [[nodiscard]] bool IsBestSolution() const;
    void SetEndLevelHighscore(bool isBestSolution);
    void SetStartLevelHighscore();
    [[nodiscard]] uint16_t GetHighscorePlayer() const;
    ~Level() = default;

protected:
    Grid<std::shared_ptr<GameObject>> m_foregroundObjects;
    Grid<std::shared_ptr<GameObject>> m_backgroundObjects;
    std::shared_ptr<Player> m_player;
    std::vector<std::shared_ptr<Box>> m_boxes;
    std::vector<std::shared_ptr<Target>> m_targets;
    uint16_t m_bestSolution;
    uint16_t m_currentSolution;
    uint16_t m_highscorePlayer;
    uint16_t m_levelHighscore;
};
