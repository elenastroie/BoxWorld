#include "stdafx.h"
#include "Game.h"


int main()
{
    Game game;
    try
    {
        game.Start();
    }
    catch(std::exception &exception)
    {
        //std::cout << exception.what();
    }
    return 0;
}
