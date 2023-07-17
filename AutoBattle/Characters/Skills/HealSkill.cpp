#include "HealSkill.h"

#include <iostream>

HealSkill::HealSkill(Character& character)
    : Skill(character)
{ }

HealSkill::~HealSkill()
{
    std::cout << "\n ||| Destroying HealSkill |||\n";
}

bool HealSkill::CanCast()
{
    constexpr int chanceToHeal = 20;

    return mCharacter.Health < mCharacter.BaseHealth && rand() % 100 <= chanceToHeal;
}

void HealSkill::Cast()
{
    constexpr float healAmount = 30.f;
    
    mCharacter.Heal(healAmount);
    std::cout << mCharacter.ToString() << " used heal and recovered " << healAmount << ". Now with " << mCharacter.Health << std::endl;
}
