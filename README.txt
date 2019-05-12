Hangman information:

The program simulates a version of the classic game Hangman.
User will be prompted at the start of the game to select a difficulty
level of 1, 2, or 3. This will determine the length of the phrase
that is selected for the player to use during that instance of
the game. the game will then print out a "gallow" typical of the 
game and begin prompting the user for single letter guesses. each 
incorrect guess will result in another part of the hangman's body
to appear on users screen. each correct guess will unveil to the
player the letters location in the phrase. The game continues this
way until the entire hangman is on the gallow (5 incorrect guesses)
or the user has guessed the phrase. The user will then be prompted
to continue or end the program.

How to compile:

Using Cygwin Terminal with the c++ development compiler packet,
navigate to the files directory. command to compile(without 
quotation marks): "g++ hangman.cpp -o hangman.exe" This will 
create an executable file called hangman.exe. to run this file
simply type: ./hangman.exe