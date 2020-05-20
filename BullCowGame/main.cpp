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
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main(int32 argc, const char * argv[]) {
    do {
        IntroduceGame();
        PlayGame();
    } while (AskToPlayAgain());
    
    return 0;
}

void IntroduceGame() {
    // Print intro to game.
    std::cout << "Welcome to Bulls and Cows!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PlayGame() {
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // Loop for the number of turns asking for guesses.
    // TODO: change to while loop once we can validate a guess.
    for (int32 i = 0; i < MaxTries; ++i) {
        FText Guess = GetValidGuess();
        
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls: " << BullCowCount.Bulls;
        std::cout << ". Cows: " << BullCowCount.Cows << std::endl;
        std::cout << std::endl;
    }
    
    // TODO: Summarise game
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
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n";
                break;
            case EGuessStatus::Invalid_Status:
            default:
                break;
        }
        std::cout << std::endl;
    } while (Status != EGuessStatus::OK);
    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Would you like to play again? (y/n): ";
    FText Answer = "";
    std::getline(std::cin, Answer);
    return Answer[0] == 'y' || Answer[0] == 'Y';
}

