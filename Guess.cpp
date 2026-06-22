//Homework 4 #3 write a guessing game

//You are going to write a short program to play a guessing game in which two players attempt to guess a number. 
// You will write the program where the players can be either a human player or a computer player of varying intelligence.

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MAXGUESS = 1000;  // range is [0,MAXGUESS]

// Polymorphic classes
class Player {
public:
    virtual int getGuess() = 0;  //can be overriden by dervied classes and should be defined by the derived class
    virtual void binarySearch(bool tooHigh, int guess) {}  //function to get back results and calculate smart answer
    virtual ~Player() {}
};
 
class HumanPlayer:public Player { //derived from Player
public:
    int getGuess(){ //HumanPlayer::getGuess() should prompt the user to enter a number and return the value entered from the keyboard
        int guess;
        cout << "Guess a number between 1 to " << MAXGUESS << ": ";
        cin >> guess;
        return guess;
    } 
}; 

class ComputerPlayer: public Player { //derived from Player
public:
    int getGuess() {//ComputerPlayer::getGuess() randomly selects a number from 0 to MAXGUESS
        //how to make it random
        int guess = rand() % MAXGUESS + 1; //taken from code later - should use random instead?
        cout << "The Computer's guess is " << guess << endl;
        return guess;
    }
}; 

//modify the program so that SmartComputerPlayer plays a better game with a binary search
//add functions to the classes derived from Players so that the play function can send the results of a guess back correctly
    //computer must be told if it's last guess was too high or too low, and if the opponent's guess was too high or too low. Computer can then use this info for it's next guess

class SmartComputerPlayer: public ComputerPlayer {//computer player does not play the guessing game very well, it will only make random guesses
//inherits from ComputerPlayer
private:
    int low;
    int high;
    int guess;

public:
    //constructor 
    SmartComputerPlayer() : low(1), high(MAXGUESS), guess(0) {} //if I have a constructor here, does the parent need one?

    int getGuess() {
        guess = (low + high) / 2; //finds mid point
        cout << "The Smart Computer's guess is " << guess << endl;
        return guess;
    }
    void binarySearch(bool tooHigh, int guess) {
        if (guess == 0 || guess >= MAXGUESS)  //range check
            return;

        if (tooHigh)
            high = guess - 1; 
        else
            low = guess + 1;

    }
};


 Player* selectPlayers(int PLAYERNUMBER) {
    //write a menu that allows the user to select whether player 1 or player2 are human or computer players
     int role = 0;

     do {
         cout << endl;
         cout << "Please make a selection for Player " << PLAYERNUMBER << ": " << endl;
         cout << "1. Human Player" << endl;
         cout << "2. Computer Player" << endl;
         cout << "3. Smart Computer Player" << endl;
         cout << "-----------------------------" << endl;
         cout << "Please enter a number between 1 and 3: ";
         cin >> role;

         switch (role) {
         case 1:
             return new HumanPlayer();
         case 2:
             return new ComputerPlayer();
         case 3:
             return new SmartComputerPlayer();
         default:
             cout << "Invalid choice, please try again.";
         }

     } while (role < 1 || role > 3); //do while loop
     return nullptr;
}


// You can change this however you want
bool checkForWin(int guess, int answer, Player& guesser, Player& other) {
    if (answer == guess) {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess) {
        cout << "Your guess is too high." << endl;
        //tell computer it was too high
        guesser.binarySearch(true, guess); //sends back results to both players
        other.binarySearch(true, guess); 
    }
    else {
        cout << "Your guess is too low." << endl;
        //tell computer it was too low
        guesser.binarySearch(false, guess);
        other.binarySearch(false, guess);
    }
    return  false;
}

int play(Player& player1, Player& player2) {  // do not change this line
    // change anything you like below this line
    int guess = 0;
    int numGuesses = 0;
    int answer = rand() % MAXGUESS + 1; //removed redundant answer integer

    bool win = false;
    int round = 1;

    while (!win) { 
        cout << endl;
        cout << "****** - Round " << round << " - ******" << endl; //to match the exe code visual more
        cout << endl;
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer, player1, player2); //need both players as arguments to pass back to the computer
        if (win) break;

        cout << endl;
        cout << "\nPlayer 2's turn to guess." << endl;
        guess = player2.getGuess();
        numGuesses++;
        win = checkForWin(guess, answer, player2, player1);
        round += 1;
    }
    return numGuesses;
}

int main() {
    //generate random number
    srand(time(0));

    //run function slectPlayers
    Player* player1 = selectPlayers(1);
    Player* player2 = selectPlayers(2);

    //run game
    play(*player1, *player2);

    //delete dynamically allocated objects
    delete player1;
    delete player2;
}