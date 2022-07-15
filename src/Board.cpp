#include <assert.h>
#include "Board.h"

void Board::DrawCell(const Location& loc, Color color)
{
    assert(loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height);
    DrawRectangle(posX + loc.x * dimension + padding, posY + loc.y * dimension + padding, dimension - padding, dimension - padding, color);
}
void Board::Draw()
{
    for(int iY = 0; iY < height; ++iY)
    {
        for(int iX = 0; iX < width; ++iX)
        {
            Location loc = {iX, iY};
            DrawCell(loc, color);
        }
    }
    DrawRectangleLinesEx(
        {float(posX - 5), 
        float(posY - 5), 
        float(width * (dimension) + 10 + padding), 
        float(height * (dimension) + 10 + padding)
        }, 
        5.0f, 
        WHITE
    );
}
bool Board::IsInsideBoard(const Location& loc) const
{
    return (loc.x >= 0 && loc.y >= 0 && loc.x < width && loc.y < height);
}
const int Board::GetWidth() const
{
    return width;
}
const int Board::GetHeight() const
{
    return height;
}
