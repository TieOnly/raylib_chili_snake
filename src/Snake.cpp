#include <assert.h>
#include "Snake.h"
Snake::Snake(const Location& loc_in)
{
    segments[0].InitHead( loc_in );
    segments[1].InitBody( loc_in );
}
void Snake::MoveBy(const Location& delta_loc_in)
{
    for(int i = nSegments - 1; i > 0; --i)
    {
        segments[i].Follow( segments[i - 1] );
    }
    segments[0].MoveBy( delta_loc_in );
}
void Snake::Grow()
{
    if( nSegments < nSegmentMax )
    {
        segments[nSegments].InitBody();
        ++nSegments;
    }
}
void Snake::Draw(Board& board) const
{
    for(int i = 0; i < nSegments; ++i)
    {
        segments[i].Draw( board );
    }
}
Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
    Location l( segments[0].GetLocation() );
    l.Add( delta_loc );
    return l;
}
bool Snake::IsInTileExceptEnd(const Location& target) const
{
    for(int i = 0; i < nSegments - 1; ++i)
    {
        if(segments[i].GetLocation() == target)
        {
            return true;
        }
    }
    return false;
}
bool Snake::IsInTile(const Location& target) const
{
    for(int i = 0; i < nSegments; ++i)
    {
        if(segments[i].GetLocation() == target)
        {
            return true;
        }
    }
    return false;
}

void Snake::Segment::InitHead(const Location& loc_in)
{
    loc = loc_in;
    color = headColor;
}
void Snake::Segment::InitBody()
{
    color = bodyColor;
}
void Snake::Segment::InitBody(const Location& loc_pre)
{
    loc = loc_pre;
    loc = loc - 1;
    color = bodyColor;
}
void Snake::Segment::Follow(const Segment& next)
{
    loc = next.loc;
}
void Snake::Segment::MoveBy(const Location& delta_loc_in)
{
    assert( abs(delta_loc_in.x) + abs(delta_loc_in.y) == 1 );
    loc.Add(delta_loc_in);
}
void Snake::Segment::Draw(Board& board) const
{
    board.DrawCell( loc, color );
}
const Location& Snake::Segment::GetLocation() const
{ 
    return loc;
}
