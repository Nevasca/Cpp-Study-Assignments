#include "ThrowSkill.h"

#include <iostream>

#include "../../Logging.h"

ThrowSkill::ThrowSkill(Character& InCharacter)
    : Skill(InCharacter)
{ }

ThrowSkill::~ThrowSkill()
{
    LOG_DESTRUCTOR("ThrowSkill")
}

bool ThrowSkill::CanCast()
{
    constexpr int chanceToThrow = 20;
    
    return !mCharacter.IsFacingTarget() && rand() % 100 <= chanceToThrow;
}

void ThrowSkill::Cast()
{
    if(!mCharacter.HasTarget())
    {
        std::cout << "Character has no valid target to cast skill!" << std::endl;
        return;
    }
    
    std::weak_ptr<Character> targetPtr = mCharacter.GetTarget();
    const auto target = targetPtr.lock();

    constexpr float throwDamage = 30.f;
    const bool hasKilledTarget = target->TakeDamage(throwDamage);

    if(hasKilledTarget)
    {
        std::cout << mCharacter.ToString() << " threw a rock doing " << throwDamage << " damage and killed " << target->ToString() << std::endl;
    }
    else
    {
        std::cout << mCharacter.ToString() << " threw a rock at " << target->ToString() << " and did " << throwDamage << " damage (" << target->Health << " left)" << std::endl;
    }
}
