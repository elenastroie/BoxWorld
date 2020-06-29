#include "stdafx.h"
#include "Utils.h"
#include "GameObject.h"
#include <sstream>
#include <iomanip>

void Utils::SetPosition(const std::shared_ptr<GameObject>& object, Grid<std::shared_ptr<GameObject>>& grid, const MatrixPosition& position)
{
    object->setPosition(GameObject::TEXTURE_SIZE * position.GetColumnIndex(),  // NOLINT(cppcoreguidelines-narrowing-conversions)
        GameObject::TEXTURE_SIZE * position.GetRowIndex());  // NOLINT(cppcoreguidelines-narrowing-conversions)
    object->SetMatrixPosition(position);
    grid.SetItem(position, object);
}

std::string Utils::GetString(const MoveDirection moveDirection)
{
    switch (moveDirection)
    {
    case MoveDirection::Bottom:
        return "bottom";
    case MoveDirection::Top:
        return "top";
    case MoveDirection::Right:
        return "right";
    case MoveDirection::Left:
        return "left";
    }
    throw std::exception("Invalid move direction");
}

std::string Utils::AddSpaces(const std::string& userString)
{
    std::string spacedString;

    for (auto itr : userString)
    {
        spacedString += itr;
        spacedString += ' ';
    }

    return spacedString;
}

bool Utils::ContainsSameElements(const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& first, const std::unordered_set<MatrixPosition, MatrixPosition::HashCode>& second)
{
    if (first.size() == second.size())
    {
        for (auto const& elementFromFirst : first)
        {
            if (second.find(elementFromFirst) == second.end())
            {
                return false;
            }
        }
    }
    return true;
}

std::string Utils::ConvertToFloatWithPrecision(const float n, const int precision)
{
    static std::stringstream ss;
    ss.str(std::string());
    ss << std::fixed << std::setprecision(precision) << n;
    return ss.str();
}
