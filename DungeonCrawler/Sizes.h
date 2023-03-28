#pragma once

enum class Sizes
{
    Big,
    Medium,
    Small
};

inline std::string ConvertSizeToString(Sizes size)
{
    switch (size)
    {
        case Sizes::Small:
            return "Small";
        case Sizes::Medium:
            return "Medium";
        case Sizes::Big:
            return "Big";
        default:
            return "Invalid";
    }
}

