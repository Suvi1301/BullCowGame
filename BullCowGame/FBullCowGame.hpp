//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Suvineet Singh on 20/05/2020.
//  Copyright © 2020 Suvineet Singh. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

using FString = std::string; // Following Unreal standards.
using int32 = int;

// All values initialised to zero
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Incorrect_Length,
    Not_Lowercase,
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    EGuessStatus GetGuessValidity(FString Guess) const;
    bool IsGameWon() const;
    
    void Reset(); // TODO: Make a more rich return value.
    
    FBullCowCount SubmitValidGuess(FString Guess);
    
private:
    // Initialised in Constructor
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameWon;
    bool IsIsogram(FString Guess) const;
    bool IsLowerCase(FString Guess) const;
};

#endif /* FBullCowGame_hpp */
