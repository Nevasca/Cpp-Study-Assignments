#include "Position.h"

Position Position::Right{1, 0};
Position Position::Left{-1, 0};
Position Position::Up{0, -1};
Position Position::Down{0, 1};

int Position::Distance(const Position& a, const Position& b)
{
    return abs(b.X - a.X) + abs(b.Y - a.Y);
}

std::string Position::ToString() const
{
    return "[" + std::to_string(X) + ", " + std::to_string(Y) + "]";
}

Position operator +(const Position& lhs, const Position& rhs)
{
    return Position{lhs.X + rhs.X, lhs.Y + rhs.Y};
}

Position operator-(const Position& lhs, const Position& rhs)
{
    return Position{lhs.X - rhs.X, lhs.Y - rhs.Y};
}

Position operator*(const Position& lhs, const int& rhs)
{
    return Position{lhs.X * rhs, lhs.Y * rhs};
}

bool operator==(const Position& lhs, const Position& rhs)
{
    return lhs.X == rhs.X
        && lhs.Y == rhs.Y;
}

bool operator!=(const Position& lhs, const Position& rhs)
{
    return !(lhs == rhs);
}
