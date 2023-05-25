/****************************
 * Program 5: Yahtzee
 * 
 * Course: CS 141, Fall 2022
 * System: MacOS using VSCode
 * Student Author: Albert Huynh
 *
 * Starter code provided by: Dr. Sara Riazi
 * ***************************/


#include <string>
#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;



//#################################################################################################



class Dice{
	private:
		int value;
        bool rolling;

	public:

		//Randomly assigns a value between from 1 to 6 to the dice.
		void roll(){
            int randNum = rand() % 6 + 1;
            value = randNum;
        }

		int reveal() {return value;}

        //sets the boolean to if the dice is kept or rolled
        void setRolling(bool boolean){
            rolling = boolean;
        }

        void unselectRolling(){
            this->rolling = true;
        }
        void selectRolling(){
            this->rolling = false;
        }

        bool getRolling(){
            return rolling;
        }

		//The autograder will set the values directly instead of calling roll() to avoid randomness!
		void setValue(int value) {this->value = value;}
};
//#################################################################################################

const int HAND_SIZE = 5;

class Hand {
	public:
		//Display the value of the five dice
        //reveals the dice
		void show(){
            cout << "Hand: ";
            for(int i = 0; i < HAND_SIZE; i++){
                cout << listOfDice[i].reveal() << " ";
            }
        }

        //when you roll the dice
		void play(){
            int diceRolls[5];
            for(int i = 0; i < HAND_SIZE; i++){
                if(listOfDice[i].getRolling()){
                    (*getDice(i)).roll();
                }
                this->listOfDice[i].unselectRolling();
            }
        }

        //gets the pointer to the dice desired
		Dice* getDice(int diceNum){
            return &listOfDice[diceNum];
        }
		
		//selection is the string of dice numbers that the player wants to keep.
		//For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.

        //false =  want to keep and true = does not want to keep the dice
		void setSelection(string selection){
            for(int i = 0; i < HAND_SIZE; i++){
                char a = char(i + 1) + '0';
                if(selection.find(a) != -1){
                    listOfDice[i].setRolling(false);
                }
                else{
                    listOfDice[i].setRolling(true);
                }
            }
        }

        //creating default constructor
		Hand(){
            for(int i = 0; i < HAND_SIZE; i++){
                Dice d1;
                d1.roll();
                listOfDice[i] = d1;
            }
        }
	private:
        Dice listOfDice[5];
};



//######################################################################


//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE=13; 

class Game {

    private:
        int Wscores[13] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	public:
		//calcScore returns a score of a hand (5 dice) for given row in the board. 
		//Note the rows are indexed from zero. 
		//For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.

        //Calculation of rows 0-5 (ONES TO SIX)
        //Starting the helper functions for calcScore()
        int CalcUpperBoard(Hand *hand, int row){
            int score = 0;
            if(row == 0){
                for(int i = 0; i < 5; i++){
                    if(hand->getDice(i)->reveal() == 1){
                        score += 1;
                    }
                }
            }
            else if(row == 1){
                for(int i = 0; i < 5; i++){
                    if(hand->getDice(i)->reveal() == 2){
                        score += 2;
                    }
                }
            }
            else if(row == 2){
                for(int i = 0; i < 5; i++){
                    if(hand->getDice(i)->reveal() == 3){
                        score += 3;
                    }
                }
            }
            else if(row == 3){
                for(int i = 0; i < 5; i++){
                    if(hand->getDice(i)->reveal() == 4){
                        score += 4;
                    }
                }
            }
            else if(row == 4){
                for(int i = 0; i < 5; i++){
                    if(hand->getDice(i)->reveal() == 5){
                        score += 5;
                    }
                }
            }
            else if(row == 5){
                for(int i = 0; i < 5; i++){
                    if(hand->getDice(i)->reveal() == 6){
                        score += 6;
                    }
                }
            }

            return score;
        }

        //Checks if there is a 3 in a row
        int CalcThreeOfAKind(Hand* hand, int row){
            bool isThree;

            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;
            int count5 = 0;
            int count6 = 0;

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 1){
                    count1++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 2){
                    count2++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 3){
                    count3++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 4){
                    count4++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 5){
                    count5++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 6){
                    count6++;
                }
            }


            int total = 0;
            if(count1 >= 3 || count2 >= 3 || count3 >= 3 || count4 >= 3 || count5 >= 3 || count6 >= 3){
                for(int i = 0; i < 5; i++){
                    total += hand->getDice(i)->reveal();
                }
                return total;
            }
            return 0;
        }

        //Checks for 4 of a kind
        int CalcFourOfAKind(Hand* hand, int row){
            int count;
        
            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;
            int count5 = 0;
            int count6 = 0;

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 1){
                    count1++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 2){
                    count2++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 3){
                    count3++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 4){
                    count4++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 5){
                    count5++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 6){
                    count6++;
                }
            }

            int total = 0;
            if(count1 >= 4 || count2 >= 4 || count3 >= 4 || count4 >= 4 || count5 >= 4 || count6 >= 4){
                for(int i = 0; i < 5; i++){
                    total += hand->getDice(i)->reveal();
                }
                return total;
            }
            return 0;
        }

        //Checking for 3 of a kind and a pair / yahtzee 
        int CalcFullHouse(Hand* hand, int row){
            bool threeInARow;
            if(CalcThreeOfAKind(hand, row) > 0){
                threeInARow = true;
            }
            else{
                threeInARow = false;
            }

            int count1 = 0;
            int count2 = 0;
            int count3 = 0;
            int count4 = 0;
            int count5 = 0;
            int count6 = 0;

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 1){
                    count1++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 2){
                    count2++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 3){
                    count3++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 4){
                    count4++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 5){
                    count5++;
                }
            }

            for(int i = 0; i < 5; i++){
                if(hand->getDice(i)->reveal() == 6){
                    count6++;
                }
            }

            int total = 0;

            if(count1 == 5 || count2 == 5 || count3 == 5 || count4 == 5 || count5 == 5 || count6 == 5){
                return 25;
            }
            if((count1 == 2 || count2 == 2 || count3 == 2|| count4 == 2 || count5 == 2 || count6 == 2) && threeInARow){
                return 25;
            }
            return 0;
        }

        //Checking the 3 cases for small straight
        int CalcSmallStraight(Hand* hand, int row){
            bool isStraight;
            string empty = "";
            for(int i = 0; i < 5; i++){
                empty += to_string(hand->getDice(i)->reveal());
            }   

            if(empty.find("1") < -1 && empty.find("2") < -1 && empty.find("3") < -1 && empty.find("4") < -1){
                return 30;
            }
            if(empty.find("2") < -1 && empty.find("3") < -1 && empty.find("4") < -1 && empty.find("5") < -1){
                return 30;
            }
            if(empty.find("3") < -1 && empty.find("4") < -1 && empty.find("5") < -1 && empty.find("6") < -1){
                return 30;
            }
            return 0;   
        }

        //checking the 2 cases for large straight
        int CalcLargeStraight(Hand* hand, int row){

            string empty = "";
            for(int i = 0; i < 5; i++){
                empty += (char(hand->getDice(i)->reveal()) + '0');
            }
            
            if((empty.find('1') != -1) && (empty.find("2")  != -1) && (empty.find("3")  != -1) && (empty.find("4")  != -1) && (empty.find("5")  != -1)){
                return 40;
            }

            if((empty.find("2")  != -1) && (empty.find("3")  != -1) && (empty.find("4")  != -1) && (empty.find("5")  != -1) && (empty.find("6")  != -1)){
                return 40;
            }
            return 0;
        }

        //checking for 5 in a row
        int CalcYahtzee(Hand* hand, int row){
            bool isYahtzee;
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 5; j++){
                    if(hand->getDice(i)->reveal() == hand->getDice(j)->reveal()){
                        isYahtzee = true;
                    }
                    else{
                        isYahtzee = false;
                        break;
                    }
                }
            }
            if(isYahtzee){
                return 50;
            }
            return 0;       
        }

        //using the helper functions to get the score
		int calcScore(Hand* hand, int row){
            int score = 0;
            if(row == 0 || row == 1 || row == 2 || row == 3 || row == 4 || row == 5){
                score = CalcUpperBoard(hand, row);
            }
            else if(row == 6){
                score = CalcThreeOfAKind(hand, row);
            }
            else if(row == 7){
                score = CalcFourOfAKind(hand, row);
            }
            else if(row == 8){
                score = CalcFullHouse(hand, row);
            }
            else if(row == 9){
                score = CalcSmallStraight(hand, row);
            }
            else if(row == 10){
                score = CalcLargeStraight(hand, row);
            }
            else if(row == 11){
                for(int i = 0; i < 5; i++){
                    score += hand->getDice(i)->reveal();
                }
            }
            else if(row == 12){
                score = CalcYahtzee(hand, row);
            }
            return score;
        }
		
		//Display the board
        //need to add something after the initial string
		void show(Hand* hand){
            cout << "1. Ones:               " << calcScore(hand, 0) << endl;
            cout << "2. Twos:               " << calcScore(hand, 1) << endl;
            cout << "3. Threes:             " << calcScore(hand, 2) << endl;
            cout << "4. Fours:              " << calcScore(hand, 3) << endl;
            cout << "5. Fives:              " << calcScore(hand, 4) << endl;
            cout << "6. Sixes:              " << calcScore(hand, 5) << endl;
            cout << "   Sum:                " << getUpperScore() << endl;
            cout << "   Bonus:              " << getBonusScore() << endl;
            cout << "7. Three of a kind:    " << calcScore(hand, 6) << endl;
            cout << "8. Four of a kind:     " << calcScore(hand, 7) << endl;
            cout << "9. Full house:         " << calcScore(hand, 8) << endl;
            cout << "10. Small straight:    " << calcScore(hand, 9) << endl;
            cout << "11. Large straight:    " << calcScore(hand, 10) << endl;
            cout << "12. Chance:            " << calcScore(hand, 11) << endl;
            cout << "13. Yahtzee:           " << calcScore(hand, 12) << endl;
            cout << "Total:                 " << getTotalScore() << endl;
        }

		//Returns the score of the upper part of the board
		int getUpperScore(){
            int total = 0;
            for(int i = 0; i < 6; i++){
                total += Wscores[i];
            }
            return total;
        }
		
		//Returns the score of the lower part of the board
		int getLowerScore(){
            int total = 0;
            for(int i = 6; i < 13; i++){
                total += Wscores[i];
            }
            return total;
        }
	

		//Returns the bonus points
		int getBonusScore(){
            int bonus = 0;
            if(getUpperScore() >= 63){
                bonus = 35;
            }
            return bonus;
        }

		//Returns the total score
		int getTotalScore(){
            return (getUpperScore() + getLowerScore() + getBonusScore());
        }

		//Play a hand based on the selected row
		void play(Hand* hand, int row){
            int totalScore = 0;
            totalScore += calcScore(hand, row);
            this->Wscores[row] = totalScore;
        }

		
		//Check to see if a row has been played or not (returns true if a row has been played)
		bool isPlayed(int row){
            // see if the row has a value of more than 0
            if(Wscores[row] == -1){
                return false;
            }
            else{
                return true;
            }
        }
		
		//Check to see if all rows haven been played or not (returns true if all rows have been played)
		bool isFinished(){
            for(int i = 0; i < 13; i++){
                if(!isPlayed(i)){
                    return false;
                }
            }
            return true;
        }
};

//#######################################################################################

//The run function is the main loop of your program
void run() {
    //Creating the starting values of first hand
    Game newGame;
    Hand* hand = new Hand;
    hand->play();

    //looping until the game is finished
    while(!newGame.isFinished()){
        int userInput;
        string keptDiceValues;
        for(int i = 0; i < 2; i++){
            hand->play();
            hand->show();
            cout << endl;
            cout << "Keep dice (s to stop rolling): ";
            cin >> keptDiceValues;
            if(keptDiceValues == "s"){
                break;
            }
            hand->setSelection(keptDiceValues);
        }
        cout << "Choose a combination to play ";
        cin >> userInput;
        newGame.play(hand, userInput);
        newGame.show(hand);
        break;
    }
}
//For these types of programs there exists many combinations that you might have missed. 
//The best way to check them all is to write test cases for your program. 
//Here I give you an example of checking large straight. You can design your own test cases for different parts.

void test_case() {
	Game game;
	Hand* hand = new Hand();
	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(5);
	
	bool check1 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check1 = false;
	}
	if (check1) {
		cout << "check 1 passed\n"; 
	}

	hand->getDice(0)->setValue(2);
	hand->getDice(1)->setValue(6);
	hand->getDice(2)->setValue(4);
	hand->getDice(3)->setValue(3);
	hand->getDice(4)->setValue(5);
	
	bool check2 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 40) {
		check2 = false;
	}

	if (check2) {
		cout << "check 2 passed\n"; 
	}

	hand->getDice(0)->setValue(3);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(5);
	hand->getDice(3)->setValue(6);
	hand->getDice(4)->setValue(3);

	bool check3 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check3 = false;
	}

	if (check3) {
		cout << "check 3 passed\n"; 
	}

	hand->getDice(0)->setValue(1);
	hand->getDice(1)->setValue(2);
	hand->getDice(2)->setValue(3);
	hand->getDice(3)->setValue(4);
	hand->getDice(4)->setValue(6);

	bool check4 = true;
	if (game.calcScore(hand, LARGE_STRAIGHT) != 0) {
		check4 = false;
	}

	if (check4) {
		cout << "check 4 passed\n"; 
	}
}

// THE AUTOGRADER WILL REPLACE THE MAIN FUNCTION. 
// DO NOT ADD ANY LOGIC OF YOUR PROGRAM HERE.
int main() {
	srand(time(0));
	run();
	//test_case();
	return 0;
}
