#include "Utility.h"

#include <iostream>

int Utility::AskPositiveNumber(const std::string& message, const int& min)
{
    int number = -1;

    do
    {
        std::cout << message << std::endl;
        
        std::cin.clear();
        std::cin >> number;
    }
    while (!std::cin && number < min);

    return number;
}
