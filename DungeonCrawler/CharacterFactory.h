#pragma once
#include "Character.h"

class CharacterFactory
{
    const int baseHealth = 100;
    const int baseDamage = 20;
public:
    Character Create();   
};
