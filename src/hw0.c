#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hw0_functions.h"
#define ROWS 5
#define COLS 5
#define FAILURE 1

int top_key[COLS] = {1, 2, 3, 4, 5};
int bottom_key[COLS] = {1, 2, 3, 4, 5};
int left_key[ROWS] = {1, 2, 3, 4, 5};
int right_key[ROWS] = {1, 2, 3, 4, 5};

char board[ROWS][COLS] = {
    {'1', '1', '2', '-', '3'}, 
    {'3', '2', '2', '3', '3'}, 
    {'2', '1', '-', '4', '4'}, 
    {'2', '-', '3', '2', '-'}, 
    {'4', '5', '4', '1', '3'}};

char choice;
int gameOver = 0;
int filledBoardSpaces = 0;
int boardSize = sizeof(board) / sizeof(board[0][0]);

//scanf(" %c", &choice); //this command will erase whitespace in the token selection and read 1 char 
//(replace the 'c' with a 'd' to read an int)



int main(){
    game();
	return 0;
}



void printBoard(){
    printf("     1 2 3 4 5\n     v v v v v\n");
    for(int i = 0; i < 5; i++){
        printf("%d > ", i+1);
        for (int j = 0; j < 5; j++){
            printf("%c ", board[i][j]);
        }
        printf("< %d\n", i+1);
    }
    printf("     ^ ^ ^ ^ ^\n     1 2 3 4 5\n");
}

void game(){
    //Initial check of how many baord spaces are pre-filled
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (isdigit(board[i][j]) == 1)
                filledBoardSpaces++;
        }
    }

    //Initialize variables that store user input
    int piece = -1, row = -1, col = -1;

    //Skyscrapers game logic
    while (gameOver == 0){
        printBoard();

        //Checks if correct piece is chosen
        Invalid1: 
        printf("Choose a piece (1-5) or q to quit: ");
        scanf(" %c", &choice);
        if (isValidChoice('p', choice) == 2){
            gameOver = 1;
            break;
        }
        if (isValidChoice('p', choice) == 0){
            printf("\nInvalid Choice. ");
            goto Invalid1;
        }
        piece =  choice - '0';
        
        //Checks if correct row is chosen
        Invalid2: 
        printf("Choose a row (0-4): ");
        scanf(" %c", &choice);
        if (isValidChoice('r', choice) == 0){
            printf("\nInvalid Choice. ");
            goto Invalid2;
        }
        row = choice - '0';

        //Checks if correct column is chosen
        Invalid3: 
        printf("Choose a column (0-4): ");
        scanf(" %c", &choice);
        if (isValidChoice('c', choice) == 0){
            printf("\nInvalid Choice. ");
            goto Invalid3;
        }
        col = choice - '0';

        //Checks if board space is empty
        if (board[row][col] == '-')
            printf("Invalid choice. That space is already occupied.\n");
        else 
            board[row][col] = piece;

        if (filledBoardSpaces == boardSize){
            gameOver = 1;
            printf("Congratulations, you have filled the board!\n");
            printBoard();
        }
    }

    printf("Game is over.");
}

int isValidChoice(char question, int response){
    if (response == 'q')
        return 2;
    switch (question)
    {
    case 'p':
        if (response < 1 || response > 5)
            return 0;
        break;
    case 'r': case 'c':
        if (response < 0 || response > 4)
            return 0;
        break;
    default:
        printf("Unexpected behavior in choice validity checking");
        exit(FAILURE);
        break;
    }
    return 1;
}