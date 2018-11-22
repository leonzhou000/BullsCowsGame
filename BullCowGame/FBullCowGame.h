// must have to ensure everything is imported once
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <map>
#include <fstream>

// To make syntax Unreal friendly
using int32 = int;
using FString = std::string;
 
// used to create grouped int (ints only)
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0; 
};

//enumeration is a user-defined data type that consists of integral constants.
//Multi enum you want to use "enum class" this put the enums in there own scope
// great for error checking 
enum EGuessStatus
{
	Invalid_Status,
	Ok,
	Not_Isogram,
	Not_Lowcerase,
	Wrong_Length,
};

class FBullCowGame
{
public:
	FBullCowGame(); // Constuctor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidation(FString) const; 
	void GenerateWord();
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	//See Constuctor for inputs 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
