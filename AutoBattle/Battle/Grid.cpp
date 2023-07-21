#include "Grid.h"

#include <iostream>
#include <sstream>

#include "../Logging.h"

Grid::Grid(int rows, int columns)
    : XLength(columns), YLength(rows)
{
    for (int y = 0; y < rows; ++y)
    {
        std::vector<std::shared_ptr<GridBox>> row{};
        row.reserve(columns);
        
        for (int x = 0; x < columns; ++x)
        {
            row.push_back(std::make_shared<GridBox>(Position{x, y}));
        }
        
        mBoxes.push_back(row);
    }

    std::cout << "The battlefield has been created" << std::endl;
}

Grid::~Grid()
{
    LOG_DESTRUCTOR("Grid")
}

std::shared_ptr<GridBox> Grid::GetRandomAvailableLocation()
{
    int i = 0;
    int maxIterations = YLength * XLength;
    std::shared_ptr<GridBox> randomLocation{};

    do
    {
        randomLocation = GetRandomLocation();
    }
    while (randomLocation->IsOccupied() && i < maxIterations);

    if(i == maxIterations)
    {
        return nullptr;
    }

    return randomLocation;
}

std::shared_ptr<GridBox> Grid::GetRandomLocation()
{
    int randomRow = rand() % YLength;
    int randomColumn = rand() % XLength;
    
    return mBoxes[randomRow][randomColumn];
}

std::shared_ptr<GridBox> Grid::GetBoxAt(const Position& position)
{
    return mBoxes[position.Y][position.X];
}

bool Grid::IsPositionOccupied(const Position& position)
{
    return GetBoxAt(position)->IsOccupied();
}

void Grid::Draw()
{
    std::stringstream stream{};
    stream << std::endl << std::endl;

    for (int y = 0; y < YLength; ++y)
    {
        for (int x = 0; x < XLength; ++x)
        {
            stream << mBoxes[y][x]->ToString();
        }

        stream << std::endl;
    }

    stream << std::endl << std::endl;
    
    std::cout << stream.str();
}

bool Grid::IsValidPosition(const Position& position)
{
    return position.Y >= 0 && position.Y < YLength && position.X >= 0 && position.X < XLength;
}
