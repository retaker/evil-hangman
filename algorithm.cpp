#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <ctime>
#include <cstdlib>
#include "Graphics.h"
#include "SDL_Plotter.h"

using namespace std;

const int TOTAL_WORDS = 127142;
const int FOUR_LETTER_WORDS = 3862;
//const int SIX_LETTER_WORDS = 14383;
const int SEVEN_LETTER_WORDS = 21730;
const int EIGHT_LETTER_WORDS = 26448;

void selectDiff(int &, int &, int &, vector<string> &);
void readIn(fstream &, string, vector<string> &);
void readIn2(fstream &, string, int, vector<string> &, int &);
void inputCheck(bool &, char &, vector<char> &);
void checkWord(int, bool &, int, vector<string>, char, int &, vector<string> &, bool);
void pickRandom(int &, vector<string>, string &);

int main( int argc, char** args) {
	// algorithm variables
	vector<string> wordList(1);
	vector<string> temp(1);
	vector<char> attemptedLetters(1);
	int difficulty = 0;
	int	length = 0;
	int	numWords = 0;
	int attempts = 0;
	int incorrect = 0;
	int remainingVals = 0;
	int randomNum; 
	int maxIncorrect;
	char letter; 
	char *correctLetterArr;
	bool multipleWordsRemaining = true; 
	bool repeatedLetter = false; 
	bool gameWon = false;
	bool foundLetter = false;
	bool noWords = false; 
	bool doesContain = false;
    fstream dict;
    string word, finalWord = "";

	temp.resize(52040);
	// open dictionary file
	dict.open("Dictionary.txt", std::fstream::in);
	readIn(dict, word, temp);

    // prompt difficulty
    cout << "Select difficulty(1 2 3): ";
    cin >> difficulty;

	// select the difficulty
	selectDiff(difficulty, length, maxIncorrect, wordList);

    // allocate array for correct letters / underscore
    correctLetterArr = new char[length];
    for( int i = 0; i < length; i++)
        correctLetterArr[i] = '_';

	// read in words with length characters and place them in the list
	//readIn2(dict, word, length, wordList, numWords);
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i].length() == length) {
			wordList[numWords] = temp[i];
			numWords++;
		}
	}

    // create sub-list vector to be used
    vector<string> currentList(wordList);
    vector<string> subList(1);
    
    // this loop controls the length of the game
    while(incorrect < maxIncorrect && multipleWordsRemaining == true) {
        // clear the subLIst and reset remaining value count
        subList.clear();
        remainingVals = 0;
        
        // input letter
		inputCheck(repeatedLetter, letter, attemptedLetters);

        // check if word contains letter and create subset that doesn't contain letter
		checkWord(numWords, foundLetter, length, currentList, letter, remainingVals, subList, doesContain);

        cout << "--------------------------------------------------" << endl;
        // output words remaining
        if(remainingVals == 0)
            cout << "Words remaining = " << remainingVals + 1 << endl;
        else
            cout << "Words remaining = " << remainingVals << endl;

        // update numWords and the number of incorect if not zero
        numWords = remainingVals;
        if(numWords > 1) {
            // clear currentList and assign it to subList
            currentList.clear();
            currentList = subList;
            
            incorrect++;
            cout << "Sorry you guessed incorrectly!" << endl;
            cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;
        } 
        // if there is only one word left
        else if(numWords == 1) {
            // clear currentList and assign it to subList
            currentList.clear();
            currentList = subList;
            
            incorrect++;
            cout << "Sorry you guessed incorrectly!" << endl;
            cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;
            finalWord = currentList[0];
            multipleWordsRemaining = false;
        }
        // if no words remaining
        else {
            // check if word contains letter and create subset that does contain letter
			checkWord(currentList.size(), foundLetter, length, currentList, letter, remainingVals, subList, doesContain = true);

			cout << "You guessed a letter correctly!" << endl;
            cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;
            
            // Picking a random word from new subset
			pickRandom(randomNum, subList, finalWord);

            // update correct letter array with correct letters
            for(int i = 0; i < length; i++) {
                if(finalWord[i] == letter)
                    correctLetterArr[i] = finalWord[i];
                cout << correctLetterArr[i] << " ";
            }

            // set multipleWordsRemaining to false to exit loop
            multipleWordsRemaining = false;
            noWords = true; 
            numWords = 1;
        }

        //display correct letters / underscores
        cout << endl;
        if(numWords >= 1 && noWords == false) {
            for(int i = 0; i < length; i++) 
                cout << correctLetterArr[i] << " ";
        }
        cout << endl << endl << "Attempted Letters: ";
        for(int i = 0; i < attemptedLetters.size(); i++)
            cout << attemptedLetters[i] << " ";
        cout << endl << "-----------------------------------------------------" << endl << endl;
    }

	// Picking a random word from new subset
	if (numWords > 1) {
		pickRandom(randomNum, subList, finalWord);
	}

    // If one word is remaining
    else if(finalWord != "" && numWords == 1) {
        while(incorrect < maxIncorrect && gameWon == false) {
            foundLetter = false;
            
			// input letter
			inputCheck(repeatedLetter, letter, attemptedLetters);

            for(int i = 0; i < length; i++) {
                if(finalWord[i] == letter)
                    foundLetter = true;
            }
            
            cout << "--------------------------------------------------" << endl;
            cout << "Words remaining = " << numWords << endl;

            if(foundLetter == false) {
                incorrect++;
                cout << "Sorry you guessed incorrectly!" << endl;
                cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;
                
                // print correct letterss
                cout << endl;
                for(int i = 0; i < length; i++) 
                    cout << correctLetterArr[i] << " ";

                // print attempted letters
                cout << endl << endl << "Attempted Letters: ";
                for(int i = 0; i < attemptedLetters.size(); i++)
                    cout << attemptedLetters[i] << " ";
                cout << endl << "-----------------------------------------------------" << endl << endl;
            }
            else {
                cout << "You guessed a letter correctly!" << endl;
                cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;

                // update correct letter array with correct letters
                for(int i = 0; i < length; i++) {
                    if(finalWord[i] == letter)
                        correctLetterArr[i] = finalWord[i];
                    cout << correctLetterArr[i] << " ";
                }
                 // print attempted letters
                cout << endl << endl << "Attempted Letters: ";
                for(int i = 0; i < attemptedLetters.size(); i++)
                    cout << attemptedLetters[i] << " ";
                cout <<  endl << "-----------------------------------------------------" << endl << endl;
                
                gameWon = true;
                for(int i = 0; i < finalWord.length() && gameWon == true; i++) {
                    if(correctLetterArr[i] != finalWord[i])
                        gameWon = false;
                }
            }
        }
    }

    if(incorrect == maxIncorrect && gameWon == false) {
        cout << "YOU LOSE!!!" << endl << endl;
        cout << "The word was " << finalWord << endl << endl;
    }
    else {
        cout << "YOU WON!!!" << endl << endl;
    }

    return 0;
}

void selectDiff(int &level, int &length, int &maxIncorrect, vector<string> &wordList) {
	switch (level) {
	case 1:
		length = 4;
		wordList.resize(FOUR_LETTER_WORDS);
		maxIncorrect = 12;
		break;
	case 2:
		length = 7;
		wordList.resize(SEVEN_LETTER_WORDS);
		maxIncorrect = 7;
		break;
	case 3:
		length = 8;
		wordList.resize(EIGHT_LETTER_WORDS);
		maxIncorrect = 6;
		break;
	default:
		cerr << "Invalid difficulty. Exiting Game..." << endl;
	}
}

void readIn(fstream &dict, string word, vector<string> &temp) {
	int i = 0;
	while (getline(dict, word)) {
		if (word.length() == 4 || word.length() == 7 || word.length() == 8) {
			temp[i] = word;
			i++;
		}
	}
}

void inputCheck(bool &repeatedLetter, char &letter, vector<char> &attemptedLetters) {
	
	do {
		repeatedLetter = false;
		// prompt
		cout << "Guess a letter: ";
		cin >> letter;
		letter = tolower(letter);

		// check for repeated letter
		for (int i = 0; i < attemptedLetters.size() && repeatedLetter == false; i++) {
			if (letter == attemptedLetters[i])
				repeatedLetter = true;
		}
		// if not repeat letter, push letter onto attempted letter vector
		if (repeatedLetter == false)
			attemptedLetters.push_back(letter);
		else
			cout << "Repeated Letter!" << endl << endl;

	} while (repeatedLetter);
}

void checkWord(int numWords, bool &foundLetter, int length, vector<string> currentList, char letter, int &remainingVals, vector<string> &subList, bool doesContain) {
	for (int i = 0; i < numWords; i++) {
		foundLetter = false;
		// cycle through each letter of the word
		for (int j = 0; j < length && foundLetter == false; j++) {
			if (currentList[i][j] == letter)
				foundLetter = true;
		}
		// update remainingVals and add word to currentList if it does not conatin letter
		if (foundLetter == doesContain) {
			remainingVals++;
			subList.push_back(currentList[i]);
		}
	}
}

void pickRandom(int &randomNum, vector<string> subList, string &finalWord) {
	srand(time(NULL));
	randomNum = rand() % subList.size();
	finalWord = subList[randomNum];
}