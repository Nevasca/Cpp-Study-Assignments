#pragma once

#include <memory>
#include <vector>

#include "GridBox.h"

class Grid
{
public:
    Grid() = default;
    Grid(int rows, int columns);
    ~Grid();

    std::shared_ptr<GridBox> GetRandomAvailableLocation();
    std::shared_ptr<GridBox> GetBoxAt(const Position& position);
    bool IsValidPosition(const Position& position);
    bool IsPositionOccupied(const Position& position);
    void Draw();
    
    const int XLength = 0;
    const int YLength = 0;

private:
    std::shared_ptr<GridBox> GetRandomLocation();
    std::vector<std::vector<std::shared_ptr<GridBox>>> mBoxes{};
};
