#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int main( int argc, char* args[]) {

    const int TOTAL_WORDS = 127142; 
    const int FOUR_LETTER_WORDS = 3862;
    const int SIX_LETTER_WORDS = 14383;
    const int EIGHT_LETTER_WORDS = 26447;
    int difficulty = 0, length = 0, numWords = 0, attempts = 0, incorrect = 0;
    int randomNum;
    char letter, *correctLetterArr;
    vector<string> wordList(1);
    vector<char> attemptedLetters(1);
    bool multipleWordsRemaining = true, repeatedLetter = false, gameWon = false;
    fstream dict;
    string word, finalWord = "";

    // prompt difficulty
    cout << "Select difficulty(1 2 3): ";
    cin >> difficulty;

    // assign length and resize wordList
    switch(difficulty) {
        case 1:
            length = 4;
            wordList.resize(FOUR_LETTER_WORDS);
            break;
        case 2:
            length = 6;
            wordList.resize(SIX_LETTER_WORDS);
            break;
        case 3:
            length = 8;
            wordList.resize(EIGHT_LETTER_WORDS);
            break;
        default:
            cerr << "Invalid difficulty. Exiting Game..." << endl;
            return -1;
    }

    // allocate array for correct letters / underscore
    correctLetterArr = new char[length];
    for( int i = 0; i < length; i++)
        correctLetterArr[i] = '_';

    // open dictionary file
    dict.open("Dictionary.txt", std::fstream::in);
    if (!dict.is_open()) {
        cerr << "Could not open dictionary file. Exiting Game..." << endl;
        return 1;
    }

    // read in words with length characters and place them in the list
    for(int i = 0; !dict.eof(); i++) {
        getline(dict, word);
        if(word.length() == length + 1) {
            wordList[numWords] = word;
            numWords++;
        }
    }
    
    // create sub-list vector to be used
    vector<string> currentList(wordList);
    vector<string> subList(1);

    bool foundLetter = false, noWords = false;
    int remainingVals = 0;
    
    // this loop controls the length of the game
    while(incorrect < 12 && multipleWordsRemaining == true) {
        // clear the subLIst and reset remaining value count
        subList.clear();
        remainingVals = 0;
        
        // input letter
        do {
            repeatedLetter = false;
            // prompt
            cout << "Guess a letter: ";
            cin >> letter;
            letter = tolower(letter);

            // check for repeated letter
            for(int i = 0; i < attemptedLetters.size() && repeatedLetter == false; i++) {
                if(letter == attemptedLetters[i])
                    repeatedLetter = true;
            }
            // if not repeat letter, push letter onto attempted letter vector
            if( repeatedLetter == false)
                attemptedLetters.push_back(letter);
            else
                cout << "Repeated Letter!" << endl << endl;

        } while(repeatedLetter == true);

        // check if word contains letter and create subset that doesn't contain letter
        for(int i = 0; i < numWords; i++) {
            foundLetter = false;
            // cycle through each letter of the word
            for(int j = 0; j < length && foundLetter == false; j++) {
                if(currentList[i][j] == letter)
                    foundLetter = true;
            }
            // update remainingVals and add word to currentList if it does not conatin letter
            if(foundLetter == false) {
                remainingVals++;
                subList.push_back(currentList[i]);
            }
        }

        cout << "--------------------------------------------------" << endl;
        // output words remaining
        if(remainingVals == 0)
            cout << "Words remaining = " << remainingVals + 1 << endl;
        else
            cout << "Words remaining = " << remainingVals << endl;

        // update numWords and the number of incorect if not zero
        numWords = remainingVals;
        cout << "*****NumWords: " << numWords << endl;
        if(numWords > 1) {
            cout << "1" << endl;
            // clear currentList and assign it to subList
            currentList.clear();
            currentList = subList;
            
            incorrect++;
            cout << "Sorry you guessed incorrectly!" << endl;
            cout << "You have " << 12 - incorrect << " tries left" << endl;
        } 
        // if there is only one word left
        else if(numWords == 1) {
            cout << "2" << endl;
            // clear currentList and assign it to subList
            currentList.clear();
            currentList = subList;
            
            incorrect++;
            cout << "Sorry you guessed incorrectly!" << endl;
            cout << "You have " << 12 - incorrect << " tries left" << endl;
            finalWord = currentList[0];
            multipleWordsRemaining = false;
        }
        // if no words remaining
        else {
            cout << "3" << endl;
            // check if word contains letter and create subset that does contain letter
            for(int i = 0; i < currentList.size(); i++) {
                foundLetter = false;
    
                // cycle through each letter of the word
                for(int j = 0; j < length && foundLetter == false; j++) {
                    if(currentList[i][j] == letter)
                        foundLetter = true;
                }

                // update remainingVals and add word to currentList if it does conatin letter
                if(foundLetter == true) {
                    remainingVals++;
                    subList.push_back(currentList[i]);
                }
            }
            
            cout << "You guessed a letter correctly!" << endl;
            cout << "You have " << 12 - incorrect << " tries left" << endl;
            
            // Picking a random word from new subset
            srand(time(NULL));
            randomNum = rand() % subList.size();
            finalWord = subList[randomNum];

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

    // If one word is remaining
    if(finalWord != "") {
        while(incorrect < 12 && gameWon == false) {
            foundLetter = false;
            
           // input letter
            do {
                repeatedLetter = false;
                // prompt
                cout << "Guess a letter: ";
                cin >> letter;
                letter = tolower(letter);

                // check for repeated letter
                for(int i = 0; i < attemptedLetters.size() && repeatedLetter == false; i++) {
                    if(letter == attemptedLetters[i])
                        repeatedLetter = true;
                }
                // if not repeat letter, push letter onto attempted letter vector
                if( repeatedLetter == false)
                    attemptedLetters.push_back(letter);
                else
                    cout << "Repeated Letter!" << endl << endl;

            } while(repeatedLetter == true);

            for(int i = 0; i < length; i++) {
                if(finalWord[i] == letter)
                    foundLetter = true;
            }
            
            cout << "--------------------------------------------------" << endl;
            cout << "Words remaining = " << numWords << endl;

            if(foundLetter == false) {
                incorrect++;
                cout << "Sorry you guessed incorrectly!" << endl;
                cout << "You have " << 12 - incorrect << " tries left" << endl;
                
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
                cout << "You have " << 12 - incorrect << " tries left" << endl;

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
                for(int i = 0; i < finalWord.length() - 1 && gameWon == true; i++) {
                    if(correctLetterArr[i] != finalWord[i])
                        gameWon = false;
                }
            }
        }
    }

    // 
    if(incorrect == 12 && gameWon == false) {
        cout << "YOU LOSE!!!" << endl << endl;
        cout << "The word was " << finalWord << endl << endl;
    }
    else {
        cout << "YOU WON!!!" << endl << endl;
    }

    return 0;
}