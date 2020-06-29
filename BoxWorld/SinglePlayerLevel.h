#pragma once
#include "Level.h"
class SinglePlayerLevel final : public Level
{
public:
    SinglePlayerLevel() = delete;
    SinglePlayerLevel(size_t, size_t);
    void FetchBoxes() override;
    void FetchTargets() override;
    uint8_t GetNumberOfRemainingHints() override;
    bool CanTakeHint() override;
    void IncreaseNumberOfHintsTaken();
    [[nodiscard]] uint8_t GetNumberOfHintsForLevel() const;

private:
    uint8_t m_numberOfHintsTaken;
    constexpr static float HINTS_MULTIPLIER = 1 / 4.f;
};

