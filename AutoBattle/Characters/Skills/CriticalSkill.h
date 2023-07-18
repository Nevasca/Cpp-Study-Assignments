#pragma once
#include "Skill.h"

class CriticalSkill : public Skill
{
public:
    CriticalSkill(Character& character);

    ~CriticalSkill() override;
    bool CanCast() override;
    void Cast() override;
};
