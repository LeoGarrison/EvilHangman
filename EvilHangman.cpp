// EvilHangman2.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include "FamilySet.h"
//#include "TreeMap.h"
using namespace std;

bool debug;

bool PromptYesNoMessage(string msg) {
	while (true) {
		cout << msg << " (y/n) ";
		string response;
		cin >> response;
		if (response == "y")
			return true;
		if (response == "n")
			return false;
		cout << "Please enter y or n." << endl;
	}
}

int PromptGuesses() 
{
	while (true) {
		int len;
		cout << "Please enter how many guesses: ";
		cin >> len;
		if (len > 0)
			return len;
	}
}

int PromptWordLength()
{
    int len;

    // Your code here...

    return len;
}

string PromptGuess(string& guessedLetters)
{
    string guess = "";

    // Your code here...

    return guess;
}

string ChooseFamily(string guess, string guessProgress, FamilySet& set) 
{
    // filter families by guess and guessProgress/guessPattern

    string maxFamily;

    /*
     * Use the iterator to loop through each family and
     * figure out the biggest family size.
     * Return this family
     */

    return maxFamily;
}

bool isWin(string guessedProgress)
{
	return guessedProgress.find('*') == string::npos;
}

void PlayEvilHangman(string file) 
{
    int len, guessesLeft;
    string guessProgress = "";      // correctly guessed positions
    string guessedLetters = "";     // letters already guessed by user

    // Prompt user for word length and number of guesses

    // Load dictionary based on word length
    cout << "Loading dictionary..." << endl;
    FamilySet families(file, len);

    // Show *'s for the guessProgress at the beginning
    for (int i = 0; i < len; i++)
        guessProgress += "*";

	// Actual game loop...
	while (true) {
		cout << endl << endl;
		cout << guessProgress << endl;
		cout << "Guesses Left: " << guessesLeft << endl;
		cout << "Guessed Letters: " << guessedLetters << endl;

		// Your code here

		if (isWin(guessProgress)) {
			cout << endl << "Wow! You won!" << endl;
			return;
		}

		if (guessesLeft <= 0) {
			cout << "Wow... you are a really bad guesser..." << endl;
			cout << "The mystery word was " << families.getRandomWord() << endl;
			return;
		}
	}
}

int main()
{
    string file;
    cout << "Enter file: ";
    cin >> file;				// Can comment out this line and include the following while developing
    //file = "dictionary.txt";  // Convenient to hard code while developing
	
	while (true) {
		debug = PromptYesNoMessage("Turn debugging on?");
		PlayEvilHangman(file);
		if (!PromptYesNoMessage("Would you like to play again? "))
			break;
	}
}

