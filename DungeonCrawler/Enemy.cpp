#include "Enemy.h"
#include "Sizes.h"

std::string Enemy::ToString()
{
    return "Health: " + std::to_string(Health) + " | Damage: " + std::to_string(Damage) + " | Size: " + ConvertSizeToString(Size);
}
