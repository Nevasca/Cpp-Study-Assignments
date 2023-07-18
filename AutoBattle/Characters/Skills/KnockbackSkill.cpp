#include "KnockbackSkill.h"

#include <iostream>

KnockbackSkill::KnockbackSkill(Character& character)
    :Skill(character)
{ }

KnockbackSkill::~KnockbackSkill()
{
    std::cout << "\n ||| Destroying KnockbackSkill |||\n";
}

bool KnockbackSkill::CanCast()
{
    if(!mCharacter.IsFacingTarget())
    {
        return false;
    }
    
    constexpr int chanceToKnockback = 30;

    if(rand() % 100 > chanceToKnockback)
    {
        return false;
    }

    Position knockbackPosition = GetKnockbackPosition();
    const std::shared_ptr<Battlefield> battlefield = mCharacter.GetBattlefield();
    
    return battlefield->CanMoveTo(knockbackPosition);
}

void KnockbackSkill::Cast()
{
    Position knockbackPosition = GetKnockbackPosition();
    std::shared_ptr<Battlefield> battlefield = mCharacter.GetBattlefield();

    auto target = mCharacter.GetTarget().lock();
    battlefield->MoveCharacterTo(*target, knockbackPosition);

    std::cout << mCharacter.ToString() << " knockback " << target->ToString() << std::endl;
    
    battlefield->Draw();
}

Position KnockbackSkill::GetKnockbackPosition()
{
    auto target = mCharacter.GetTarget().lock();
    
    Position targetPostion = target->GetPosition();
    Position directionToTarget = targetPostion - mCharacter.GetPosition();
    Position knockbackPosition = targetPostion + directionToTarget;

    return knockbackPosition;
}
