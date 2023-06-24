#include "Enemy.h"
#include "Sizes.h"

bool Enemy::IsDead()
{
    return Health <= 0;
}

void Enemy::ApplyDamage(int damage)
{
    if(IsDead())
    {
        return;
    }

    Health -= damage;
}

std::string Enemy::ToString()
{
    return "Health: " + std::to_string(Health) + " | Damage: " + std::to_string(Damage) + " | Size: " + ConvertSizeToString(Size);
}
