#pragma once
#include <random>
#include "raylib.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"

class Sprite
{
private:
    class Wall
    {
    public:
        void SetLocation(const Location& newLoc);
        const Location& GetLocation() const;
        void Draw(Board& board) const;
    private:
        Location loc;
        static constexpr Color color = RAYWHITE;
    };
public:
    Sprite(std::mt19937& rng, Board& board, const Snake& snake, const Goal& goal);
    void Init(std::mt19937& rng, Board& board, const Snake& snake, const Goal& goal);
    void Respawn(std::mt19937& rng, Board& board, const Snake& snake, const Goal& goal);
    bool IsUniqueOwn(const Location& newLoc) const;
    bool IsTouch(const Location& loc_in) const;
    void Draw(Board& board) const;
private:
    static constexpr int nWallMax = 5;
    Wall walls[nWallMax];
    int nWalls = 1;
};