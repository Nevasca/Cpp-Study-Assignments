#include "Battlefield.h"

#include <iostream>

Battlefield::Battlefield(int rows, int columns)
    : mGrid(Grid{rows, columns})
{
}

bool Battlefield::PlaceNewCharacterRandomly(Character* character)
{
    GridBox* randomLocation = mGrid.GetRandomAvailableLocation();

    if(randomLocation == nullptr)
    {
        std::cout << "It was not possible to place " << character->ToString() << " at the grid" << std::endl;
        return false;
    }

    randomLocation->SetOccupied(true, std::to_string(character->Index));
    character->SetBattlefield(this, randomLocation);
    mCharacters.push_back(character);

    std::cout << character->ToString() << " placed at " << randomLocation->Position.ToString() << std::endl;
    
    return true;
}

Character* Battlefield::FindClosestTarget(const Character* character)
{
    Character* closestTarget = nullptr;
    int closestDistance = -1;

    for (Character* target : mCharacters)
    {
        if(target->Index == character->Index)
        {
            continue;
        }

        int distance = Position::Distance(character->GetPosition(), target->GetPosition());

        if(closestDistance != -1 && distance > closestDistance)
        {
            continue;
        }

        closestDistance = distance;
        closestTarget = target;
    }

    return closestTarget;
}

bool Battlefield::MoveCharacterTo(Character* character, const Position& position)
{
    if(!mGrid.IsValidPosition(position))
    {
        return false;
    }

    if(mGrid.IsPositionOccupied(position))
    {
        return false;
    }

    character->CurrentBox->SetOccupied(false);
    character->CurrentBox = mGrid.GetBoxAt(position);
    character->CurrentBox->SetOccupied(true, std::to_string(character->Index));

    return true;
}

void Battlefield::RemoveCharacter(Character* character)
{
    character->CurrentBox->SetOccupied(false);
    mCharacters.erase(std::remove(mCharacters.begin(), mCharacters.end(), character), mCharacters.end());
}

void Battlefield::Draw()
{
    mGrid.Draw();
}
