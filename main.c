/****************************
 * Program 2: Weaver
 * 
 * Course: CS 211, Spring 2023
 * System: MacOS using VSCode
 * Starter Code Author: Ellen Kidane
 * Student Author: Albert Huynh
 *
 * ***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

//global variables
int totalWords = 0; // the # of words based off what the # of letters should be based off user input 
char** wordsList; // the 2D array that is dynamically allocated, holding all the words
const int growthNum = 3; // the number the array will grow by

//dynamically adding the words to the array
void AddWords(char ***pArray, char newWord[81], int *currentSize, int *maxSize){
    char **pNew = NULL;
    
    if(*currentSize == *maxSize){
        pNew = (char**)malloc(sizeof(char*) * (*maxSize + growthNum));

        //copying the elements into pNew
        for(int i = 0; i < *maxSize; i++){
            pNew[i] = (*pArray)[i];
        }
        //free the array then assign the new array to it
        free(*pArray);  

        *pArray = pNew;
        *maxSize += growthNum;
    }
    (*pArray)[*currentSize] = strdup(newWord);
    (*currentSize)++;
}

//Reading in the words of the userInput size
void ReadingInWords(int numOfLetters){
    totalWords = 0; // resetting the count of total words to 0 whenever the function is called
    int currentSize = 0; // resetting currentsize to 0 
    int maxSize = 0; 
    char** tempArray = (char**)malloc(sizeof(char*) * growthNum);
    maxSize = growthNum; //assigning the maxSize to growthNum

    //starter code segment starts
	char filename[] = "words.txt";
	FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading
	
	// Check that the file was able to be opened
	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	// Read each word from file, and print them one by one
	char inputString[81];
	while(fscanf(filePtr, "%s", inputString) != EOF) {
        if(strlen(inputString) == numOfLetters){
            AddWords(&tempArray, inputString, &currentSize, &maxSize);
            totalWords++;
        }
	}
    // Close the file
	fclose(filePtr);
    //Assigning wordsList to the tempArray
    wordsList = tempArray;
}

//Checking the words to see if the user's word is the correct length based off userInput
bool CorrectLength(int userInput, char userWord[81]){
    if(userInput == strlen(userWord)){
        return true; // is the correct length
    }
    return false; // is not the correct length
}

//Checking to see if the userWord exists within wordsList given
bool ValidWord(char userWord[81]){
    for(int i = 0; i < totalWords; i++){
        if(strcmp(userWord, wordsList[i]) == 0){
            return true; // exists in the dictionary
        }
    }
    return false; // does not exist in the dictionary
}

//compares two characters
bool compareChar(char a, char b){
    if(a == b){
        return true; //is equal
    }
    return false; //not equal
}

//checks if one letter is different or not
bool OneLetterDifferent(char prevWord[81], char userWord[81]){
    int count = 0; // counter for the different letters
    int size = strlen(prevWord);

    for(int i = 0; i < size; i++){
        if(compareChar(prevWord[i], userWord[i]) == false){
            count++; //for each difference the counter increases
        }
    }
    
    if(count == 1){
        return true; // There is only a one letter difference
    }
    return false; // There is more than a one letter difference
}

int main() {
    srand(1);
    int numLetters; // # of letters in the word
    int numLetterOfWords; // # of words based off the # of lettters
    char startingWord[81]; // startingWord based off userInput
    char endingWord[81]; // endingWord based off userInput
    char randomWord1[81]; // randomWord 1
    char randomWord2[81]; // randomWord 2

    char realStartingWord[81]; // this sets it to the starting word once and doesn't change to ensure correct output
    char realEndingWord[81]; // this sets it to the ending word once and doesn't change to ensure correct output

	printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
	printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	printf("Enjoy!\n\n");

    int randomNum; // random integer
    int randomNum2; // a different random integer
    while(true){
        printf("How many letters do you want to have in the words? ");
        scanf(" %d", &numLetters);

        ReadingInWords(numLetters); // dynamically growing array
        numLetterOfWords = totalWords;

        printf("Number of %d-letter words found: %d.\n\n", numLetters, numLetterOfWords);
        // start of the game sequence
        while(true){
            while(true){
                printf("Enter starting and ending words, or 'r' for either for a random word: ");
                scanf(" %s", startingWord);
                scanf(" %s", endingWord);

                // if userInput is r then startingWord would get assigned to a random word
                if(strcmp(startingWord, "r") == 0){
                    randomNum = rand() % numLetterOfWords;
                    strcpy(startingWord, wordsList[randomNum]);
                }

                //if userInput is r for the second word then endingWord would get assigned to a random word
                if(strcmp(endingWord, "r") == 0){
                    randomNum2 = rand() % numLetterOfWords;
                    strcpy(endingWord, wordsList[randomNum2]);
                }

                //checking all the false cases
                if((strcmp(startingWord, "r") != 0) && (strcmp(endingWord, "r") != 0)){ //if the user does not input r then they will put in the words they want
                    if(CorrectLength(numLetters, startingWord) == false){
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n", startingWord, numLetters);
                    }
                    else if(CorrectLength(numLetters, endingWord) == false){
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n", endingWord, numLetters);
                    }
                    else if(ValidWord(startingWord) == false){
                        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", startingWord);
                    }
                    else if(ValidWord(endingWord) == false){
                        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endingWord);
                    }
                    else{
                        printf("Your starting word is: %s.\n", startingWord);
                        printf("Your ending word is: %s.\n", endingWord);
                        strcpy(realStartingWord, startingWord);
                        strcpy(realEndingWord, endingWord);
                        break;
                    }
                }
            }

                printf("\nOn each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
                printf("You may also type in 'q' to quit guessing.\n");

                int turnNumber = 1;
                char prevWord[81];
                char currentWord[81];
                strcpy(prevWord, realStartingWord);

                //start of the game functionality
                while(true){
                    printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", turnNumber, prevWord, realEndingWord);
                    scanf(" %s", currentWord);
                    
                    //checking if userInput is q first
                    if(currentWord[0] == 'q'){
                        break;
                    }
                    else if(CorrectLength(numLetters, currentWord) == false){
                        printf("Your word, '%s', is not a %d-letter word. Try again.\n", currentWord, numLetters);
                    }
                    else if(ValidWord(currentWord) == false){
                        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", currentWord);
                    }
                    else if(OneLetterDifferent(prevWord, currentWord) == false){
                        printf("Your word, '%s', is not exactly 1 character different. Try again.\n", currentWord);
                    }
                    else{
                        //checking if the user won
                        strcpy(prevWord, currentWord);
                        if(strcmp(prevWord, realEndingWord) == 0){
                            printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", realStartingWord, realEndingWord, turnNumber);
                            break;
                        }
                        turnNumber++;
                    }
                }
                int userPlayAgain;
                printf("\nEnter: \t1 to play again,\n");
                printf("\t2 to change the number of letters in the words and then play again, or\n");
                printf("\t3 to exit the program.\n");
                printf("Your choice --> ");
                scanf(" %d", &userPlayAgain);
                // menu options and also makes sure to free any of the dynamically allocated memory
                if(userPlayAgain == 3){
                    printf("\nThanks for playing!\n");
                    printf("Exiting...");
                    for(int i = 0; i < totalWords; i++){
                        free(wordsList[i]);
                    }
                    free(wordsList);
                    exit(0);
                }
                else if(userPlayAgain == 1){
                    continue;
                }
                else if(userPlayAgain == 2){
                    for(int i = 0; i < totalWords; i++){
                        free(wordsList[i]);
                    }
                    free(wordsList);
                    break;
                }
            }
        }
	return 0;
}