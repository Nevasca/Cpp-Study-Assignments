#pragma once
#include "Skill.h"

class KnockbackSkill : public Skill
{
public:
    KnockbackSkill(Character& character);
    ~KnockbackSkill() override;

    bool CanCast() override;
    void Cast() override;
    
private:
    Position GetKnockbackPosition();
};
