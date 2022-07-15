#pragma once
#include <random>
#include "raylib.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"

class Wall
{
public:
    Wall(std::mt19937& rng, Board& board, const Snake& snake);
    void Respawn(std::mt19937& rng, Board& board, const Snake& snake);
    const Location& GetLocation() const;
    void Draw(Board& board) const;
    bool IsInTile(const Location& loc_in) const;
private:
    Location loc;
    static constexpr int width = 20;
    static constexpr int height = 20;
    static constexpr Color color = RAYWHITE;
};