#include <random>
#include "Sprite.h"

Sprite::Sprite(std::mt19937& rng, Board& board, const Snake& snake, const Goal& goal)
{
    Init(rng, board, snake, goal);
}
bool Sprite::IsUniqueOwn(const Location& newLoc) const
{
    for(int i = 0; i < nWalls; ++i)
    {
        if(walls[i].GetLocation() == newLoc)
        {
            return false;
        }
    }
    return true;
}
void Sprite::Init(std::mt19937& rng, Board& board, const Snake& snake, const Goal& goal)
{
    std::uniform_int_distribution<int> xDist( 1, board.GetWidth() - 2 );
    std::uniform_int_distribution<int> yDist( 1, board.GetHeight() - 2 );

    Location newLoc;
    do{
        newLoc.x = xDist( rng );
        newLoc.y = yDist( rng );
    } while( snake.IsInTile( newLoc ) || goal.IsInTile( newLoc ));
        
    walls[0].SetLocation( newLoc );    
}
void Sprite::Respawn(std::mt19937& rng, Board& board, const Snake& snake, const Goal& goal)
{
    std::uniform_int_distribution<int> xDist( 1, board.GetWidth() - 2 );
    std::uniform_int_distribution<int> yDist( 1, board.GetHeight() - 2 );

    Location newLoc;
    do{
        newLoc.x = xDist( rng );
        newLoc.y = yDist( rng );
    } while( snake.IsInTile( newLoc ) || goal.IsInTile( newLoc ) || !IsUniqueOwn( newLoc ));
    
    if( nWalls < nWallMax )
    {
        walls[nWalls].SetLocation( newLoc );
        ++nWalls;
    }
}
bool Sprite::IsTouch(const Location& loc_in) const
{
    for(int i = 0; i < nWalls; ++i)
    {
        if(walls[i].GetLocation() == loc_in)
        {
            return true;
        }
    }
    return false;
}
void Sprite::Draw(Board& board) const
{
    for(int i = 0; i < nWalls; ++i)
    {
        walls[i].Draw(board);
    }
}

void Sprite::Wall::SetLocation(const Location& newLoc)
{
    loc = newLoc;
}
const Location& Sprite::Wall::GetLocation() const
{
    return loc;
}
void Sprite::Wall::Draw(Board& board) const
{
    board.DrawCell( loc, color );
}