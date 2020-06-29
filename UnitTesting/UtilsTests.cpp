#include "pch.h"
#include "CppUnitTest.h"
#include "../BoxWorld/Utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(UtilsTests)
    {
    public:
        TEST_METHOD(SetPosition)
        {
            Grid<std::shared_ptr<GameObject>> grid(3, 3);
            const std::shared_ptr<Player> player = std::make_shared<Player>();
            const MatrixPosition matrixPosition(1, 1);
            Utils::SetPosition(player, grid, matrixPosition);
            Assert::IsNotNull(&player->GetMatrixPosition());
        }

        TEST_METHOD(AddSpaces)
        {
            const std::string string = "test";
            const std::string expected = "t e s t ";
            const auto spaced = Utils::AddSpaces(string);
            Assert::AreEqual(expected, spaced);
        }

        TEST_METHOD(GetStringBottom)
        {
            const std::string expected = "bottom";
            Assert::AreEqual(expected, Utils::GetString(MoveDirection::Bottom));
        }

        TEST_METHOD(GetStringTop)
        {
            const std::string expected = "top";
            Assert::AreEqual(expected, Utils::GetString(MoveDirection::Top));
        }

        TEST_METHOD(GetStringRight)
        {
            const std::string expected = "right";
            Assert::AreEqual(expected, Utils::GetString(MoveDirection::Right));
        }

        TEST_METHOD(GetStringLeft)
        {
            const std::string expected = "left";
            Assert::AreEqual(expected, Utils::GetString(MoveDirection::Left));
        }

        TEST_METHOD(Contains)
        {
            std::vector<std::shared_ptr<Node>> nodes;
            const auto myNode = std::make_shared<Node>();
            nodes.push_back(myNode);
            Assert::IsTrue(Utils::SequenceContains(nodes, myNode));
        }
    };
}
