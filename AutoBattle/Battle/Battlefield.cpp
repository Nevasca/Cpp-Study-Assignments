#include "Battlefield.h"

#include <iostream>

#include "../Logging.h"

Battlefield::Battlefield(int rows, int columns)
    : mGrid(Grid{rows, columns})
{
}

Battlefield::~Battlefield()
{
    LOG_DESTRUCTOR("Battlefield")
}

bool Battlefield::PlaceNewCharacterRandomly(const std::shared_ptr<Character>& character)
{
    std::shared_ptr<GridBox> randomLocation = mGrid.GetRandomAvailableLocation();

    if(randomLocation == nullptr)
    {
        std::cout << "It was not possible to place " << character->ToString() << " at the grid" << std::endl;
        return false;
    }

    randomLocation->SetOccupied(true, std::to_string(character->Id));
    character->CurrentBox = randomLocation;
    mCharacters.push_back(character);

    std::cout << character->ToString() << " placed at " << randomLocation->Position.ToString() << std::endl;
    
    return true;
}

std::weak_ptr<Character> Battlefield::FindClosestTarget(const Character& character)
{
    std::weak_ptr<Character> closestTarget{};
    int closestDistance = -1;

    for (const std::weak_ptr<Character>& targetPtr : mCharacters)
    {
        auto target = targetPtr.lock();
        
        if(target->Id == character.Id)
        {
            continue;
        }

        if(character.IsFromSameTeam(*target))
        {
            continue;
        }

        int distance = Position::Distance(character.GetPosition(), target->GetPosition());

        if(closestDistance != -1 && distance > closestDistance)
        {
            continue;
        }

        closestDistance = distance;
        closestTarget = target;
    }

    return closestTarget;
}

bool Battlefield::CanMoveTo(const Position& position)
{
    return mGrid.IsValidPosition(position) && !mGrid.IsPositionOccupied(position); 
}

bool Battlefield::MoveCharacterTo(Character& character, const Position& position)
{
    if(!CanMoveTo(position))
    {
        return false;
    }

    character.CurrentBox->SetOccupied(false);
    character.CurrentBox = mGrid.GetBoxAt(position);
    character.CurrentBox->SetOccupied(true, std::to_string(character.Id));

    return true;
}

void Battlefield::RemoveCharacter(Character* characterToRemove)
{
    characterToRemove->CurrentBox->SetOccupied(false);

    mCharacters.erase(std::remove_if(mCharacters.begin(), mCharacters.end(),
        [characterToRemove](const std::weak_ptr<Character>& character)
        {
            return character.lock().get() == characterToRemove;
        }), mCharacters.end());
}

void Battlefield::Draw()
{
    mGrid.Draw();
}
