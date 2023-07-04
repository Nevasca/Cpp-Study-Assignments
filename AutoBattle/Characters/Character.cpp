#include "Character.h"

#include <iostream>

Character::Character(CharacterClass InClass)
    : Class(InClass)
{
}

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

    if(IsFacingTarget())
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
    if(mTarget.expired())
    {
        std::cout << "Character " << this->ToString() << " has no valid target" << std::endl;
        return;
    }
    
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

bool Character::IsDead()
{
    return Health <= 0.f;
}

void Character::SetBattlefield(const std::shared_ptr<Battlefield>& battlefield)
{
    mBattlefield = battlefield;
}

Position Character::GetPosition() const
{
    return CurrentBox->Position;
}

std::string Character::ToString()
{
    return "[" + std::to_string(Index) + "]" + Name;
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

bool Character::IsFacingTarget()
{
    auto target = mTarget.lock();
    Position offset = target->GetPosition() - GetPosition();

    return offset == Position::Right
        || offset == Position::Left
        || offset == Position::Up
        || offset == Position::Down;
}
