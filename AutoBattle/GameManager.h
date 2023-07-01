#pragma once
#include "Characters/Character.h"
#include "Characters/CharacterClass.h"

class GameManager
{
public:
    void Start();

private:
    void Restart();
    bool Setup();
    void CreateBattlefield();
    CharacterClass GetPlayerChoice();
    void AskTotalEnemies();
    void AskCharacterName();
    void CreatePlayerCharacter(CharacterClass characterClass);
    void CreateEnemyCharacters();
    bool PlaceCharacters();
    void NextTurn();
    void HandleTurnEnded();
    Character* HasOnlyOneLeft();
    void ShowGameOver(Character* winner);
    void AskForReplay();

    Battlefield* mBattlefield{};
    Character* mPlayer{};
    std::vector<Character*> mCharacters{};
    int mCurrentTurn = 1;
    int mTotalEnemies = 1;
};
