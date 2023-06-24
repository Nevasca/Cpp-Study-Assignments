#pragma once
#include <vector>

#include "Character.h"
#include "Enemy.h"

class Game
{
public:
    Game();
    Game(int seed);
    void Start();
    
private:
    std::string AskPlayerName();
    int AskTotalEnemiesToBattle();
    void StartBattle(Character& character, std::vector<Enemy>& enemies);
    void Battle(Character& character, Enemy& enemy);
    void ShowGameOver(Character& character, std::vector<Enemy>& enemies);
    void IncrementEnemyReport(Enemy& enemy, int& currentTotal, int& currentTotalDefeated);
};
