#include "Character.h"

#include <iostream>

Character::Character(CharacterClass InClass)
    : Class(InClass)
{
}

void Character::StartTurn()
{
    if(IsDead())
    {
        return;
    }

    mTarget = mBattlefield->FindClosestTarget(this);

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
    auto randomDamage = static_cast<float>(rand() % static_cast<int>(BaseDamage));
    randomDamage *= DamageMultiplier;

    bool hasKilledTarget = mTarget->TakeDamage(randomDamage);

    if(hasKilledTarget)
    {
        std::cout << this->ToString() << " did " << randomDamage << " and killed " << mTarget->ToString() << std::endl;
    }
    else
    {
        std::cout << this->ToString() << " is attacking " << mTarget->ToString() << " and did " << randomDamage << " damage (" << mTarget->Health << " left)" << std::endl;
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

void Character::SetBattlefield(Battlefield* battlefield, GridBox* startBox)
{
    mBattlefield = battlefield;
    CurrentBox = startBox;
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
    Position targetPosition = mTarget->GetPosition();

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

    if(!mBattlefield->MoveCharacterTo(this, desiredPosition))
    {
        return false;
    }

    std::cout << this->ToString() << " walked " << directionName << std::endl;
    mBattlefield->Draw();

    return true;
}

bool Character::IsFacingTarget()
{
    Position offset = mTarget->GetPosition() - GetPosition();

    return offset == Position::Right
        || offset == Position::Left
        || offset == Position::Up
        || offset == Position::Down;
}
