#include "Game.h"

#include <iostream>
#include <vector>
#include "Character.h"
#include "CharacterFactory.h"
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
    std::string playerName = AskPlayerName();

    std::cout << "Welcome to the challenge, " << playerName << std::endl;

    int totalEnemies = AskTotalEnemiesToBattle();
    
    CharacterFactory characterFactory{};
    Character character = characterFactory.Create();
    
    EnemyFactory enemyFactory{};
    std::vector<Enemy> enemies{};
    
    for (int i = 0; i < totalEnemies; i++)
    {
        Enemy enemy = enemyFactory.Create();
        enemies.push_back(enemy);
    }
    
    ShowStatus(character, enemies);
    
    StartBattle(character, enemies);
}

std::string Game::AskPlayerName()
{
    std::string playerName;
    
    std::cout << "How should I call you?" << std::endl;
    std::cin >> playerName;

    return playerName;
}

int Game::AskTotalEnemiesToBattle()
{
    int totalEnemies;
    
    std::cout << "How many enemies do you dare to face?" << std::endl;
    std::cin >> totalEnemies;

    return totalEnemies;
}

void Game::ShowStatus(Character& character, std::vector<Enemy>& enemies)
{
    std::cout << std::endl << std::endl << "------------------ " << std::endl << std::endl << std::endl;
    std::cout << "(Character) " << character.ToString() << std::endl << std::endl;

    for (Enemy& enemy : enemies)
    {
        std::cout << "(Enemy) " << enemy.ToString() << std::endl;
    }

    std::cout << std::endl << std::endl << "------------------ " << std::endl << std::endl << std::endl;
}

void Game::StartBattle(Character& character, std::vector<Enemy>& enemies)
{
    bool isAnEnemyAlive = true;
    
    while(!character.IsDead() && isAnEnemyAlive)
    {
        isAnEnemyAlive = false;
        
        for (Enemy& enemy : enemies)
        {
            Battle(character, enemy);
            
            if(!enemy.IsDead())
            {
                isAnEnemyAlive = true;
            }
            
            if(character.IsDead())
            {
                break;
            }
        } 
    }

    ShowGameOver(character, enemies);

    bool restartGame = AskRestartGame();

    if(restartGame)
    {
        Start();
    }
}

void Game::Battle(Character& character, Enemy& enemy)
{
    if(enemy.IsDead())
    {
        return;
    }
    
    std::cout << "You (" << character.ToString() << ") attacked enemy (" << enemy.ToString() << "). ";
    enemy.ApplyDamage(character.Damage);

    if(enemy.IsDead())
    {
        std::cout << "Enemy was defeated!" << std::endl << std::endl;
        return;
    }
    
    std::cout << "Enemy is now with " << enemy.Health << "." << std::endl;

    std::cout << "Enemy attacked you. ";
    character.ApplyDamage(enemy.Damage);

    if(character.IsDead())
    {
        std::cout << "You have been defeated!" << std::endl << std::endl;
    }
    else
    {
        std::cout << "You are now with " << character.Health << "." << std::endl << std::endl;
    }
}

void Game::ShowGameOver(Character& character, std::vector<Enemy>& enemies)
{
    if(character.IsDead())
    {
        std::cout << "You lose!" << std::endl;
    }
    else
    {
        std::cout << "You won!" << std::endl;
    }

    int totalBigEnemies = 0;
    int totalBigEnemiesDefeated = 0;
    int totalMediumEnemies = 0;
    int totalMediumEnemiesDefeated = 0;
    int totalSmallEnemies = 0;
    int totalSmallEnemiesDefeated = 0;

    for (Enemy& enemy : enemies)
    {
        switch (enemy.Size)
        {
            case Sizes::Big:
                IncrementEnemyReport(enemy, totalBigEnemies, totalBigEnemiesDefeated);
                break;
            case Sizes::Medium:
                IncrementEnemyReport(enemy, totalMediumEnemies, totalMediumEnemiesDefeated);
                break;
            case Sizes::Small:
                IncrementEnemyReport(enemy, totalSmallEnemies, totalSmallEnemiesDefeated);
                break;
        }    
    }

    std::cout << "Enemies defeated:" << std::endl;
    std::cout << "Big:  " << totalBigEnemiesDefeated << "/" << totalBigEnemies << std::endl;
    std::cout << "Medium:  " << totalMediumEnemiesDefeated << "/" << totalMediumEnemies << std::endl;
    std::cout << "Small:  " << totalSmallEnemiesDefeated << "/" << totalSmallEnemies << std::endl << std::endl << std::endl;
}

void Game::IncrementEnemyReport(Enemy& enemy, int& currentTotal, int& currentTotalDefeated)
{
    currentTotal++;

    if(enemy.IsDead())
    {
        currentTotalDefeated++;
    }
}

bool Game::AskRestartGame()
{
    std::cout << "Would you like to restart? [y/n] ";
    char restart;
    std::cin >> restart;
    
    std::cout << std::endl << std::endl;

    return restart == 'y' || restart == 'Y';
}
