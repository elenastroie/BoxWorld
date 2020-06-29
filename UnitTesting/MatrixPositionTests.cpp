#include "pch.h"
#include "CppUnitTest.h"
#include "../BoxWorld/MatrixPosition.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(MatrixPositionTests)
    {
    public:
        TEST_METHOD(Constructor)
        {
            const size_t rowIndex = 3;
            const size_t columnIndex = 2;
            const MatrixPosition matrixPosition(rowIndex, columnIndex);
            Assert::IsNotNull(&matrixPosition);
            Assert::AreEqual(matrixPosition.GetRowIndex(), rowIndex);
            Assert::AreEqual(matrixPosition.GetColumnIndex(), columnIndex);
        }

        TEST_METHOD(MinusOperator)
        {
            const MatrixPosition matrixPosition1(1, 1);
            const MatrixPosition matrixPosition2(1, 1);
            const MatrixPosition result = matrixPosition1 - matrixPosition2;
            Assert::IsTrue(MatrixPosition(0, 0) == result);
        }

        TEST_METHOD(PlusOperator)
        {
            const MatrixPosition matrixPosition1(1, 1);
            const MatrixPosition matrixPosition2(1, 1);
            const MatrixPosition result = matrixPosition1 + matrixPosition2;
            Assert::IsTrue(MatrixPosition(2, 2) == result);
        }

        TEST_METHOD(Top)
        {
            MatrixPosition matrixPosition(1, 1);
            matrixPosition = matrixPosition.Top();
            Assert::IsTrue(matrixPosition == MatrixPosition(0, 1));
        }

        TEST_METHOD(Bottom)
        {
            MatrixPosition matrixPosition(1, 1);
            matrixPosition = matrixPosition.Bottom();
            Assert::IsTrue(matrixPosition == MatrixPosition(2, 1));
        }

        TEST_METHOD(Left)
        {
            MatrixPosition matrixPosition(1, 1);
            matrixPosition = matrixPosition.Left();
            Assert::IsTrue(matrixPosition == MatrixPosition(1, 0));
        }

        TEST_METHOD(Right)
        {
            MatrixPosition matrixPosition(1, 1);
            matrixPosition = matrixPosition.Right();
            Assert::IsTrue(matrixPosition == MatrixPosition(1, 2));
        }

        TEST_METHOD(Move)
        {
            MatrixPosition matrixPosition1(1, 1);
            matrixPosition1 = matrixPosition1.Move(MoveDirection::Top);
            Assert::IsTrue(matrixPosition1 == MatrixPosition(0, 1));

            MatrixPosition matrixPosition2(1, 1);
            matrixPosition2 = matrixPosition2.Move(MoveDirection::Bottom);
            Assert::IsTrue(matrixPosition2 == MatrixPosition(2, 1));

            MatrixPosition matrixPosition3(1, 1);
            matrixPosition3 = matrixPosition3.Move(MoveDirection::Left);
            Assert::IsTrue(matrixPosition3 == MatrixPosition(1, 0));

            MatrixPosition matrixPosition4(1, 1);
            matrixPosition4 = matrixPosition4.Move(MoveDirection::Right);
            Assert::IsTrue(matrixPosition4 == MatrixPosition(1, 2));

        }

    };
}
