#pragma once
#include "../Character.h"

class Character;

class Skill
{
public:
    virtual ~Skill() = default;
    Skill(const Skill& Other) = delete;

    virtual bool CanCast() = 0;
    virtual void Cast() = 0;
    
protected:
    Skill(Character& character);

    Character& mCharacter;
};
