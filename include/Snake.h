#pragma once
#include "raylib.h"
#include "Location.h"
#include "Board.h"

class Snake
{

private:
    class Segment
    {
    public:
        void InitHead(const Location& loc_in);
        void InitBody();
        void InitBody(const Location& loc_pre);
        void Follow(const Segment& next);
        void MoveBy(const Location& delta_loc_in);
        void Draw(Board& board) const;
        const Location& GetLocation() const;
    private:
        Location loc;
        Color color;
    };
public:
    Snake(const Location& loc_in);
    void MoveBy(const Location& delta_loc_in);
    void Grow();
    void Draw(Board& board) const;
    Location GetNextHeadLocation(const Location& delta_loc) const;
    bool IsInTileExceptEnd(const Location& target) const;
    bool IsInTile(const Location& target) const;
private:
    static constexpr Color headColor = ORANGE;
    static constexpr Color bodyColor = SKYBLUE;
    static constexpr int nSegmentMax = 100;
    Segment segments[nSegmentMax];
    int nSegments = 2;
};