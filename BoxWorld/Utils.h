#pragma once
#include "Level.h"
#include "MatrixPosition.h"
#include "Node.h"
#include <unordered_set>

class Utils
{
public:
    Utils() = delete;
    static void SetPosition(const std::shared_ptr<GameObject>&, Grid<std::shared_ptr<GameObject>>&, const MatrixPosition&);
    static std::string GetString(MoveDirection moveDirection);
    static std::string AddSpaces(const std::string& userString);
    static bool ContainsSameElements(const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& first, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& second);

    static std::string ConvertToFloatWithPrecision(const float, const int);
    template <typename Unordered>
    static bool UnorderedContains(const Unordered& unordered, const int row, const int col)
    {
        return unordered.find(MatrixPosition(row, col)) != unordered.end();
    }

    template <typename Unordered, typename Element>
    static bool UnorderedContains(const Unordered& unordered, const Element& element)
    {
        return unordered.find(element) != unordered.end();
    }

    template <typename SequenceContainer, typename Element>
    static bool SequenceContains(const SequenceContainer& sequenceContainer, const Element& element)
    {
        return std::find(sequenceContainer.begin(), sequenceContainer.end(), element) != sequenceContainer.end();
    }
};
