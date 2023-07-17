#pragma once
#include <memory>

#include "Skills/Skill.h"

class SkillFactory
{
public:
    static std::shared_ptr<Skill> CreateSkill(Character& character);
};
