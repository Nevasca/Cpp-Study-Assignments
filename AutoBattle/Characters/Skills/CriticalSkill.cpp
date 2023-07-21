#include "CriticalSkill.h"

#include <iostream>

#include "../../Logging.h"

CriticalSkill::CriticalSkill(Character& character)
    : Skill(character)
{ }

CriticalSkill::~CriticalSkill()
{
    LOG_DESTRUCTOR("CriticalSkill")
}

bool CriticalSkill::CanCast()
{
    constexpr int chanceToCritical = 20;
    constexpr float criticalNormalizedHealth = 0.35f;

    float normalizedHealth = mCharacter.Health / mCharacter.BaseHealth;
    
    return normalizedHealth <= criticalNormalizedHealth && rand() % 100 <= chanceToCritical;
}

void CriticalSkill::Cast()
{
    constexpr int criticalDamageMultiplier = 4;
    
    float criticalDamage = mCharacter.BaseDamage * criticalDamageMultiplier;

    auto target = mCharacter.GetTarget().lock();
    bool hasKilledTarget = target->TakeDamage(criticalDamage);

    std::cout << mCharacter.ToString() << " did a critical attack of " << criticalDamage;
    
    if(hasKilledTarget)
    {
        std::cout << " damage and killed " << target->ToString() << std::endl;
    }
    else
    {
        std::cout << " damage on " << target->ToString() << " (" << target->Health << " left)" << std::endl;
    }
}
