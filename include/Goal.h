#pragma once
#include <random>
#include "raylib.h"
#include "Location.h"
#include "Board.h"
#include "Snake.h"

class Goal
{
public:
    Goal(std::mt19937& rng, Board* board, const Snake* snake);
    void Respawn(std::mt19937& rng, Board* board, const Snake* snake);
    const Location& GetLocation() const;
    void Draw(Board* board) const;
private:
    Location loc;
    static constexpr Color color = RED;
};