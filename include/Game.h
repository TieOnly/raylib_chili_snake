#pragma once
#include <string>
#include <random>
#include "raylib.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include "Sprite.h"

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

    std::mt19937 rng;
    Board board;
    Location delta_loc = {1, 0};
    Location last_delta_loc = {1, 0};

    Snake snake;
    static constexpr int snakePeriod = 10;
    int snakeMoveCount = 0;

    Goal goal;
    
    Sprite sprite;
    static constexpr int spritePeriod = 250;
    int spriteMoveCount = 0;

    bool IsGameOver = false;
};
