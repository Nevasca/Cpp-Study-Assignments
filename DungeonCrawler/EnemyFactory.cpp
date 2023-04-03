#include "EnemyFactory.h"

Enemy EnemyFactory::Create()
{
    return Enemy{GetRandomHealth(), GetRandomDamage(), GetRandomSize()};
}

int EnemyFactory::GetRandomHealth()
{
    return rand() % maxHealth + minHealth;
}

int EnemyFactory::GetRandomDamage()
{
    return rand() % maxDamage + minDamage;
}

Sizes EnemyFactory::GetRandomSize()
{
    int randomIndex = rand() % std::size(sizes);
    
    return sizes[randomIndex];
}
