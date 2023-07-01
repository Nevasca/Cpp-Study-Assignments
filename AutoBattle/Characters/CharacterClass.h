#pragma once

enum class CharacterClass
{
    Paladin = 1,
    Warrior = 2,
    Cleric = 3,
    Archer = 4
};

inline std::string ConvertClassToString(const CharacterClass& characterClass)
{
    switch (characterClass)
    {
        case CharacterClass::Paladin:
            return "Paladin";
        case CharacterClass::Warrior:
            return "Warrior";
        case CharacterClass::Cleric:
            return "Cleric";
        case CharacterClass::Archer:
            return "Archer";
    }

    return "Undefined";
}
