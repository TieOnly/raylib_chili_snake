#include "Goal.h"

Goal::Goal(std::mt19937& rng, Board* board, const Snake* snake)
{
    Respawn(rng, board, snake);
}
void Goal::Respawn(std::mt19937& rng, Board* board, const Snake* snake)
{
    std::uniform_int_distribution<int> xDist( 0, board->GetWidth() - 1 );
    std::uniform_int_distribution<int> yDist( 0, board->GetHeight() - 1 );

    Location newLoc;
    do {
        newLoc.x = xDist( rng );
        newLoc.y = yDist( rng );
    } while ( snake->IsInTile( newLoc ) || board->checkExistItem( newLoc ));
    
    board->SetItemExist( newLoc );
    loc = newLoc;
}
const Location& Goal::GetLocation() const
{
    return loc;
}
void Goal::Draw(Board* board) const
{
    board->DrawCell( loc, color );
}

