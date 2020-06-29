#include "stdafx.h"
#include "SinglePlayerLevel.h"
SinglePlayerLevel::SinglePlayerLevel(const size_t row, const size_t col): Level(row, col), m_numberOfHintsTaken(0)
{
}

void SinglePlayerLevel::FetchBoxes()
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

void SinglePlayerLevel::FetchTargets()
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

uint8_t SinglePlayerLevel::GetNumberOfRemainingHints()
{
    return GetNumberOfHintsForLevel() - m_numberOfHintsTaken;
}

bool SinglePlayerLevel::CanTakeHint()
{
    return m_numberOfHintsTaken < GetNumberOfHintsForLevel();
}

void SinglePlayerLevel::IncreaseNumberOfHintsTaken()
{
    ++m_numberOfHintsTaken;
}

uint8_t SinglePlayerLevel::GetNumberOfHintsForLevel() const
{
    return std::round(GetBestSolution() * HINTS_MULTIPLIER);  // NOLINT
}
