#include "Game.h"
#include "Settings.h"

int main()
{
    InitAudioDevice();
    Game game(settings::screenW, settings::screenH, settings::fps, "Raylib Game");

    while(!game.GameShouldClose())
    {
        game.Tick();
    }
    
    return 0;
}