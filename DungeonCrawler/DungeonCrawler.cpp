#include <iostream>
#include "Character.h"
#include "Enemy.h"

int main(int argc, char* argv[])
{
    Character character{100, 5};
    Enemy enemy{50, 3, Sizes::Medium};

    std::cout << "(Character) " << character.ToString() << std::endl;
    std::cout << "(Enemy) " << enemy.ToString() << std::endl;
    
    return 0;
}
