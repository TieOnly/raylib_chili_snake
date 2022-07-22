#pragma once
#include <random>
#include "Location.h"
#include "raylib.h"

class Board
{
public:
    Board(const int width, const int height, const int dimension);
    ~Board();
    void DrawCell(const Location& loc, Color color);
    void Draw();
    bool IsInsideBoard(const Location& loc) const;
    const int GetWidth() const;
    const int GetHeight() const;
    bool checkExistItem(const Location& loc_in) const;
    void SetItemExist(const Location& next);
    void SetItemEmpty(const Location& next);
    void InitItems(std::mt19937& rng);
    int GetDimension() const;
    void DrawItem();
private:
    static constexpr int posX = 100;
    static constexpr int posY = 50;
    static constexpr int padding = 2;
    int width;
    int height;
    int dimension;
    int amountItems = width * height / 4;
    bool* pHasItems= nullptr;
    Color color = BLACK;
};