#include "GameManager.h"

int main(int argc, char* argv[])
{
    GameManager game{};
    game.Start();

    while(!game.IsFinished())
    {
        game.Update();
    }

    return 0;
}