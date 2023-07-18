#pragma once
#include <memory>
#include <string>

#include "CharacterClass.h"
#include "Skills/Skill.h"
#include "../Battle/Battlefield.h"

class Battlefield;
class Skill;

class Character
{
public:
    Character() = default;
    Character(CharacterClass InClass);

    ~Character();
    
    void StartTurn();
    bool TakeDamage(const float& amount);
    void Heal(const float& amount);
    bool IsDead() const;
    void SetBattlefield(const std::shared_ptr<Battlefield>& battlefield);
    void SetSkill(const std::shared_ptr<Skill>& skill);
    bool IsFromSameTeam(const Character& character) const;
    bool HasTarget() const;
    bool IsFacingTarget() const;
    std::weak_ptr<Character> GetTarget();
    std::shared_ptr<Battlefield> GetBattlefield() const;
    Position GetPosition() const;
    std::string ToString() const;
    
    CharacterClass Class = CharacterClass::Paladin;
    int Id = 0;
    int TeamId = -1;
    std::string Name{};
    float BaseHealth = 100.f;
    float Health = 0.f;
    float BaseDamage = 0.f;
    float DamageMultiplier = 1.f;
    std::shared_ptr<GridBox> CurrentBox{};

private:
    void Attack();
    void Die();
    void MoveCloserToTarget();
    bool WalkTo(const Position& direction, const std::string& directionName);

    std::weak_ptr<Character> mTarget{};
    std::shared_ptr<Battlefield> mBattlefield{};
    std::shared_ptr<Skill> mSkill{};
};
