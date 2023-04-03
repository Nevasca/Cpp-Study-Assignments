#pragma once

#include "Enemy.h"

class EnemyFactory
{
    const int minHealth = 5;
    const int maxHealth = 50;
    const int minDamage = 10;
    const int maxDamage = 20;
    const Sizes sizes[3] = {Sizes::Small, Sizes::Medium, Sizes::Big};
    
public:
    Enemy Create();
    
private:
    int GetRandomHealth();
    int GetRandomDamage();
    Sizes GetRandomSize();
};
