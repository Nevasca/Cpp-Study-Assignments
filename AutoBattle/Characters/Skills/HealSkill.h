#pragma once
#include "Skill.h"

class HealSkill : public Skill
{
public:
    HealSkill(Character& character);
    ~HealSkill() override;

    bool CanCast() override;
    void Cast() override;
};
