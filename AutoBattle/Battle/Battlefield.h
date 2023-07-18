#pragma once
#include <vector>

#include "Grid.h"
#include "../Characters/Character.h"

class Character;

class Battlefield
{
public:
    Battlefield(int rows, int columns);
    ~Battlefield();
    bool PlaceNewCharacterRandomly(const std::shared_ptr<Character>& character);
    std::weak_ptr<Character> FindClosestTarget(const Character& character);
    bool CanMoveTo(const Position& position);
    bool MoveCharacterTo(Character& character, const Position& position);
    void RemoveCharacter(Character* characterToRemove);
    void Draw();
private:
    Grid mGrid{};
    std::vector<std::weak_ptr<Character>> mCharacters{};
};
