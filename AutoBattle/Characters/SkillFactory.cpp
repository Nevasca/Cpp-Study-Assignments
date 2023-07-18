#include "SkillFactory.h"

#include "Skills/HealSkill.h"
#include "Skills/KnockbackSkill.h"
#include "Skills/ThrowSkill.h"

std::shared_ptr<Skill> SkillFactory::CreateSkill(Character& character)
{
    switch (character.Class)
    {
        case CharacterClass::Paladin:
            return std::make_shared<KnockbackSkill>(character);
        case CharacterClass::Cleric:
            return std::make_shared<HealSkill>(character);
        case CharacterClass::Archer:
        case CharacterClass::Warrior:
            return std::make_shared<ThrowSkill>(character);
    }

    return std::make_shared<ThrowSkill>(character);
}
