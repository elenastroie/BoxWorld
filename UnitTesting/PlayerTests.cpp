#include "pch.h"
#include "CppUnitTest.h"
#include "../BoxWorld/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(PlayerTests)
    {
    public:
        TEST_METHOD(Constructor)
        {
            Player player{};
            Assert::IsNotNull(&player);
        }

        TEST_METHOD(CanBeMoved)
        {
            const Player player{};
            Assert::IsFalse(player.CanBeMovedByPlayer());
        }

        TEST_METHOD(CanMoveThrough)
        {
            const Player player{};
            Assert::IsFalse(player.CanPlayerMoveThrough());
        }
    };
}
