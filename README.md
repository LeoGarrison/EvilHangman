# Evil Hangman

## A note about grading

Unlike previous assignments, part of this assignment will be cloned and 
graded manually.  In particular, the functionality will be graded 
manually. Compiled versions of the program are provided to show what is 
expected for the game functionality. Assignments that do not compile will 
receive 0 points.

A Catch test for the FamilySet is provided to check ***some*** functionality.

## Deliverables

| Deliverable                  | Points  |
| ---------------------------- | -------:|
| EvilHangman                  |  25     |
| FamilySet                    |  35     |
| Commits                      |  5      |
| Commenting                   |  5      |
| **Total**                    | **70**  |

The same standards for committing and commenting apply for this assignment
as previous assignments. You should have pre/post comments in the header
files at minimum as well as general comments in `EvilHangman.cpp` .  You 
should be committing and pushing regularly.

## INTRODUCTION
In this assignment, you will build a mischievous program that bends the 
rules of Hangman to trounce its human opponent time and time again. In doing 
so, you'll cement your skills with abstract data types and iterators, and 
will hone your general programming savvy. Plus, you'll end up with a piece 
of software which will be highly entertaining.

In case you aren't familiar with the game Hangman, the rules are as follows:

1. One player chooses a secret word, then writes out a number of dashes 
   equal to the word length.

2. The other player begins guessing letters. Whenever she guesses a letter 
   contained in the hidden word, the first player reveals each instance of 
   that letter in the word. Otherwise, the guess is wrong.

3. The game ends either when all the letters in the word have been revealed 
   or when the guesser has run out of guesses.
   
## Evil Hangman Strategy

Fundamental to the game is the fact the first player accurately represents 
the word she has chosen. That way, when the other players guess letters, she 
can reveal whether that letter is in the word. But what happens if the 
player doesn't do this? This gives the player who chooses the hidden word an 
enormous advantage. For example, suppose that you're the player trying to 
guess the word, and at some point, you end up revealing letters until you 
arrive at this point with only one guess remaining:

D O – B L E

There are only two words in the English language that match this pattern: 
"doable" and "double". If the player who chose the hidden word is playing 
fairly, then you have a fifty-fifty chance of winning this game if you guess 
'A' or 'U' as the missing letter. However, if your opponent is cheating and 
hasn't actually committed to either word, then there is no possible way you 
can win this game. No matter what letter you guess, your opponent can claim 
that she had picked the other word, and you will lose the game. That is, if 
you guess that the word is "doable", the opponent can pretend that the 
committed word was "double" the whole time, and vice-versa.

## Example of Evil Hangman Strategy
Suppose that you are playing Hangman and it's your turn to choose a word, 
which we'll assume is of length four. Rather than committing to a secret 
word, you instead compile a list of every four-letter word in the English 
language. For simplicity, let's assume that English only has a few 
four-letter words, all of which are reprinted here:

ALLY&ensp;&ensp;BETA&ensp;&ensp;COOL&ensp;&ensp;DEAL&ensp;&ensp;ELSE&ensp;&ensp;FLEW&ensp;&ensp;GOOD&ensp;&ensp;HOPE&ensp;&ensp;IBEX

Now, suppose that your opponent guesses the letter 'E.' You now need to tell 
your opponent which letters in the word you've “picked” are E's.  You 
haven't picked a word so you have multiple options about where you reveal 
the E's. Here's the above word list, with E's highlighted in each word:

ALLY&ensp;&ensp;B**E**TA&ensp;&ensp;COOL&ensp;&ensp;D**E**AL&ensp;&ensp;
**E**LS**E**&ensp;&ensp;FL**E**W&ensp;&ensp;GOOD&ensp;&ensp;HOP**E**&ensp;&ensp;
IB**E**X

If you'll notice, every word in your word list falls into one of five "word 
families":
*	`----`	contains the word ALLY, COOL, and GOOD
*	`-E--`	contains BETA and DEAL
*	`--E-`	contains FLEW and IBEX
*	`E--E`	contains ELSE
*	`---E`	contains HOPE

You can choose to reveal any one of the above five families. There are many 
ways to pick which family to reveal – perhaps you want to steer your 
opponent toward a smaller family with more obscure words, or toward a larger 
family in the hopes of keeping your options open. In this assignment, in the 
interests of simplicity, we'll adopt the latter approach and always choose 
the largest of the remaining word families. In this case, it means that you 
should pick the family `----`. This reduces your word list down to

ALLY&ensp;&ensp;COOL&ensp;&ensp;GOOD

and since you didn't reveal any letters, you would tell your opponent that 
his guess was wrong.  Now the list of words you have to choose from has been 
reduced to these three words.  If your opponent guesses the letter O, then 
you would break your word list down into two families:

*	`-OO-`	contains `COOL` and `GOOD`
*	`----`	contains `ALLY`

Since the `-OO-` family is larger (two words) we go ahead and choose it, 
revealing two O's in the word and reducing the list down to

COOL&ensp;&ensp;GOOD

But what happens if your opponent guesses a letter that doesn't appear 
anywhere in your word list? For example, what happens if your opponent now 
guesses 'T'? This isn't a problem. If you try splitting these words apart 
into word families, you'll find that there's only one family;  the family 
`----` in which T appears nowhere and which contains both `COOL` and `GOOD`. Since 
there is only one word family here, it's already the largest family, and by 
picking it you would maintain the word list you already had.

There are two possible outcomes of this game. 

1.	Your opponent might be smart enough to pare the word list down to one 
    word and then guess what that word is. In this case, you should 
    congratulate the player. 

2.	By far the most common case, your opponent will be completely stumped 
    and will run out of guesses. When this happens, you can pick any word 
    you'd like from your list and say it's the word that you had chosen 
    all along.

The beauty of this setup is that your opponent will have no way of knowing 
that you were dodging guesses the whole time – it looks like you simply 
picked an unusual word and stuck with it the whole way.

## unordered_map

There are many different ways to go about organizing the data. The most 
convenient and the one that first comes to mind is some sort of lookup table.
While we are playing the game, we need to be able to associate each word 
with a particular family. To accomplish this, we will use a table that 
uses the word family as a key and some sort of list or dictionary to store 
the words associated with that key.

The `unorderded_map` is a lookup table that is part of the Standard Template 
Library (STL). It has a key and a value associated with the key.

### Example usage of an `unordered_map`

In the following example, an `unordered_map` is used to store towns in for a 
given state.  The key in this case is the state name (a string), and the 
value associated with the key is a pointer to a vector of strings. The usage 
below covers all the functionality required for your program.

```c++
// key is a string, value is a pointer to a vector of strings.
unordered_map<string, vector<string>*> townTable;   

// count allows you to tell if this key exists in the table.
// Here we check if CA exists.  If it doesn't, then we need to insert this key 
// into the table and associate it with a vector pointer.
if (townTable.count("CA") == 0) {
    // Creates a new vector
    vector<string>* townVector = new vector<string>;
    
    // Insert the new vector and associate it with the key "CA".
    // This is done using a pair object, which is simply an object that can 
    // hold two values. (More on this later...)
    dictionaries.insert(pair<string, vector<string>*>("CA", townVector));
}

// We can now push towns onto the vector associated with the state
townTable["CA"]->push_back("Hayward");
townTable["CA"]->push_back("Palo Alto");
townTable["CA"]->push_back("San Francisco");
townTable["CA"]->push_back("Dublin");
townTable["CA"]->push_back("Livermore");


// Inserting a few more states.  Inserting null instead of a vector pointer.
dictionaries.insert(pair<string, vector<string>*>("NY", nullptr));
dictionaries.insert(pair<string, vector<string>*>("FL", nullptr));
dictionaries.insert(pair<string, vector<string>*>("NV", nullptr));

// To get the vector associated with the key "CA", you can use the following
vector<string>* townsInCA = townTable["CA"];

// To iterate over all the keys of townTable, you will need an iterator for 
// the unordered_map.
unordered_map<string, vector<string>*>::iterator it = townTable.begin();

/*
 * The iterator actually points to a pair object.  The pair object is very 
 * simply and just holds two values.  
 * 
 * it->first    This is the key
 * it->second   This is the value associated with the key
 * 
 * The following loop will output all the keys of townTable.
 */
while(it != townTable.end()) {
    string stateName = it->first;
    cout << stateName << endl;
    it++;
}


// loop through each key and the towns associated with the key
it = townTable.begin();
while(it != townTable.end()) {
    string stateName = it->first;               // key
    vector<string>* townVector = it->second;    // value associated with the key
    
    cout << "State: " << stateName << endl;
    
    // Only print out the towns if the vector is not nullptr
    if (townVector != nullptr) {
        for (int i = 0; i < townVector->size(); i++) {
            cout << townVector->at(i) << ", ";
        }
        cout << endl;
    }
    cout << endl;
    it++;
}
```

## `FamilySet(string dictFile, int len)`

This constructor opens a file with the name `dictFile` and pushes all words 
of the length `len` into the vector `wordlist`.

> **Hint:** Note that `wordlist` is a `vector<string>*`.  You will need to 
> allocate memory before you can push words onto the wordlist.

## `void setFamily(string family)`

This function sets `wordlist` to the dictionary of the given family.
This function should also clear the dictionaries.

> **Note:** The setFamily function only should work if `family` exists in 
> `dictionaries`.  If `family` is not in `dictionary`, then `setFamily` 
> should do nothing.

## `filterFamilies(string letter, string guessPattern)`

This function does the heavy lifting for the "evil" strategy.  For each word in 
`wordlist`, you need to classify what family is part of based on the letter 
and guess pattern. 

**If you can find letter in the word, then it will be part 
of a family.**  If you can't, then the family will just be the guess pattern. 

### Filtering a single word

Suppose

`letter` is "a"

`guessPattern` is ***y

`word` is "ally"  (this would be a word from `wordlist`)
 
In this case, the family is a**y. Once this is determined, then "ally" can 
be added to this family dictionary.
 
If the letter does not exist in the word, then the family is 
simply the `guessPattern`.

Here is the rough algorithm for this filtering process:

```c++
for (each word in wordlist) {
    if (word is part of a family) {
        Construct the family (ie figure out that ally belongs to a**y)
    }
    else {
        The family is the guess pattern
    }
    
    Push the word into dictionaries under the appropriate family
}
```

> **HINTS:**
> 
> #### Constructing a word family from a word, letter, and guess pattern
> To construct the family from the word, letter, and guess pattern, you may 
> find it helpful to go through each letter of the word and decide whether 
> the letter should remain the same, or change it to *.  For example, if 
> the word is "ally", the letter is "a", and `guessPattern` is ***y, 
> then we would look at each letter of the word and decide if it should remain 
> the same or change to *:
> 
> * ***a***lly&ensp;&ensp;("a" is the guessed letter. Do not change.)  
> * a***l***ly&ensp;&ensp;("l" is not the guessed letter or a letter in the guessPattern. Change "l" to "*".)
> * a\****l***y&ensp;&ensp;("l" is not the guessed letter or a letter in the guessPattern. Change "l" to "*".)
> * a\*\****y***&ensp;&ensp;("y" is part of the guessPattern. Do not change.)
> 
> #### Pushing a word into `dictionaries`
> 
> You will need to check if the family exists in `dictionaries` before 
> pushing the word into the `dictionaries`.  If the family is NOT in 
> `dictionaries`, then create a new vector of strings and insert it into 
> `dictionaries` ***first*** before pushing the word into the appropriate 
> word family in `dictionaries`.

## `string getRandomWord()`

This function returns a random word from `wordlist`.

## `int numWords()`

This function returns the number of words in `wordlist`.

## `int numFamilies()`

This function returns the number of families in `dictionaries`.

## `int familySize(string family)`

This returns the number of words for a given `family` in `dictionaries`.  If 
the family does not exist, then it should return -1.

## FamilySet Iterator 

The `FamilySet` iterator iterates of the ***families*** of `dictionaries`.   
In other words, it iterates over the keys of `dictionaries`. It does not 
return individual words.  This iterator is only called after the 
`filterFamilies` function has been run on the current `wordlist`.

## `void resetFamilyIter()`

This should set `famIter` to start at the beginning.

## `string getNextFamily()`

This function returns the value of the iterator and moves the iterator to 
the next value. If there are no more families left in the iterator (the 
iterator is not at the end), then this function should return the empty string.

## Other Random Hints

### Figuring out if a letter is in a word

The find method of a string returns the first position a letter occurs. If 
the letter does not occur then it will return string::npos (this is actually 
a special integer).

```c++
if (word.find("*") == string::npos) {
    
}
```

### Get a random number between 0 and some other number

```c++
int randInd = rand()%100; // Returns an integer between 0 and 99.
```

### Gaps in the dictionary file
Watch out for gaps in the dictionary. When the user specifies a word length, 
you will need to check that there are indeed words of that length in the 
dictionary. You might initially assume that if the requested word length is 
less than the length of the longest word in the dictionary, there must be 
some word of that length. Unfortunately, the dictionary contains a few gaps. 
The longest word in the dictionary has length 29, but there are no words of 
length 27 or 26. Be sure to take this into account when checking if a word 
length is valid.