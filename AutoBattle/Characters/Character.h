#pragma once
#include <memory>
#include <string>

#include "CharacterClass.h"
#include "../Battle/Battlefield.h"

class Battlefield;

class Character
{
public:
    Character() = default;
    Character(CharacterClass InClass);

    ~Character();
    
    void StartTurn();
    void Attack();
    bool TakeDamage(const float& amount);
    bool IsDead();
    void SetBattlefield(const std::shared_ptr<Battlefield>& battlefield);
    Position GetPosition() const;
    std::string ToString();
    
    CharacterClass Class = CharacterClass::Paladin;
    int Index = 0;
    std::string Name{};
    float Health = 0.f;
    float BaseDamage = 0.f;
    float DamageMultiplier = 1.f;
    std::shared_ptr<GridBox> CurrentBox{};

private:
    void Die();
    void MoveCloserToTarget();
    bool WalkTo(const Position& direction, const std::string& directionName);
    bool IsFacingTarget();

    std::weak_ptr<Character> mTarget{};
    std::shared_ptr<Battlefield> mBattlefield{};
};
