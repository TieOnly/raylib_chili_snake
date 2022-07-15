#pragma once
#include "Location.h"
#include "raylib.h"

class Board
{
public:
    void DrawCell(const Location& loc, Color color);
    void Draw();
    bool IsInsideBoard(const Location& loc) const;
    const int GetWidth() const;
    const int GetHeight() const;
private:
    static constexpr int dimension = 20;
    static constexpr int posX = 100;
    static constexpr int posY = 50;
    static constexpr int width = 20;
    static constexpr int height = 20;
    static constexpr int padding = 2;
    Color color = BLACK;
};