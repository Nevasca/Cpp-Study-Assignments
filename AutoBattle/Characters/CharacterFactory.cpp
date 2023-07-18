#include "CharacterFactory.h"

#include <iostream>
#include <memory>

#include "SkillFactory.h"

std::shared_ptr<Character> CharacterFactory::CreateCharacter(const CharacterClass& characterClass)
{
    std::shared_ptr<Character> character = std::make_shared<Character>(characterClass);
    character->BaseHealth = 100.f;
    character->Health = 100.f;
    character->BaseDamage = 20.f;
    character->Name = GetRandomName();
    character->DamageMultiplier = 1.f + rand() % 4;

    const std::shared_ptr<Skill> skill = SkillFactory::CreateSkill(*character);
    character->SetSkill(skill);

    return character;
}

std::shared_ptr<Character> CharacterFactory::CreateRandomCharacter()
{
    constexpr CharacterClass classes[]{CharacterClass::Paladin, CharacterClass::Warrior, CharacterClass::Cleric, CharacterClass::Archer};
    
    int randomIndex = rand() % static_cast<int>(std::size(classes));
    
    return CreateCharacter(classes[randomIndex]);
}

std::string CharacterFactory::GetRandomName()
{
    const std::string defaultNames[]{ "Quyn", "Ash", "Gary", "Misty", "Brock", "Blue", "Red", "Nessa"};
    
    int randomIndex = rand() % static_cast<int>(std::size(defaultNames));
    
    return defaultNames[randomIndex];
}
