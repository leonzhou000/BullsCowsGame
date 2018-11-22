#pragma once
#include "FBullCowGame.h"

// to make syntax UNREAL FRIENDLY
#define Tmap std::map // ***New***
using int32 = int;
using Fstring = std::string;

FBullCowGame::FBullCowGame() { Reset(); } // default constuctor

// const prevent varibles from being changed.
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	Tmap< int32, int32 > WordLengthToMaxTries{ {3,4}, {4,5}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HiddenWord = "fun"; //must be an isogram
	MyHiddenWord = HiddenWord; 

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

											  // loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return FBullCowCount();
}

void FBullCowGame::GenerateWord()
{
	FString word = "";
	std::ofstream Wordlist("ListOfWords.txt");  
	if (Wordlist.fail()) {
		std::cerr << "Error opening file";
		exit(1);
	}
	while (!Wordlist.eof())
	{
		Fstring word;
		getline(Wordlist, word);
	}
}

EGuessStatus FBullCowGame::CheckGuessValidation(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess is not an isogram, 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isnt' all lowcase 
	{
		return EGuessStatus::Not_Lowcerase;
	}
	else if (Guess.length() != MyHiddenWord.length()) // if the word length is word 
	{
		return EGuessStatus::Wrong_Length;
	}
	else { return EGuessStatus::Ok; }
}
// receives a VALID guess, incriments turn, and returns count

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isogram
	if (Word.length() <= 1) { return true; }
	
	Tmap <char, bool> LetterSeen;// set up Tmaps
	for (auto Letter : Word) // For all letters of the word
	{
		Letter = tolower(Letter); // handle mix case of Upper and Lower case
		if (LetterSeen[Letter])// if the letter is the word
		{
			return false;// Not an isogram
		}
		else //Otherwise
		{
			LetterSeen[Letter] = true; // add to LetterSeen
		}
	}
	return true; // for example in case where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) 
	{ 
		if (!islower(Letter)) // if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}

