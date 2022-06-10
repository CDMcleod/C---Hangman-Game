/*
Programmer: Connor Drayden McLeod
Program: Hangman game
Creation date: April 18th, 2018
Last Modified: 4/28/2021
Design Comments: Readme.txt
*/
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<array>
#include<cctype>

using namespace std;

//function to instantiate elements into
//the struct phrase
struct Phrase{
    string text;
    string::size_type guessesRequired;
    bool isUsed;
};

//function declarations
int uniqueLetterCount(const string word);
void loadPhrasesFromFile(string fileName, Phrase phraseArray[],
    int phraseNum);
void sortPhrases(Phrase phraseArray[], int phraseNum);
void printPhrases(Phrase phraseArray[], int phraseNum);
string phraseWithBlanks(const string &phrase, const string &guessed);
string toLowerCase(const string& text);
bool isLetter(unsigned char text);
int getDifficultyLevel();
void runGame(Phrase &selectedPhrase);
void drawGallows(int missCount);

//main function
int main(){

    int phraseNum = 60;
    typedef Phrase phraseArray[phraseNum]; // array of structs
    phraseArray Phrase; // variable of the array type phraseArray
    int firstThird = phraseNum / 3;
    int secondThird = firstThird + firstThird;
    int lastThird = phraseNum - firstThird;
    srand(static_cast<unsigned int>(time(nullptr)));
	int randPhraseIndex;
    int difficulty;
    int phrasesExpended;
    char cont = 'y';

    loadPhrasesFromFile("phrases.txt", Phrase, phraseNum);
    sortPhrases(Phrase, phraseNum);

    //do..while to run game until user selects 'n'
    do{
        phrasesExpended = 0;
        difficulty = getDifficultyLevel();
        
        //if else statments use rand() and selected difficulty
        //to retrieve phrase from phrases.txt

        if(difficulty == 1){
	
		    randPhraseIndex = (rand() % firstThird);
	    }
        else if(difficulty == 2){
            randPhraseIndex = (rand() % firstThird + firstThird);
        }
        else if(difficulty == 3){
            randPhraseIndex = (rand() % firstThird + secondThird);
        }

        while(Phrase[randPhraseIndex].isUsed){

            difficulty = getDifficultyLevel();
            if(difficulty == 1){
	
		        randPhraseIndex = (rand() % firstThird);
	        }
            else if(difficulty == 2){
                randPhraseIndex = (rand() % firstThird + firstThird);
            }
            else if(difficulty == 3){
                randPhraseIndex = (rand() % firstThird + secondThird);
            }
        }
        
        runGame(Phrase[randPhraseIndex]);
        Phrase[randPhraseIndex].isUsed = true;
        cout << "\nwould you like to continue? (y/n):";
        cin >> cont;
    
    }while(phrasesExpended < firstThird && cont == 'y');
    return 0;
}

//function to count unique number of letters in a phrase
//to be guessed
int uniqueLetterCount(const string word){
    int uniqueCount = 0;
    string uniqueLetters = "";
    char letter;
    for (int index = 0; index < word.size(); index++){
        letter = tolower(word[index]);

        if(letter >= 'a' || letter <= 'z' && letter != ' ' && letter != '.' &&
            letter != ',' && letter != '?')
            if(uniqueLetters.find(letter) == string::npos){
            uniqueLetters = uniqueLetters + letter;
            uniqueCount++;
            }
    }
    return uniqueCount;
}

//loads a list of phraes from input stream and places them
//into an array of phrases.
void loadPhrasesFromFile(string fileName, Phrase phraseArray[],
    int phraseNum){

    ifstream inputFile;
    inputFile.open(fileName);
    for(int index = 0; index < phraseNum && !inputFile.eof(); index ++){

        getline(inputFile, phraseArray[index].text);
        phraseArray[index].guessesRequired =
        uniqueLetterCount(phraseArray[index].text);
        phraseArray[index].isUsed = false;
    }

}

//sorts the phrases based upon difficulty level(guesses required)
void sortPhrases(Phrase phraseArray[], int phraseNum){

    int index;
    int lower;
    int current;
    Phrase tempVar;
    
    for(index = 0; index < phraseNum - 1; index++){

        lower = index;
        for(current = index + 1; current < phraseNum; current++){
            if(phraseArray[current].guessesRequired <
                phraseArray[lower].guessesRequired)
                lower = current;
        }

        tempVar = phraseArray[lower];
        phraseArray[lower] = phraseArray[index];
        phraseArray[index] = tempVar;

    }
}

//outputs the elements of every phrase in the Array of 
//phrase structures
void printPhrases(Phrase phraseArray[], int phraseNum){

    string status;
    const char SPACER = ' ';
    cout << left << setw(10) << "Guesses "
        << setw(50) << "Phrase ";
    cout << left << "Status " << endl;

    for(int index = 0; index < phraseNum; index++){

    cout << phraseArray[index].guessesRequired << "";
    cout << phraseArray[index].text << " ";

        if(phraseArray[index].isUsed){
            cout << " Used";
        }
        else{
            cout << " Unused";
        }

        cout << endl;
     
    }
}

//funtion to output to user a string, seperated by spaces,
// where all unguessed letters are replaced with blanks
string phraseWithBlanks(const string &phrase, const string &guessed){

    string phraseBlanks;
    string correctlyGuessedLower;
    char currentCharLower;

      correctlyGuessedLower = toLowerCase(guessed);

    for (char currChar : phrase)
    {
        if (phraseBlanks.length() > 0)
            phraseBlanks+= ' ';

        currentCharLower = tolower(currChar);
        if (currentCharLower < 'a' || currentCharLower > 'z' ||
            correctlyGuessedLower.find(currentCharLower) != string::npos)
            phraseBlanks += currChar;
            
        else
        phraseBlanks += '_';
        
    }
    return phraseBlanks;
}

//converts an entire string to lower case text
//for simplicity
string toLowerCase(const string& text){

    string lowerCaseStr;
    for (char ch : text)
        lowerCaseStr += tolower(ch);

    return lowerCaseStr;
}

//checks ASCII value of input to determine if user 
//response is indeed a letter.
bool isLetter(unsigned char text){

    bool status = false;

    if(text > 96 && text < 123){
        status = true;
    }
    else if(text < 96 && text > 123){
    }

    return status;
}

//prompts user with difficulty options then
//accepts difficulty level as user input
int getDifficultyLevel(){

    int selection;
    cout << left << "Difficulty options: " << endl;
    cout << "(1) Easy" << endl;
    cout << "(2) Medium" << endl;
    cout << "(3) Hard" << endl;

    cout << "Enter the number to select difficults (Ex: 3):";
    cin >> selection;

    while(selection < 1 || selection > 3){
        
        cout << "\nPlease enter 1, 2, or 3 to select your difficulty:";
        cin >> selection;
    }
    return selection;
}

//funtion to draw gallows, and run the simultation of
//the hangman game
void runGame(Phrase &selectedPhrase){
    
    int incorrectGuesses = 0;
    string::size_type correctGuesses = 0;
    string rightGuess = "";
    string wrongGuess = "";
    string currPhrase = selectedPhrase.text;
    currPhrase = toLowerCase(currPhrase);
    char guess;
    do{
        drawGallows(incorrectGuesses);
        cout << phraseWithBlanks(currPhrase, rightGuess) << endl;

            cout << "Please guess a letter in the phrase: ";
            cin >> guess;
            guess = tolower(guess);
            if(guess > 'z' || guess < 'a'){
                cout << guess << " is not a valid guess!" << endl;
                
            }
            else if(rightGuess.find(guess) != string::npos
                || wrongGuess.find(guess) != string::npos){
                    cout << "You have already guessed " << guess << endl;
            }
            else{

                if(currPhrase.find(guess) != string::npos){
                    cout << "Good guess" << endl;
                    correctGuesses++;
                    rightGuess += guess;
                }
                else{
                    cout << "Sorry, bad guess." << endl;
                    incorrectGuesses++;
                    wrongGuess += guess;
                }
            }
        
    } while(incorrectGuesses < 5 && correctGuesses 
        < selectedPhrase.guessesRequired - 1);

    if(incorrectGuesses >= 5){
        cout << "You are dead!";
        cout << " Correct phrase: " << selectedPhrase.text << endl;

    }
    else{
        cout << "Cheers, you survived." << endl;
    }
        drawGallows(incorrectGuesses);
}

//draws an image of the hangman "gallows", based
//upon how many incorrect guesses have been made so far
void drawGallows(int missCount){

	// Output the top of the gallows
	cout
		<< "   +----+     \n"
		<< "   |    |     \n";

	// Output the stand and body
	switch (missCount)
	{
	case 0:
		cout
			<< "   |       \n"
			<< "   |       \n"
			<< "   |       \n"
			<< "   |       \n";
		break;

	case 1:
		cout
			<< "   |    O  \n"
			<< "   |    |  \n"
			<< "   |       \n"
			<< "   |       \n";
		break;

	case 2:
		cout
			<< "   |    O  \n"
			<< "   |   /|  \n"
			<< "   |       \n"
			<< "   |       \n";
		break;

	case 3:

		cout
			<< "   |    O   \n"
			<< "   |   /|\\ \n"
			<< "   |        \n"
			<< "   |        \n";
		break;

	case 4:
		cout
			<< "   |    O   \n"
			<< "   |   /|\\ \n"
			<< "   |     \\ \n"
			<< "   |        \n";
		break;

	default:
		cout
			<< "   |    O    \n"
			<< "   |   /|\\  \n"
			<< "   |   / \\  \n"
			<< "   |You're Dead\n";
	}
	// Output the base
	cout << "  =============\n" << endl;
}
