#include <random>
#include "Sprite.h"

Sprite::Sprite(std::mt19937& rng, Board* board, const Snake* snake, const Goal* goal, const settings::Config& config)
    :
    nWallMax( config.GetWidth() * config.GetHeight() / 20 ),
    pWall( new Wall[nWallMax] )
{
    Init(rng, board, snake, goal);
}
Sprite::~Sprite()
{
    delete [] pWall;
    pWall = nullptr;
}
void Sprite::Init(std::mt19937& rng, Board* board, const Snake* snake, const Goal* goal)
{
    std::uniform_int_distribution<int> xDist( 1, board->GetWidth() - 2 );
    std::uniform_int_distribution<int> yDist( 1, board->GetHeight() - 2 );

    Location newLoc;
    do{
        newLoc.x = xDist( rng );
        newLoc.y = yDist( rng );
    } while( snake->IsInTile( newLoc ) || board->checkExistItem( newLoc ));
        
    pWall[0].SetLocation( newLoc );    
    board->SetItemExist( newLoc );
}
void Sprite::Respawn(std::mt19937& rng, Board* board, const Snake* snake, const Goal* goal)
{
    std::uniform_int_distribution<int> xDist( 1, board->GetWidth() - 2 );
    std::uniform_int_distribution<int> yDist( 1, board->GetHeight() - 2 );

    Location newLoc;
    do{
        newLoc.x = xDist( rng );
        newLoc.y = yDist( rng );
    } while( snake->IsInTile( newLoc ) || board->checkExistItem( newLoc ));
    
    if( nWalls < nWallMax )
    {
        pWall[nWalls].SetLocation( newLoc );
        ++nWalls;
    }
    board->SetItemExist( newLoc );
}
bool Sprite::IsTouch(const Location& loc_in) const
{
    for(int i = 0; i < nWalls; ++i)
    {
        if(pWall[i].GetLocation() == loc_in)
        {
            return true;
        }
    }
    return false;
}
void Sprite::Draw(Board* board) const
{
    for(int i = 0; i < nWalls; ++i)
    {
        pWall[i].Draw(board);
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
void Sprite::Wall::Draw(Board* board) const
{
    board->DrawCell( loc, color );
}