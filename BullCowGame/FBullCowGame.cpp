//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Suvineet Singh on 20/05/2020.
//  Copyright © 2020 Suvineet Singh. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(3); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32) MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
    return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset(int32 WordLength) {
    TMap<int32, FString> WordMap { {3, "dog"}, {4, "park"}, {5, "plane"}, {6, "donkey"}, {7, "account"} };
    
    MyCurrentTry = 1;
    MyHiddenWord = WordMap[WordLength];
    bGameWon = false;
    return;
}

EGuessStatus FBullCowGame::GetGuessValidity(FString Guess) const {
    
    if (Guess.length() != GetHiddenWordLength())
        return EGuessStatus::Incorrect_Length;
    else if (!IsLowerCase(Guess)) {
        return EGuessStatus::Not_Lowercase;
    } else if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    return EGuessStatus::OK;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
    
    if (Guess.length() <= 1) { return true; }
    TMap<char, bool> UsedLetters;
    for (auto c : Guess) {
        c = tolower(c);
        if (UsedLetters[c])
            return false;
        UsedLetters[c] = true;
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const {
    for (char c : Guess) {
        if (c != tolower(c))
            return false;
    }
    return true;
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
    bGameWon = BullCowCount.Bulls == WordLength;

    return BullCowCount;
}
