#pragma once
#include <string>

#include "CharacterClass.h"
#include "../Battle/Battlefield.h"

class Battlefield;

class Character
{
public:
    Character() = default;
    Character(CharacterClass InClass);
    
    void StartTurn();
    void Attack();
    bool TakeDamage(const float& amount);
    bool IsDead();
    void SetBattlefield(Battlefield* battlefield, GridBox* startBox);
    Position GetPosition() const;
    std::string ToString();
    
    CharacterClass Class = CharacterClass::Paladin;
    int Index = 0;
    std::string Name{};
    float Health = 0.f;
    float BaseDamage = 0.f;
    float DamageMultiplier = 1.f;
    GridBox* CurrentBox = nullptr;

private:
    void Die();
    void MoveCloserToTarget();
    bool WalkTo(const Position& direction, const std::string& directionName);
    bool IsFacingTarget();

    Character* mTarget = nullptr;
    Battlefield* mBattlefield = nullptr;
};
