#include "pch.h"
#include <CppUnitTest.h>
#include "../BoxWorld/TextureManagerImpl.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
    TEST_CLASS(TextureManagerTests)
    {
    public:
        TEST_METHOD(Constructor)
        {
            TextureManagerImpl textureManager;
            Assert::IsNotNull(&textureManager);
        }

        TEST_METHOD(GetTexture)
        {
            TextureManagerImpl textureManager;
            textureManager.LoadAllTextures({
                "red_box.png"
            });
            Assert::IsNotNull(&textureManager.GetTexture("red_box.png"));
        }

        TEST_METHOD(GetInstance)
        {
            TextureManagerImpl textureManager;
            Assert::IsNotNull(&textureManager.GetInstance());
        }
    };
}
