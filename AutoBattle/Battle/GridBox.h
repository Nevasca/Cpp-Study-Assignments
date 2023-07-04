#pragma once
#include <string>

#include "../Position.h"

class GridBox
{
public:
    GridBox() = default;
    GridBox(Position InPosition);
    ~GridBox();
    void SetOccupied(bool isOccupied, const std::string& marker = "");
    bool IsOccupied();
    std::string ToString();
    
    Position Position{};
    
private:
    std::string mMarker{};
    bool mIsOccupied = false;
};
