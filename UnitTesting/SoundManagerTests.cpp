#include "pch.h"
#include <CppUnitTest.h>
#include "../BoxWorld/SoundManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(SoundManagerTests)
    {
    public:
        TEST_METHOD(Constructor)
        {
            SoundManager soundManager;
            Assert::IsNotNull(&soundManager);
        }
    };
}
