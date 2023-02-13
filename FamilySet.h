#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class FamilySet
{
public:
    FamilySet(string dictFile, int len);
	// Initializes from a word file where the word
	// must be of length len.

	~FamilySet();

	void filterFamilies(string letter, string guessPattern);

	void setFamily(string family);
	string getRandomWord();

	vector<string> getWords();
	int numWords();
	int numFamilies();
	int familySize(string family);

	// Iterator
	void resetFamilyIter();
	string getNextFamily();
	
private:
    	// This stores all words currently "valid"
	vector<string>* wordlist;
	unordered_map<string, vector<string>*> dictionaries;

	// Used for Iterator.  The const_iterator is the same as an iterator
	// but used for situations where you want to prevent changes to the data.
	unordered_map<string, vector<string>*>::const_iterator famIter;
};

