#pragma once
#include <string>

struct Position
{
    int X = 0;
    int Y = 0;

    static int Distance(const Position& a, const Position& b);
    static Position Right;
    static Position Left;
    static Position Up;
    static Position Down;
    
    std::string ToString() const;
    
    friend Position operator +(const Position& lhs, const Position& rhs);
    friend Position operator -(const Position& lhs, const Position& rhs);
    friend Position operator *(const Position& lhs, const int& rhs);
    friend bool operator==(const Position& lhs, const Position& rhs);
    friend bool operator!=(const Position& lhs, const Position& rhs);
};
