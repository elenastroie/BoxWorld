#include "pch.h"
#include "CppUnitTest.h"
#include "../BoxWorld/Grid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(GridTests)
    {
    public:
        TEST_METHOD(Constructor)
        {
            Grid<int> grid(2,2);
            Assert::IsNotNull(&grid);
        }

        TEST_METHOD(Constructor2)
        {
            const Grid<int> grid(2, 3);
            const size_t expetedRow = 2;
            Assert::AreEqual(expetedRow, grid.GetRows());
            const size_t expectedCol = 3;
            Assert::AreEqual(expectedCol, grid.GetColumns());
        }

        TEST_METHOD(SetItem)
        {
            Grid<int> grid(2, 2);
            grid.SetItem(0, 0, 5);
            Assert::AreEqual(5, grid.GetItem(0, 0));
        }

        TEST_METHOD(SetItemMatrixPositionOverload)
        {
            Grid<int> grid(2, 2);
            grid.SetItem({ 0,0 }, 5);
            Assert::AreEqual(5, grid.GetItem({0,0}));
        }

        TEST_METHOD(GetVetor)
        {
            Grid<int> grid(2, 2);
            grid.SetItem({ 0,0 }, 5);
            Assert::IsNotNull(&grid.GetVector());
        }

        TEST_METHOD(GetIndexOutOfBounds)
        {
            Grid<int> grid(2, 2);
            Assert::ExpectException<std::exception>([&grid]() {grid.GetItem({55, 63}); });
        }
        TEST_METHOD(SetIndexOutOfBounds)
        {
            Grid<int> grid(2, 2);
            Assert::ExpectException<std::exception>([&grid]() {grid.SetItem({ 34,104 }, 3); });
        }
        TEST_METHOD(GetIndexOutOfBoundsOverload)
        {
            Grid<int> grid(2, 2);
            Assert::ExpectException<std::exception>([&grid]() {grid.GetItem( 55, 63 ); });
        }
        TEST_METHOD(SetIndexOutOfBoundsOverload)
        {
            Grid<int> grid(2, 2);
            Assert::ExpectException<std::exception>([&grid]() {grid.SetItem( 34,104 , 3); });
        }
    };
}
