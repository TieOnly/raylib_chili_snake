#include <assert.h>
#include "Game.h"
#include "raylib.h"
#include "Settings.h"

Game::Game(int width, int height, int fps, std::string title)
    :
    rng( std::random_device()() ),
    snake( {5, 5} ),
    goal(rng, board, snake),
    sprite(rng, board, snake, goal)
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());
    SetTargetFPS(fps);
}
Game::~Game() noexcept
{
    assert(GetWindowHandle());
    CloseWindow();
}
bool Game::GameShouldClose() const
{
    return WindowShouldClose();
}
void Game::Tick() 
{
    BeginDrawing();
    Update();
    Draw();
    EndDrawing();
}
void Game::Update()
{
    dt = fr.Mark();
    
    if(!IsGameOver)
    {
        if(IsKeyPressed(KEY_UP))
        {
            delta_loc = {0, -1};
        }
        else if(IsKeyPressed(KEY_RIGHT))
        {
            delta_loc = {1, 0};
        }
        else if(IsKeyPressed(KEY_DOWN))
        {
            delta_loc = {0, 1};
        }
        else if(IsKeyPressed(KEY_LEFT))
        {
            delta_loc = {-1, 0};
        }
        
        //
        ++spriteMoveCount;
        if( spriteMoveCount == spritePeriod )
        {
            spriteMoveCount = 0;
            sprite.Respawn(rng, board, snake, goal);
        }

        //Snake Period Compare Frame
        ++snakeMoveCount;
        if( snakeMoveCount == snakePeriod )
        {
            snakeMoveCount = 0;
            //Check NOT reverse
            if(
                last_delta_loc.x * delta_loc.x != -1 &&
                last_delta_loc.y * delta_loc.y != -1   
            ) {
                last_delta_loc = delta_loc;
            }
            const Location next = snake.GetNextHeadLocation(last_delta_loc);
            if(!board.IsInsideBoard( next ) ||
               snake.IsInTileExceptEnd( next ) ||
               sprite.IsTouch( next ))
            {
                IsGameOver = true;
            } else {
                bool eating = snake.GetNextHeadLocation(last_delta_loc) == goal.GetLocation();
                if(eating)
                {
                    snake.Grow();
                }
                snake.MoveBy( last_delta_loc );
                if(eating) goal.Respawn(rng, board, snake);
            }
        }
    }
}
void Game::Draw()
{
    ClearBackground(BLACK);
    board.Draw();
    snake.Draw(board);
    goal.Draw(board);
    sprite.Draw(board);
    if(IsGameOver)
    {
        DrawGameText("Game Over");
    } else {
        DrawGameText("Nom Nom");
    }
}
void Game::DrawGameText(const char* text)
{
    DrawText(text, int(settings::screenW - MeasureText(text, 30) - 60) , 50, 30, WHITE);
}
