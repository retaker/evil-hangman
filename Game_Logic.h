#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Graphics.h"

const int FOUR_LETTER_WORDS = 3862;
const int SEVEN_LETTER_WORDS = 21730;
const int EIGHT_LETTER_WORDS = 26448;

/*
 * description: This function reads in all words that are 4 7 and 8 characters long
 * return: void                                         
 * precondition: dict, word, and temp are valid                            
 * postcondition: temp has all the string that are 4 7 and 8 characters long
 */
void readIn(fstream &dict, string word, vector<string> &temp) {
	int i = 0;
	while (getline(dict, word)) {
		if (word.length() == 4 || word.length() == 7 || word.length() == 8) {
			temp[i] = word;
			i++;
		}
	}
}

/*
 * description: This function selects the difficulty based on the level input
 * return: void                                         
 * precondition: level, length, maxIncorrect and wordList are valid                           
 * postcondition: length, size of wordList and maxIncorrect are set
 */
void selectDiff(int &level, int &length, int &maxIncorrect, vector<string> &wordList) {
	switch (level) {
	case 4:
		length = 4;
		wordList.resize(FOUR_LETTER_WORDS);
		maxIncorrect = 12;
		break;
	case 5:
		length = 7;
		wordList.resize(SEVEN_LETTER_WORDS);
		maxIncorrect = 7;
		break;
	case 6:
		length = 8;
		wordList.resize(EIGHT_LETTER_WORDS);
		maxIncorrect = 6;
		break;
	default:
		cerr << "Invalid difficulty. Exiting Game..." << endl;
	}
}

/*
 * description: This function searches through temp for the words that are certain
 *              length and putting them into wordList
 * return: void                                          
 * precondition: temp, length, wordList and numWords are valid                           
 * postcondition: words with correct length are in wordList
 */
void loadCorrectLength(vector<string> temp, int length, vector<string> &wordList, int &numWords) {
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i].length() == length) {
			wordList[numWords] = temp[i];
			numWords++;
		}
	}
}

/*
 * description: This function gets the input from user then checking if is inside the attemptedLetters   
 * return: void                                         
 * precondition: repeatedLetter, letter, attemptedLetters and plotter are valid                           
 * postcondition: a correct letter is recorded in attemptedLetters
 */
void inputCheck(bool &repeatedLetter, char &letter, vector<char> &attemptedLetters, SDL_Plotter& plotter) {
	repeatedLetter = true;
	do {
		// prompt
		//cout << "Guess a letter: ";
		
		if (plotter.kbhit()) {
			letter = plotter.getKey();

			if (letter >= 'A' && letter <= 'Z') {
				letter = tolower(letter);
				cout << letter << endl;

				repeatedLetter = false;
				// check for repeated letter
				for (int i = 0; i < attemptedLetters.size() && repeatedLetter == false; i++) {
					if (letter == attemptedLetters[i])
						repeatedLetter = true;
				}

				// if not repeat letter, push letter onto attempted letter vector
				if (repeatedLetter == false) {
					attemptedLetters.push_back(letter);
					Point repeatMessage(200, 600, 255, 255, 255);
					putString("Please choose a letter you have not already chosen", repeatMessage, 3, plotter);
					plotter.update();
				}
				else {
					cout << "Repeated Letter!" << endl << endl;
					Point repeatMessage(200, 600, 255, 0, 0);
					putString("Please choose a letter you have not already chosen", repeatMessage, 3, plotter);
					plotter.update();
				}
					
			}
		}

	} while (repeatedLetter);
}

/*
 * description: This function checks the word in currentList and add word to subList if it does or does not conatin letter
 * return: void                                         
 * precondition: numWords, foundLetter, length, currentList, subList, letter, doesContain and remainingVals are valid                           
 * postcondition: subList has words that does or does not contain the letter
 */
void checkWord(int numWords, bool &foundLetter, int length, vector<string> currentList, char letter, int &remainingVals, vector<string> &subList, bool doesContain) {
	for (int i = 0; i < numWords; i++) {
		foundLetter = false;
		// cycle through each letter of the word
		for (int j = 0; j < length && foundLetter == false; j++) {
			if (currentList[i][j] == letter)
				foundLetter = true;
		}
		// update remainingVals and add word to currentList if it does or does not conatin letter
		if (foundLetter == doesContain) {
			remainingVals++;
			subList.push_back(currentList[i]);
		}
	}
}

/*
 * description: This function picks a random word from the subList
 * return: void                                 
 * precondition: randomNum, subList and finalWord are valid                       
 * postcondition: finalWord is chosen randomly from subList
 */
void pickRandom(int &randomNum, vector<string> subList, string &finalWord) {
	srand(time(NULL));
	randomNum = rand() % subList.size();
	finalWord = subList[randomNum];
}

/*
 * description: This function concatenate the last attempted char and a space
 *              onto the attemptedLetters
 * return: void                                 
 * precondition: attemptedLetters and attemptedStr are valid                           
 * postcondition: attemptedStr has a space and the last attempted letter
 */
void makeAttemptedStr(vector<char> attemptedLetters, string &attemptedStr) {
	attemptedStr += " ";
	attemptedStr += attemptedLetters[attemptedLetters.size() - 1];
}

#endif
