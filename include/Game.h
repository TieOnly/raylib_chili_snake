#pragma once
#include <string>
#include <random>
#include "Settings.h"
#include "raylib.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include "Sprite.h"
#include "FrameTime.h"

class Game
{
public:
    Game(int width, int height, int fps, std::string title);
    ~Game() noexcept;
    Game (const Game& another) = delete;
    Game& operator = (const Game& another) = delete;
    bool GameShouldClose() const;
    void Tick();
private:
    void Update();
    void Draw();
    void DrawGameText(const char* text);

    void RestartGame();

    Sound beat;
    Sound eat;
    settings::Config config;

    FrameTime fr;
    std::mt19937 rng;

    Board* board;
    Location delta_loc = {1, 0};
    Location last_delta_loc = {1, 0};

    Snake* snake;
    float snakePeriod = 0.2f;
    float snakeMoveCount = 0.0f;

    Goal* goal;
    
    Sprite* sprite;
    static constexpr int spritePeriod = 250;
    int spriteMoveCount = 0;

    bool IsGameOver = false;
};
