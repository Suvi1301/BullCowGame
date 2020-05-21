//
//  main.cpp
//  BullCowGame
//
//  This is the console executable that makes use of the BullCowGame class.
//  This acts as the view in a MVC pattern and is responsible for all user
//  interaction. For game logic see the FBullCowGame class.
//
//  Created by Suvineet Singh on 18/05/2020.
//  Copyright © 2020 Suvineet Singh. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string; // Following Unreal standards (user interaction).
using int32 = int;

void IntroduceGame();
void PlayGame(int32 WordLength);
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
int32 AskForWordLength();

FBullCowGame BCGame;

int main(int32 argc, const char * argv[]) {
    do {
        IntroduceGame();
        int32 WordLength = AskForWordLength();
        PlayGame(WordLength);
    } while (AskToPlayAgain());
    
    return 0;
}

void IntroduceGame() {
    // Print intro to game.
    std::cout << "        Welcome to Bulls and Cows!\n";
    std::cout << std::endl;
    std::cout << "          }   {         ___ " << std::endl;
    std::cout << "          (o o)        (o o) " << std::endl;
    std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
    std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
    std::cout << " *  |-,--- |              |------|  * " << std::endl;
    std::cout << "    ^      ^              ^      ^ " << std::endl;
    std::cout << std::endl;
    return;
}

void PlayGame(int32 WordLength) {
    BCGame.Reset(WordLength);
    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess();
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls: " << BullCowCount.Bulls;
        std::cout << ". Cows: " << BullCowCount.Cows << std::endl;
        std::cout << std::endl;
    }
    PrintGameSummary();
}

int32 AskForWordLength() {
    int32 WordLength = 3;
    do {
        std::cout << "What word length would you like to guess? (3 to 7): ";
        std::cin >> WordLength;
        std::cin.ignore();
        if (WordLength < 3 || WordLength > 7)
            std::cout << "Length must be between 3 and 7\n\n";
    } while (WordLength < 3 || WordLength > 7);
    std::cout << std::endl;
    return WordLength;
}

void PrintGameSummary() {
    if (BCGame.IsGameWon())
        std::cout << "WELL DONE! YOU WIN!\n";
    else
        std::cout << "BETTER LUCK NEXT TIME :(\n";
    std::cout << std::endl;
}

FText GetValidGuess() {
    int32 MaxTries = BCGame.GetMaxTries();
    int32 CurrentTry = BCGame.GetCurrentTry();
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    do {
        std::cout << "(Try " << CurrentTry << "/" << MaxTries << ") Enter your guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.GetGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Incorrect_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
            case EGuessStatus::Invalid_Status:
            default:
                break;
        }
    } while (Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Would you like to play again? (y/n): ";
    FText Answer = "";
    std::getline(std::cin, Answer);
    return Answer[0] == 'y' || Answer[0] == 'Y';
}
