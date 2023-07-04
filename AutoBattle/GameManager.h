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
    Character* GetLastSurvivor();
    void ShowGameOver(const Character& winner);
    void AskForReplay();

    std::shared_ptr<Battlefield> mBattlefield{};
    std::shared_ptr<Character> mPlayer{};
    std::vector<std::shared_ptr<Character>> mCharacters{};
    int mCurrentTurn = 1;
    int mTotalEnemies = 1;
};
