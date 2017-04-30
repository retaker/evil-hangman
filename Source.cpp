#include <iostream>
#include <cstring>
#include <string>
#include <ctype.h>
#include "SDL_Plotter.h"
#include "Graphics.h"
#include "Game_Logic.h"

using namespace std;

const int TOTAL_WORDS = 127142;
const int NEEDED_LETTER_WORDS = 52040;

int main(int argc, char **argv) 
{
	// algorithm variables
	vector<string> temp(1);
	vector<string> wordList(1);
	vector<char> attemptedLetters;
	string attemptedStr = "Incorrect Letters: ";
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
	vector<string> subList(1);

	// SDL variables
	SDL_Plotter background = SDL_Plotter(720, 1280, true);
	loadFont("font.txt");
	DefaultScreen(background);
	background.update();

	// loading 4, 7 and 8 letter words into vector temp
	temp.resize(NEEDED_LETTER_WORDS);
	// open dictionary file
	dict.open("Dictionary.txt", std::fstream::in);
	readIn(dict, word, temp);

	int level= 4;
	bool MusicOn = true;
	int mousePointer = 1;
	bool inMainMenu = false;
	bool GameStarted = false;
	bool InSubMenu = false;

	Point p1 = Point(200, 700);
	Point p2 = Point(557, 495);
	Point p3 = Point(300, 275, 0, 0, 0);

	while (!background.getQuit()) {
		if (background.kbhit()) {

			if (background.getKey() != '\0')
			{
				
				if (inMainMenu == false) {
					background.clear();
					mousePointer = 1;
					MainMenu(background, level, MusicOn, mousePointer);
					background.update();
					inMainMenu = true;
				}
				
				//mousepointer part
				else if (background.getKey() == DOWN_ARROW)
				{
					if (mousePointer > 0 && mousePointer < 5) {
						mousePointer++;
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update(); 
					}
					else 
					{
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
				}
				else if (background.getKey() == UP_ARROW) 
				{
					if (mousePointer > 1 && mousePointer < 6) {
						mousePointer--;
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
					else 
					{
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
					}
				}
				//level control part
				else if (background.getKey()==LEFT_ARROW)
				{
					if (mousePointer == 2) 
					{
						if (level >=5) 
						{
							level--;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
						else 
						{
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
					//sound control
					else if (mousePointer == 3) 
					{
						if (MusicOn == true) {
							MusicOn = false;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}

						else if (MusicOn == false) {
							MusicOn = true;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
				}
				else if (background.getKey() == RIGHT_ARROW)
				{
					if (mousePointer == 2)
					{
						if (level < 6) 
						{
							level++;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
					//sound control
					else if (mousePointer == 3) 
					{
						if (MusicOn == true) {
							MusicOn = false;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
						else if (MusicOn == false) {
							MusicOn = true;
							background.clear();
							MainMenu(background, level, MusicOn, mousePointer);
							background.update();
						}
					}
				}
				//if user typing enter at default window.
				else if (background.getKey() == SDL_SCANCODE_RETURN&&inMainMenu == false)
				{
					inMainMenu = true;
				}
				else if (background.getKey() == SDL_SCANCODE_RETURN&&inMainMenu == true)
				{
					if (mousePointer == 1)
					{
						background.clear();
						GamingScreen(background, level);
						background.update();
						GameStarted = true;

						selectDiff(level, length, maxIncorrect, wordList);
						loadCorrectLength(temp, length, wordList, numWords);

						vector<string> currentList(wordList);


						// allocate array for correct letters / underscore
						correctLetterArr = new char[length];
						for (int i = 0; i < length; i++)
							correctLetterArr[i] = '_';

						while (incorrect < maxIncorrect && multipleWordsRemaining == true) {
							subList.clear();
							remainingVals = 0;


							inputCheck(repeatedLetter, letter, attemptedLetters, background);
							makeAttemptedStr(attemptedLetters, attemptedStr);
							putString(attemptedStr, p1, 2, background);
							putString("A", p2, 7, background);
							background.update();
							checkWord(numWords, foundLetter, length, currentList, letter, remainingVals, subList, doesContain);

							cout << "--------------------------------------------------" << endl;

							// output words remaining
							if (remainingVals == 0)
								cout << "Words remaining = " << remainingVals + 1 << endl;
							else
								cout << "Words remaining = " << remainingVals << endl;

							// update numWords and the number of incorect if not zero
							numWords = remainingVals;

							if (numWords > 1) {
								// clear currentList and assign it to subList
								currentList.clear();
								currentList = subList;

								incorrect++;
								drawHead(p3, 50, background);
								cout << "Sorry you guessed incorrectly!" << endl;
								cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;
							}
							// if there is only one word left
							else if (numWords == 1) {
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
								for (int i = 0; i < length; i++) {
									if (finalWord[i] == letter)
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
							if (numWords >= 1 && noWords == false) {
								for (int i = 0; i < length; i++)
									cout << correctLetterArr[i] << " ";
							}
							cout << endl << endl << "Attempted Letters: ";
							for (int i = 0; i < attemptedLetters.size(); i++)
								cout << attemptedLetters[i] << " ";
							cout << endl << "-----------------------------------------------------" << endl << endl;
						}
					
						// Picking a random word from new subset
						if (numWords > 1) {
							pickRandom(randomNum, subList, finalWord);
						}

						// If one word is remaining
						else if (finalWord != "" && numWords == 1) {
							while (incorrect < maxIncorrect && gameWon == false) {
								foundLetter = false;

								// input letter
								inputCheck(repeatedLetter, letter, attemptedLetters, background);

								for (int i = 0; i < length; i++) {
									if (finalWord[i] == letter)
										foundLetter = true;
								}

								cout << "--------------------------------------------------" << endl;
								cout << "Words remaining = " << numWords << endl;

								// Guessed the letter incorrectly
								if (foundLetter == false) {
									incorrect++;
									cout << "Sorry you guessed incorrectly!" << endl;
									cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;

									// print correct letterss
									cout << endl;
									for (int i = 0; i < length; i++)
										cout << correctLetterArr[i] << " ";

									// print attempted letters
									cout << endl << endl << "Attempted Letters: ";
									for (int i = 0; i < attemptedLetters.size(); i++)
										cout << attemptedLetters[i] << " ";
									cout << endl << "-----------------------------------------------------" << endl << endl;
								}

								// Guessed the letter correctly
								else {
									cout << "You guessed a letter correctly!" << endl;
									cout << "You have " << maxIncorrect - incorrect << " tries left" << endl;

									// update correct letter array with correct letters
									for (int i = 0; i < length; i++) {
										if (finalWord[i] == letter)
											correctLetterArr[i] = finalWord[i];
										cout << correctLetterArr[i] << " ";
									}
									// print attempted letters
									cout << endl << endl << "Attempted Letters: ";
									for (int i = 0; i < attemptedLetters.size(); i++)
										cout << attemptedLetters[i] << " ";
									cout << endl << "-----------------------------------------------------" << endl << endl;

									gameWon = true;
									for (int i = 0; i < finalWord.length() && gameWon == true; i++) {
										if (correctLetterArr[i] != finalWord[i])
											gameWon = false;
									}
								}
							}
						}

						if (incorrect == maxIncorrect && gameWon == false) {
							cout << "YOU LOSE!!!" << endl << endl;
							cout << "The word was " << finalWord << endl << endl;
						}
						else {
							cout << "YOU WON!!!" << endl << endl;
						}
					}
					else if (mousePointer == 4) 
					{
						background.clear();
						ScoreBoard(background);
						background.update();
						InSubMenu = true;
					}
					else if (mousePointer == 5) 
					{
						background.getQuit();
					}
					else {
					}
				}
				//back to mainMenu from gaming window
				else if (background.getKey() == '1') 
				{
					if (GameStarted == true||InSubMenu==true) 
					{
						background.clear();
						MainMenu(background, level, MusicOn, mousePointer);
						background.update();
						GameStarted == false;
						InSubMenu == false;
					}
					else {}
				}
			}
		}
	}
	return 0;
}
