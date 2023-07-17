#include "SkillFactory.h"

#include "Skills/HealSkill.h"
#include "Skills/ThrowSkill.h"

std::shared_ptr<Skill> SkillFactory::CreateSkill(Character& character)
{
    if(character.Class == CharacterClass::Cleric)
    {
        return std::make_shared<HealSkill>(character);
    }
    
    return std::make_shared<ThrowSkill>(character);
}
