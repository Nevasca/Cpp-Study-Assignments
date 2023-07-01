#pragma once
#include "Character.h"
#include "CharacterClass.h"

class CharacterFactory
{
public:
    static Character* CreateCharacter(CharacterClass characterClass);
    static Character* CreateRandomCharacter();

private:
    static std::string GetRandomName();
};
