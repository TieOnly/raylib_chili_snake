#include <assert.h>
#include "Game.h"
#include "raylib.h"
#include <iostream>

Game::Game(int width, int height, int fps, std::string title)
    :
    beat( LoadSound("../assets/sound/frad - first date.mp3") ),
    config( "../config/config.txt" ),
    rng( std::random_device()() ),
    board( new Board(config.GetWidth(), config.GetHeight(), config.GetDimension()) ),
    snake( new Snake({1, 1}, config) ),
    goal(new Goal(rng, board, snake)),
    sprite(new Sprite(rng, board, snake, goal, config))
{
    assert(!GetWindowHandle());
    InitWindow(width, height, title.c_str());
    eat = LoadSound("../assets/sound/step.mp3");
    SetTargetFPS(fps);

    board->InitItems( rng );
    PlaySound(beat);
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
void Game::RestartGame()
{
    delete board;
    delete snake;
    delete goal;
    delete sprite;
    board = nullptr;
    snake = nullptr;
    goal = nullptr;
    sprite = nullptr;

    board = new Board(config.GetWidth(), config.GetHeight(), config.GetDimension());
    snake = new Snake({1, 1}, config);
    goal = new Goal(rng, board, snake);
    sprite = new Sprite(rng, board, snake, goal, config);

    board->InitItems( rng );
    delta_loc = {1, 0};
    last_delta_loc = {1, 0};
    snakePeriod = 0.2f;
    spriteMoveCount = 0;
    
    PlaySound(beat);
}
void Game::Update()
{
    const float dt = fr.Mark();
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
        if( spriteMoveCount >= spritePeriod )
        {
            spriteMoveCount = 0;
            sprite->Respawn(rng, board, snake, goal);
        }

        //Snake Period Compare Frame
        snakeMoveCount += dt;

        if( snakeMoveCount >= snakePeriod )
        {
            snakeMoveCount -= snakePeriod;
            //Check NOT reverse
            if(
                last_delta_loc.x * delta_loc.x != -1 &&
                last_delta_loc.y * delta_loc.y != -1   
            ) {
                last_delta_loc = delta_loc;
            }
            const Location next = snake->GetNextHeadLocation(last_delta_loc);
            if(!board->IsInsideBoard( next ) ||
               snake->IsInTileExceptEnd( next ) ||
               sprite->IsTouch( next ))
            {
                IsGameOver = true;
            } else {
                bool eating = next == goal->GetLocation();
                if(eating)
                {
                    PlaySound(eat);
                    snake->Grow();
                }
                snake->MoveBy( last_delta_loc );
                if(eating) 
                {
                    goal->Respawn(rng, board, snake);
                    board->SetItemEmpty( next );
                }

                if( board->checkExistItem( next ) )
                {
                    board->SetItemEmpty( next );
                    if(snakePeriod >= 0) snakePeriod -= config.GetSpeedUp();
                }
            }
        }
    }
    else
    {
        if(IsKeyPressed(KEY_SPACE))
        {
            RestartGame();
            IsGameOver = false;
        }
    }
}
void Game::Draw()
{
    ClearBackground(BLACK);
    board->Draw();
    board->DrawItem();
    snake->Draw(board);
    goal->Draw(board);
    sprite->Draw(board);
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
