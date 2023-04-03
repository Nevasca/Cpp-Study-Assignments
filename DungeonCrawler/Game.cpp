#include "Game.h"

#include <iostream>
#include <vector>

#include "Character.h"
#include "Enemy.h"
#include "EnemyFactory.h"

Game::Game()
{
    srand(static_cast<unsigned int>(time(nullptr)));    
}

Game::Game(const int seed)
{
    srand(seed);
}

void Game::Start()
{
    std::string playerName;
    
    std::cout << "How should I call you?" << std::endl;
    std::cin >> playerName;

    std::cout << "Welcome to the challenge, " << playerName << std::endl;

    int totalEnemies;
    std::cout << "How many enemies do you dare to face?" << std::endl;
    std::cin >> totalEnemies;

    Character character{100, 5};
    std::cout << "(Character) " << character.ToString() << std::endl;

    EnemyFactory enemyFactory{};
    std::vector<Enemy> enemies{};
    
    for (int i = 0; i < totalEnemies; i++)
    {
        Enemy enemy = enemyFactory.Create();
        enemies.push_back(enemy);
    }
    
    for (int i = 0; i < totalEnemies; i++)
    {
        std::cout << "(Enemy" << std::to_string(i) << ") " << enemies[i].ToString() << std::endl;
    }
}
