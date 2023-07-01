#pragma once

#include "GridBox.h"

class Grid
{
public:
    Grid() = default;
    Grid(int rows, int columns);
    ~Grid();

    GridBox* GetRandomAvailableLocation();
    GridBox* GetBoxAt(const Position& position);
    bool IsValidPosition(const Position& position);
    bool IsPositionOccupied(const Position& position);
    void Draw();
    
    const int XLength = 0;
    const int YLength = 0;

private:
    GridBox* GetRandomLocation();
    
    GridBox*** mBoxes;
};
