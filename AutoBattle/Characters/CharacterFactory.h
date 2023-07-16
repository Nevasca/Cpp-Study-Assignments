#pragma once
#include "Character.h"
#include "CharacterClass.h"

class CharacterFactory
{
public:
    static std::shared_ptr<Character> CreateCharacter(const CharacterClass& characterClass);
    static std::shared_ptr<Character> CreateRandomCharacter();

private:
    static std::string GetRandomName();
};
