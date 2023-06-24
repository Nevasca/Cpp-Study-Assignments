#include "Character.h"

std::string Character::ToString()
{
    return "Health: " + std::to_string(Health) + " | Damage: " + std::to_string(Damage); 
}

bool Character::IsDead()
{
    return Health <= 0;
}

void Character::ApplyDamage(int damage)
{
    if(IsDead())
    {
        return;
    }
    
    Health -= damage;
}
