#pragma once
#include "Characters/Character.h"
#include "Characters/CharacterClass.h"

class GameManager
{
public:
    GameManager();
    GameManager(int seed);
    
    void Start();
    void Update();
    bool IsFinished();

private:
    void Restart();
    bool Setup();
    void CreateBattlefield();
    CharacterClass GetPlayerChoice();
    void AskCharacterName();
    void AskTotalCharacters();
    void AskTotalTeams();
    bool IsTeamMode() const;
    void SetupCharactersTeams();
    void CreatePlayerCharacter(CharacterClass characterClass);
    void CreateEnemyCharacters();
    bool PlaceCharacters();
    void NextTurn();
    void PrepareNextTurn();
    void CheckWinCondition();
    Character* GetLastSurvivor();
    int GetLastSurvivingTeam() const;
    void ShowGameOver(const Character& winner);
    void ShowGameOver(const int& winningTeamId);
    void AskForReplay();

    std::shared_ptr<Battlefield> mBattlefield{};
    std::shared_ptr<Character> mPlayer{};
    std::vector<std::shared_ptr<Character>> mCharacters{};
    int mCurrentTurn = 1;
    int mTotalEnemies = 1;
    int mTotalTeams = 0;
    bool mIsFinished = false;
};
