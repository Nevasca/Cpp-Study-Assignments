#pragma once

#include <string>
#include "Sizes.h"

class Enemy
{
public:
    int Health;
    int Damage;
    Sizes Size;

    bool IsDead();
    void ApplyDamage(int damage);
    std::string ToString();
};
