#include "GridBox.h"

GridBox::GridBox(::Position InPosition)
    : Position(InPosition)
{
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
