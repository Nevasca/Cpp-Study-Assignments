#include "GameManager.h"

#include <algorithm>
#include <iostream>
#include <random>

#include "Characters/CharacterFactory.h"
#include "Helpers/Utility.h"

GameManager::GameManager()
{
    srand(static_cast<unsigned int>(time(nullptr)));
}

GameManager::GameManager(int seed)
{
    srand(seed);
}

void GameManager::Start()
{
    if(!Setup())
    {
        std::cout << "It was not possible to setup the game";
        mIsFinished = true;
        
        return;
    }

    mBattlefield->Draw();
}

void GameManager::Update()
{
    NextTurn();
    CheckWinCondition();
    
    if(mIsFinished)
    {
        AskForReplay();
    }
    else
    {
        PrepareNextTurn();
    }
}

void GameManager::Restart()
{
    mIsFinished = false;
    
    std::cout << std::endl << std::endl;

    mBattlefield.reset();
    
    mCharacters.clear();
    mPlayer.reset();
    
    mCurrentTurn = 1;
    mTotalEnemies = 1;

    Start();
}

bool GameManager::Setup()
{
    CreateBattlefield();
    CharacterClass chosenClass = GetPlayerChoice();
    CreatePlayerCharacter(chosenClass);
    AskTotalTeams();
    AskTotalCharacters();
    CreateEnemyCharacters();

    auto rng = std::default_random_engine{};
    std::shuffle(mCharacters.begin(), mCharacters.end(), rng);
    
    SetupCharactersTeams();

    if(!PlaceCharacters())
    {
        return false;
    }

    return true;
}

void GameManager::CreateBattlefield()
{
    std::cout << "Time to chose where you are going to battle" << std::endl;

    int rows = Utility::AskNumber("How many rows (Y)?\n", 1);
    int columns = Utility::AskNumber("How many columns (X)?\n", 1);

    mBattlefield = std::make_shared<Battlefield>(rows, columns);
}

CharacterClass GameManager::GetPlayerChoice()
{
    bool isValidChoice = false;
    char choice;
    CharacterClass chosenClass = CharacterClass::Paladin;

    do
    {
        isValidChoice = true;

        std::cout << std::endl << "Choose between one of these classes:" << std::endl;
        std::cout << "[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer" << std::endl;

        std::cin >> choice;

        switch (choice)
        {
            case '1':
                chosenClass = CharacterClass::Paladin;
                break;
            case '2':
                chosenClass = CharacterClass::Warrior;
                break;
            case '3':
                chosenClass = CharacterClass::Cleric;
                break;
            case '4':
                chosenClass = CharacterClass::Archer;
                break;
            default:
                isValidChoice = false;
                break;
        }
    }
    while (!isValidChoice);

    return chosenClass;
}

void GameManager::AskTotalCharacters()
{
    std::string message{};
    
    if(IsTeamMode())
    {
        message = "How many enemies or maybe allies are you prepared to face?\n";
    }
    else
    {
        message = "How many enemies are you prepared to face?\n";
    }
    
    mTotalEnemies = Utility::AskNumber(message, 1);

    std::cout << std::endl;
}

void GameManager::AskTotalTeams()
{
    mTotalTeams = Utility::AskNumber("\nHow many teams (1 or less for free for all)?\n", 0);

    std::cout << std::endl;
}

bool GameManager::IsTeamMode() const
{
    return mTotalTeams > 1;
}

void GameManager::SetupCharactersTeams()
{
    if(!IsTeamMode())
    {
        return;
    }

    int teamId = 0;
    
    for (const std::shared_ptr<Character>& character : mCharacters)
    {
        character->TeamId = teamId;

        teamId = (teamId + 1) % mTotalTeams;
    }
}

void GameManager::AskCharacterName()
{
    std::cout << std::endl;
    std::cout << "What is your name, great " << ConvertClassToString(mPlayer->Class) << "?" << std::endl;

    std::string name;
    std::cin >> name;

    mPlayer->Name = name;
}

void GameManager::CreatePlayerCharacter(CharacterClass characterClass)
{
    mPlayer = CharacterFactory::CreateCharacter(characterClass);
    mPlayer->Id = 0;

    mCharacters.push_back(mPlayer);

    std::cout << std::endl << std::endl;
    std::cout << "Player class choice: " << ConvertClassToString(characterClass);

    AskCharacterName();
}

void GameManager::CreateEnemyCharacters()
{
    for (int i = 0; i < mTotalEnemies; ++i)
    {
        std::shared_ptr<Character> enemyCharacter = CharacterFactory::CreateRandomCharacter();
        enemyCharacter->Id = i + 1;
        mCharacters.push_back(enemyCharacter);

        std::cout << enemyCharacter->ToString() << " class choice: " << ConvertClassToString(enemyCharacter->Class) << std::endl;
    }

    std::cout << std::endl << std::endl;
}

bool GameManager::PlaceCharacters()
{
    for (const std::shared_ptr<Character>& character : mCharacters)
    {
        character->SetBattlefield(mBattlefield);
        
        if(!mBattlefield->PlaceNewCharacterRandomly(character))
        {
            return false;
        }
    }

    return true;
}

void GameManager::NextTurn()
{
    std::cout << "-- TURN " << std::to_string(mCurrentTurn) << " --" << std::endl << std::endl;

    for (const std::shared_ptr<Character>& character : mCharacters)
    {
        character->StartTurn();
    }

    mCurrentTurn++;
}

void GameManager::PrepareNextTurn()
{
    std::cout << std::endl << std::endl;
    std::cout << "Click on any key to start the next turn... ";

    std::cin.get();
    
    std::cout << std::endl << std::endl;
}

void GameManager::CheckWinCondition()
{
    if(IsTeamMode())
    {
        const int winningTeamId = GetLastSurvivingTeam();

        if(winningTeamId >= 0)
        {
            mIsFinished = true;
            ShowGameOver(winningTeamId);
        }
    }
    else
    {
        const Character* winner = GetLastSurvivor();

        if(winner)
        {
            mIsFinished = true;
            ShowGameOver(*winner);
        }
    }
}

bool GameManager::IsFinished()
{
    return mIsFinished;
}

Character* GameManager::GetLastSurvivor()
{
    Character* winner = nullptr;
    int totalAlive = 0;

    for (const std::shared_ptr<Character>& character : mCharacters)
    {
        if(character->IsDead())
        {
            continue;
        }

        totalAlive++;
        winner = character.get();
    }

    return totalAlive == 1 ? winner : nullptr;
}

int GameManager::GetLastSurvivingTeam() const
{
    int winningTeamId = -1;
    
    for (const std::shared_ptr<Character>& character : mCharacters)
    {
        if(character->IsDead())
        {
            continue;
        }

        if(winningTeamId != -1 && character->TeamId != winningTeamId)
        {
            return -1;
        }

        winningTeamId = character->TeamId;
    }

    return winningTeamId;
}

void GameManager::ShowGameOver(const Character& winner)
{
    std::cout << std::endl << std::endl;
    bool hasPlayerWon = winner.Id == mPlayer->Id;

    if(hasPlayerWon)
    {
        std::cout << "You have won the battle, " << winner.Name << "!" << std::endl;
        std::cout << "You are the best living " << ConvertClassToString(winner.Class) << std::endl;
    }
    else
    {
        std::cout << "You have lost the battle... " << winner.Name << " survived." << std::endl;
        std::cout << "What a tough " << ConvertClassToString(winner.Class) << "!" << std::endl;
    }
}

void GameManager::ShowGameOver(const int& winningTeamId)
{
    const bool hasPlayerWon = mPlayer->TeamId == winningTeamId;
    const std::string playerClass = ConvertClassToString(mPlayer->Class);
    
    std::cout << std::endl << std::endl;
    std::cout << "Team " << winningTeamId << " has won the battle!" << std::endl;

    if(hasPlayerWon)
    {
        std::cout << "And you have contributed to their victory. You're an impressive " << playerClass << "!" << std::endl;
    }
    else
    {
        std::cout << "Your team lost, better luck next time, " << playerClass << "." << std::endl;
    }
}

void GameManager::AskForReplay()
{
    std::cout << std::endl << std::endl;
    std::cout << "Play again? [Y/N]" << std::endl;

    char replay;
    std::cin >> replay;

    if(replay == 'Y' || replay == 'y')
    {
        Restart();
    }
}
