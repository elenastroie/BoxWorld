#include "pch.h"
#include "CppUnitTest.h"
#include "../BoxWorld/LevelLoaderImpl.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(LevelLoaderTests)
    {
    public:
        TEST_METHOD(Constructor)
        {
            LevelLoaderImpl levelLoader;
            Assert::IsNotNull(&levelLoader);
        }
    };
}
