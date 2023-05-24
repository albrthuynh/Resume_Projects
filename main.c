/****************************
 * Program 3: TwentyFour Part Two
 * 
 * Course: CS 211, Spring 2023
 * System: MacOS using VSCode
 * Student Author: Albert Huynh
 *
 * ***************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

typedef struct Node *NodePtr;

struct Node{
	int data;
	char operator;
	NodePtr pNext;
}; 

//deleting an element on the top of the linked list (pHead) / Stack
int pop(NodePtr *pHead){
	NodePtr nodeDeleted = *pHead;
	int num = (*pHead)->data;

	(*pHead) = (*pHead)->pNext;

	free(nodeDeleted);
	return num;
}

//deleting an element on the top of the linked list(pHead) / Stack but for operators
char popOperator(NodePtr *pHead){
	NodePtr nodeDeleted = *pHead;
	char op = (*pHead)->operator;

	(*pHead) = (*pHead)->pNext;

	free(nodeDeleted);
	return op;
}

//inserting an element into the top of the linked list (pHead) / Stack
void push(NodePtr *pHead, int newNumber){
	NodePtr pTemp = (NodePtr)malloc(sizeof(struct Node));
	pTemp->data = newNumber;
	pTemp->pNext = *pHead; //setting pTemp to the next node

	*pHead = pTemp;
}

//inserting an element into the top of the linked list (pHead) / Stack but for operators
void pushOperator(NodePtr *pHead, char newOp){
	NodePtr pTemp = (NodePtr)malloc(sizeof(struct Node));
	pTemp->operator = newOp;
	pTemp->pNext = *pHead; //setting pTemp to the next node

	*pHead = pTemp;
}

//applying an easy mode puzzle
void easyMode(int *gameList){
	int randomPuzzle = rand() % 12;
	int numbersForEasyMode[48];
	int easyPuzzles[100][4]; 

	char filename[] = "easy.txt";
	FILE *filePtr  = fopen(filename, "r");

	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	char inputString[81];
	int count = 0;
	while(fscanf(filePtr, "%s", inputString) != EOF) {
		int x = atoi(inputString);
		numbersForEasyMode[count] = x;
		count++;
	}
	fclose(filePtr);

	count = 0;
	for(int row = 0; row < 12; row++){
		for(int col = 0; col < 4; col++){
			easyPuzzles[row][col] = numbersForEasyMode[count];
			count++;
		}
	}

	//setting the numbers array in main to the correct numbers from the file
	gameList[0] = easyPuzzles[randomPuzzle][0];
	gameList[1] = easyPuzzles[randomPuzzle][1];
	gameList[2] = easyPuzzles[randomPuzzle][2];
	gameList[3] = easyPuzzles[randomPuzzle][3];
}

//applying a medium mode puzzle
void mediumMode(int *gameList){
	int mediumPuzzles[100][4];
	int randomPuzzle = rand() % 24;
	int numbersForMediumMode[96];

	char filename[] = "medium.txt";
	FILE *filePtr  = fopen(filename, "r");

	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	char inputString[81];
	int count = 0;
	while(fscanf(filePtr, "%s", inputString) != EOF) {
		int x = atoi(inputString);
		numbersForMediumMode[count] = x;
		count++;
	}
	fclose(filePtr);

	count = 0;
	for(int row = 0; row < 24; row++){
		for(int col = 0; col < 4; col++){
			mediumPuzzles[row][col] = numbersForMediumMode[count];
			count++;
		}
	}

	//setting the numbers array in main to the correct numbers from the file
	gameList[0] = mediumPuzzles[randomPuzzle][0];
	gameList[1] = mediumPuzzles[randomPuzzle][1];
	gameList[2] = mediumPuzzles[randomPuzzle][2];
	gameList[3] = mediumPuzzles[randomPuzzle][3];
}

// Applying a random hard mode puzzle
void hardMode(int *gameList){
	int hardPuzzles[100][4];
	int randomPuzzle = rand() % 11;
	int numbersForHardMode[48];

	char filename[] = "hard.txt";
	FILE *filePtr  = fopen(filename, "r");

	if(filePtr == NULL) {
		printf("Error: could not open %s for reading\n", filename);
		exit(-1);
	}

	char inputString[81];
	int count = 0;
	while(fscanf(filePtr, "%s", inputString) != EOF) {
		int x = atoi(inputString);
		numbersForHardMode[count] = x;
		count++;
	}
	fclose(filePtr);

	count = 0;
	for(int row = 0; row < 11; row++){
		for(int col = 0; col < 4; col++){
			hardPuzzles[row][col] = numbersForHardMode[count];
			count++;
		}
	}

	//setting the numbers array in main to the correct numbers from the file
	gameList[0] = hardPuzzles[randomPuzzle][0];
	gameList[1] = hardPuzzles[randomPuzzle][1];
	gameList[2] = hardPuzzles[randomPuzzle][2];
	gameList[3] = hardPuzzles[randomPuzzle][3];
}

// true if it is a valid operator and false if not
bool validOperator(char operator){
	if(operator == '-' || operator == '+' || operator == '*' || operator == '/' || operator == '(' || operator == ')'){
		return true;
	}
	return false;
}

// getting the priority for the operator to compare to eachother (used in the infix to postfix function)
int getPriority(char op) {
    if(op == '*' || op == '/') {
        return 2;
    }
    else if(op == '+' || op == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

//swapping two numbers (pointers) making them pass by reference 
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

//the algorithm for selection sort (used to compare whether the userInput uses the same numbers or not)
void selectionSort(int array[]){
    int lowestIndex;

    for(int i = 0; i < 3; i++){
        lowestIndex = i;
        for(int j = i + 1; j < 4; j++){
            if(array[j] < array[lowestIndex]){
                lowestIndex = j;
            }
        }
        swap(&array[lowestIndex], &array[i]);
    }
}

//converting the userInput with parentheses to a postfix string. ensuring PEMDAS and easier for stack calculation
void convertingToPostfix(char *infix, char *postfix){
    int i = 0;
    int j = 0;
    int len = strlen(infix);
    NodePtr stack = NULL;

    for(int i = 0; i < len; i++){
        if(infix[i] == ' '){
            continue;
        }
        if(isdigit(infix[i])){
            postfix[j++] = infix[i];
        }
        else if(infix[i] == '('){
            pushOperator(&stack, infix[i]);
        }
        else if(infix[i] == ')'){
            while(stack != NULL && stack->operator != '('){
                postfix[j++] = popOperator(&stack);
            }
            if(stack == NULL){
				//ensuring that if there is an error there won't be anything more added to the postfix
				// EXAMPLE: extra '(' or extra ')'
				postfix[j] = '\0';
                return;
            }
            else{
                popOperator(&stack);
            }
        }
        else if(validOperator(infix[i])){
            while(stack != NULL && getPriority(stack->operator) >= getPriority(infix[i])){
                postfix[j++] = popOperator(&stack);
            }
            pushOperator(&stack, infix[i]);
        }
    }

    while(stack != NULL){
        if(stack->operator == '(' || stack->operator == ')'){
			return;
        }
        postfix[j++] = popOperator(&stack);
    }

    postfix[j] = '\0';
}

//performing the calculation on the postfix string
int calculation(char *postfix){
    NodePtr stack = NULL;
    int len = strlen(postfix);
    int num1 = 0;
    int num2 = 0;
    int calculator = 0;
    int postfixNums = 0;

    for(int i = 0; i < len; i++){
        if(isdigit(postfix[i])){
            postfixNums = postfix[i] - '0';
            push(&stack, postfixNums);
        }
    
        if(postfix[i] == '+'){
            num1 = pop(&stack);
            num2 = pop(&stack);
            calculator = num2 + num1;
            push(&stack, calculator);
            printf("%d + %d = %d.\n", num2, num1, calculator);
        }
        else if(postfix[i] == '-'){
            num1 = pop(&stack);
            num2 = pop(&stack);
            calculator = num2 - num1;
            push(&stack, calculator);
            printf("%d - %d = %d.\n", num2, num1, calculator);
        }
        else if(postfix[i] == '*'){
            num1 = pop(&stack);
            num2 = pop(&stack);
            calculator = num2 * num1;
            push(&stack, calculator);
            printf("%d * %d = %d.\n", num2, num1, calculator);
        }
        else if(postfix[i] == '/'){
            num1 = pop(&stack);
            num2 = pop(&stack);
            calculator = num2 / num1;
            push(&stack, calculator);
            printf("%d / %d = %d.\n", num2, num1, calculator);
        }
    }

	// popping all remaining elements within the stack to ensure that there is no memory leak
	while(stack != NULL){
		pop(&stack);
	}
    return calculator;
}

int main() {
	srand(1);

	char postfix[81];
	char difficultyUserInput;
	int numbersForGame[4];
	char userInputString[81];
	int result;

	printf("Welcome to the game of TwentyFour Part Two!\n");
	printf("Use each of the four numbers shown exactly once, \n");
	printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
	printf("to yield the value twenty-four.\n");

	//while loop for when the user inputs option 2
	while(true){
		printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");
		printf("Your choice --> ");
		scanf(" %c", &difficultyUserInput);

		if(difficultyUserInput == 'E'){
			easyMode(numbersForGame);
		}
		else if(difficultyUserInput == 'M'){
			mediumMode(numbersForGame);
		}
		else if(difficultyUserInput == 'H'){
			hardMode(numbersForGame);
		}
		else{
			easyMode(numbersForGame);
		}
		//while loop for when the user inputs option 1
		while(true){
			int numbersFromUser[10];
			bool correctOps = true;
			printf("The numbers to use are: %d, %d, %d, %d.\n", numbersForGame[0], numbersForGame[1], numbersForGame[2], numbersForGame[3]);
			printf("Enter your solution: ");
			scanf(" %[^\n]", userInputString);

			for(int i = 0; i < strlen(userInputString); i++){
				if(userInputString[i] == ' '){
					continue;
				}
				if(validOperator(userInputString[i]) == false && isdigit(userInputString[i]) == false){
					correctOps = false;
					break;
				}
			}
			int amountOfCorrectNums = 0;
			int indexUser = 0;
			int indexGame = 0;

			//creating an array which contains the numbers from the UserInput
			for(int i = 0; i < strlen(userInputString); i++){
				if(isdigit(userInputString[i])){
					numbersFromUser[indexUser] = atoi(&userInputString[i]);
					indexUser++;
				}
			}

			//sorting the two arrays
			selectionSort(numbersForGame);
			selectionSort(numbersFromUser);

            convertingToPostfix(userInputString, postfix);

			//checking to see if the two arrays contain the same values or not
			for(int i = 0; i < 4; i++){
				if(numbersForGame[i] == numbersFromUser[i]){
					amountOfCorrectNums++;
				}
			}

			//Seeing if the correct amount of operators are used (3)
			int numOfCorrectOps = 0;
			for(int i = 0; i < strlen(userInputString); i++){
				if(validOperator(userInputString[i]) && userInputString[i] != '(' && userInputString[i] != ')'){
					numOfCorrectOps++;
				}
			}

			//counting '(' and ')'
			int numOfClosingP = 0;
			int numOfOpenP = 0;
			for(int i = 0; i < strlen(userInputString); i++){
				if(userInputString[i] == '('){
					numOfOpenP++;
				}
				else if(userInputString[i] == ')'){
					numOfClosingP++;
				}
			}

			//test cases to see if the userInput is valid or not

			//invalid symbol test case
			if(correctOps == false){
				printf("Error! Invalid symbol entered. Please try again.\n\n");
				if(difficultyUserInput == 'E'){
					easyMode(numbersForGame);
				}
				else if(difficultyUserInput == 'M'){
					mediumMode(numbersForGame);
				}
				else if(difficultyUserInput == 'H'){
					hardMode(numbersForGame);
				}
				else{
					easyMode(numbersForGame);
				}
				continue;
			}
			//seeing if the user uses the correct numbers 
			else if(amountOfCorrectNums != 4){
				printf("Error! You must use all four numbers, and use each one only once. Please try again.\n\n");
				if(difficultyUserInput == 'E'){
					easyMode(numbersForGame);
				}
				else if(difficultyUserInput == 'M'){
					mediumMode(numbersForGame);
				}
				else if(difficultyUserInput == 'H'){
					hardMode(numbersForGame);
				}
				else{
					easyMode(numbersForGame);
				}
				continue;
			}
			//seeing if there are too many values 
			else if(numOfCorrectOps != 3){
                calculation(postfix);
				printf("Error! Too many values in the expression.\n");
			}
			// checking if the amount of closing parentheses is greater than the open
			else if(numOfClosingP > numOfOpenP){
                calculation(postfix);
				printf("Error! Too many closing parentheses in the expression.\n");
			}
			//if the expression is valid proceed to do calculation and print a win or lose message
			else{
                result = calculation(postfix);

				if(result == 24){
					printf("Well done! You are a math genius.\n");
				}
				else{
					printf("Sorry. Your solution did not evaluate to 24.\n");
				}
			}
			
			//the menu options
			int userMenuOption = 0;
			printf("\nEnter:\t1 to play again,\n");
			printf("\t2 to change the difficulty level and then play again, or\n");
			printf("\t3 to exit the program.\n");
			printf("Your choice --> ");
			scanf(" %d", &userMenuOption);

			if(userMenuOption == 3){
				printf("\nThanks for playing!\n");
				printf("Exiting...\n");
				exit(0);
			}
			else if(userMenuOption == 1){
				if(difficultyUserInput == 'E'){
					easyMode(numbersForGame);
				}
				else if(difficultyUserInput == 'M'){
					mediumMode(numbersForGame);
				}
				else if(difficultyUserInput == 'H'){
					hardMode(numbersForGame);
				}
				else{
					easyMode(numbersForGame);
				}
				continue; //continues the while loop for option 1 with a new puzzle from the original difficultyUserInput
			}
			else if(userMenuOption == 2){
				break; //breaking to the outer while loop so the difficulty can be changed (difficultyUserInput changes)
			}
		}
	}
	return 0;
}