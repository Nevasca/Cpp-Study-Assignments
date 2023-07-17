#include "SkillFactory.h"

#include "Skills/ThrowSkill.h"

std::shared_ptr<Skill> SkillFactory::CreateSkill(Character& character)
{
    std::shared_ptr<Skill> skill = std::make_shared<ThrowSkill>(character);

    return skill;
}
