#pragma once
#include <string>

class Character
{
public:
    int Health;
    int Damage;

    bool IsDead();
    void ApplyDamage(int damage);
    std::string ToString();
};
