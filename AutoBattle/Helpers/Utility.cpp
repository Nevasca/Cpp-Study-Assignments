#include "Utility.h"

#include <iostream>

int Utility::AskPositiveNumber(const std::string& message, const int& min)
{
    int number = -1;

    std::cout << message << std::endl;

    while (!(std::cin >> number) || number < min)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << message << std::endl;
    }

    return number;
}
