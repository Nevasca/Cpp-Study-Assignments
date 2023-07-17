#pragma once
#include "Skill.h"

class ThrowSkill : public Skill
{
public:
    ThrowSkill(Character& character);
    ~ThrowSkill() override;

    bool CanCast() override;
    void Cast() override;
};
