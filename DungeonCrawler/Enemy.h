#pragma once
#include <string>

#include "Sizes.h"

class Enemy
{
public:
    int Health;
    int Damage;
    Sizes Size;

    std::string ToString();
};
