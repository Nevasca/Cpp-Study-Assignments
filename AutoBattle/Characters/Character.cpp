#include "Character.h"

#include <iostream>

Character::Character(CharacterClass InClass)
    : Class(InClass)
{ }

Character::~Character()
{
    std::cout << "\n ||| Destroying character " << this->ToString() << " |||\n";
}

void Character::StartTurn()
{
    if(IsDead())
    {
        return;
    }

    mTarget = mBattlefield->FindClosestTarget(*this);

    if(mTarget.expired())
    {
        std::cout << "No closest target found for " << this->ToString() << std::endl;
        return;
    }

    if(mSkill->CanCast())
    {
        mSkill->Cast();
    }
    else if(IsFacingTarget())
    {
        Attack();
    }
    else
    {
        MoveCloserToTarget();
    }
}

void Character::Attack()
{
    auto randomDamage = static_cast<float>(rand() % static_cast<int>(BaseDamage));
    randomDamage *= DamageMultiplier;

    auto target = mTarget.lock();
    bool hasKilledTarget = target->TakeDamage(randomDamage);

    if(hasKilledTarget)
    {
        std::cout << this->ToString() << " did " << randomDamage << " and killed " << target->ToString() << std::endl;
    }
    else
    {
        std::cout << this->ToString() << " is attacking " << target->ToString() << " and did " << randomDamage << " damage (" << target->Health << " left)" << std::endl;
    }
}

bool Character::TakeDamage(const float& amount)
{
    if(IsDead())
    {
        return true;
    }

    Health -= amount;

    const bool isDead = IsDead();
    
    if(isDead)
    {
        Die();
    }

    return isDead;
}

void Character::Heal(const float& amount)
{
    Health = std::min(Health + amount, BaseHealth);
}

bool Character::IsDead() const
{
    return Health <= 0.f;
}

void Character::SetBattlefield(const std::shared_ptr<Battlefield>& battlefield)
{
    mBattlefield = battlefield;
}

void Character::SetSkill(const std::shared_ptr<Skill>& skill)
{
    mSkill = skill;
}

bool Character::IsFromSameTeam(const Character& character) const
{
    return TeamId >= 0 && TeamId == character.TeamId;
}

bool Character::HasTarget() const
{
    return !mTarget.expired();
}

std::weak_ptr<Character> Character::GetTarget()
{
    return mTarget;
}

std::shared_ptr<Battlefield> Character::GetBattlefield() const
{
    return mBattlefield;
}

Position Character::GetPosition() const
{
    return CurrentBox->Position;
}

std::string Character::ToString() const
{
    if(TeamId != -1)
    {
        return "[" + std::to_string(Id) + " | Team " + std::to_string(TeamId) + "] " + Name;
    }
    
    return "[" + std::to_string(Id) + "] " + Name;
}

void Character::Die()
{
    Health = 0.f;
    mBattlefield->RemoveCharacter(this);
}

void Character::MoveCloserToTarget()
{
    Position position = GetPosition();

    auto target = mTarget.lock();
    Position targetPosition = target->GetPosition();

    if(position.X > targetPosition.X && WalkTo(Position::Left, "left"))
    {
        return;
    }

    if(position.X < targetPosition.X && WalkTo(Position::Right, "right"))
    {
        return;
    }

    if(position.Y > targetPosition.Y && WalkTo(Position::Up, "up"))
    {
        return;
    }

    if(position.Y < targetPosition.Y && WalkTo(Position::Down, "down"))
    {
        return;
    }

    std::cout << this->ToString() << " could not walk in any direction" << std::endl;
    
}

bool Character::WalkTo(const Position& direction, const std::string& directionName)
{
    Position desiredPosition = GetPosition() + direction;

    if(!mBattlefield->MoveCharacterTo(*this, desiredPosition))
    {
        return false;
    }

    std::cout << this->ToString() << " walked " << directionName << std::endl;
    mBattlefield->Draw();

    return true;
}

bool Character::IsFacingTarget() const
{
    if(!HasTarget())
    {
        return false;
    }
    
    auto target = mTarget.lock();
    Position offset = target->GetPosition() - GetPosition();

    return offset == Position::Right
        || offset == Position::Left
        || offset == Position::Up
        || offset == Position::Down;
}
