#pragma once
#include <vector>

#include "Grid.h"
#include "../Characters/Character.h"

class Character;

class Battlefield
{
public:
    Battlefield(int rows, int columns);
    bool PlaceNewCharacterRandomly(Character* character);
    Character* FindClosestTarget(const Character* character);
    bool MoveCharacterTo(Character* character, const Position& position);
    void RemoveCharacter(Character* character);
    void Draw();
private:
    Grid mGrid{};
    std::vector<Character*> mCharacters{};
};
