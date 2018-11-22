 /* *****Notes*****
This is the consule executable , that makes use of the bullcow class 
Tis act as the view in a MVC pattern, and is responisable for all 
user interaction. For game logic see the FBullCowGame Class.
'constexpr' states a final number
'getline()' grabs multiple stirngs in one line, like "Donkey Kong"
Leon Zhou
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"
/*
# represents a "preprocessor directive"
#include -imports library code '<>' standard libraries
#include "File" for self created file 
*/

// To make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

//function prototypes as outside of class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool PlayAgain();

FBullCowGame BCGame; // instantiate a new game,
//This alllow to have more than one players per game.

// the entry point for our application
int main() 
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = PlayAgain(); 
	}while (bPlayAgain);
	return 0;
}// exit the application 

void PrintIntro() { 
	//Intro the game
	//***Print line***
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	/*or
	printf("Hello World\n");
	This is without the use of a "namespace"
	*/
	std::cout << "\n";
	return;
}//intro 
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries  = BCGame.GetMaxTries();	//Number of guesses in the game

	// loop asking for guess white game is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries))
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to game 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return; 
}//play game
// loop continually until the user gives a valid guess.
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from player and repeat it back 
		int32 Tries = BCGame.GetCurrentTry();
		std::cout << "Try: " << Tries << " of " << BCGame.GetMaxTries();
		std::cout << "\nPlease enter your guess: ";
		std::getline(std::cin, Guess);
		// Check the guess 
		Status = BCGame.CheckGuessValidation(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Lowcerase:
			std::cout << "Please enter word in all lowercase. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "There are repeated letters in your word. \n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::Ok); //keep looping until theres no error
	return Guess;
}
bool PlayAgain()
{
	std::cout << "Do you want to play with the same hidden word again? Y/N\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
void PrintGameSummary()
{
	if(BCGame.IsGameWon() == true)
	{
		std::cout << "You guessed The Word!!!\n";
	}
	else
	{
		std::cout << "You Failed To Guess The Word\n";
	}
}