#include "GridBox.h"

#include <iostream>

GridBox::GridBox(::Position InPosition)
    : Position(InPosition)
{
}

GridBox::~GridBox()
{
    std::cout << "\n ||| Destroying gridbox " << this->Position.ToString() << " |||\n";
}

void GridBox::SetOccupied(bool isOccupied, const std::string& marker)
{
    mIsOccupied = isOccupied;
    mMarker = marker;
}

bool GridBox::IsOccupied()
{
    return mIsOccupied;
}

std::string GridBox::ToString()
{
    return mIsOccupied ? "[" + mMarker + "]" : "[ ]";
}
