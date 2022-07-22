#include <assert.h>
#include "Board.h"

Board::Board(const int width, const int height, const int dimension)
    :
    width( width ),
    height( height ),
    dimension( dimension ),
    pHasItems( new bool[width * height] )
{
    for(int i = 0; i < width * height; i++)
    {
        pHasItems[i] = false;
    }
}
Board::~Board()
{
    delete [] pHasItems;
    pHasItems = nullptr;
}
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
void Board::InitItems(std::mt19937& rng)
{
    std::uniform_int_distribution<int> xDist(0, width - 1);
    std::uniform_int_distribution<int> yDist(0, height - 1);

    Location newLoc;
    for(int i = 0; i < amountItems; ++i)
    {
        do {
            newLoc.x = xDist( rng );
            newLoc.y = yDist( rng );
        } while( checkExistItem( newLoc ) );

        pHasItems[newLoc.y * width + newLoc.x] = true;
    }

}
bool Board::checkExistItem(const Location& loc_in) const
{
    return pHasItems[loc_in.y * width + loc_in.x];
}
void Board::SetItemExist(const Location& next)
{
    pHasItems[next.y * width + next.x] = true;
}
void Board::SetItemEmpty(const Location& next)
{
    pHasItems[next.y * width + next.x] = false;
}
int Board::GetDimension() const
{
    return dimension;
}
void Board::DrawItem( )
{
    for(int iY = 0; iY < height; iY++)
    {
        for(int iX = 0; iX < width; iX++)
        {
            if(checkExistItem( {iX, iY} ))
            {
                DrawCell({iX, iY}, VIOLET);
            }
        }
    }
}
