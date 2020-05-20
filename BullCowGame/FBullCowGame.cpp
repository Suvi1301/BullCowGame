//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Suvineet Singh on 20/05/2020.
//  Copyright © 2020 Suvineet Singh. All rights reserved.
//

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32) MyHiddenWord.length(); }

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    const FString HiddenWord = "planet";
    
    MyMaxTries = MAX_TRIES;
    MyCurrentTry = 1;
    MyHiddenWord = HiddenWord;
    return;
}

bool FBullCowGame::IsGameWon() const {
    return true;
}

EGuessStatus FBullCowGame::GetGuessValidity(FString Guess) const {
    
    if (Guess.length() != GetHiddenWordLength())
        return EGuessStatus::Incorrect_Length;
    else if (false) {
        return EGuessStatus::Not_Lowercase;
    } else if (false) {
        return EGuessStatus::Not_Isogram;
    }
    return EGuessStatus::OK;
}

// Receives a valid guess and increments try and return count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    int32 WordLength = (int32) MyHiddenWord.length();
    
    for (int32 i = 0; i < WordLength; ++i) {
        for (int32 j = 0; j < WordLength; ++j) {
            if (MyHiddenWord[i] == Guess[j] && i == j)
                BullCowCount.Bulls++;
            else if (MyHiddenWord[i] == Guess[j])
                BullCowCount.Cows++;
        }
    }
    
    return BullCowCount;
}
