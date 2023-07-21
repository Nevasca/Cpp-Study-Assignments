#include "GridBox.h"

#include <iostream>

#include "../Logging.h"

GridBox::GridBox(::Position InPosition)
    : Position(InPosition)
{
}

GridBox::~GridBox()
{
    LOG_DESTRUCTOR("GridBox " + this->Position.ToString())
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
