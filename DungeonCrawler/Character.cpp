#include "Character.h"

std::string Character::ToString()
{
    return "Health: " + std::to_string(Health) + " | Damage: " + std::to_string(Damage); 
}
