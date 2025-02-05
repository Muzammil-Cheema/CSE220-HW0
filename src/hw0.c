#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hw0_functions.h"
#define ROWS 5
#define COLS 5
#define BOARD_SIZE ROWS*COLS
#define FAILURE 4

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

char choice[5];
int gameOver = 0, filledBoardSpaces = 0, stringLen = 0;

//scanf(" %c", &choice); //this command will erase whitespace in the token selection and read 1 char 
//(replace the 'c' with a 'd' to read an int)



int main(){
    game();
	return 0;
}



void printBoard(){
    printf("     1 2 3 4 5\n     v v v v v\n");
    for (int i = 0; i < 5; i++){
        printf("%d > ", i+1);
        for (int j = 0; j < 5; j++){
            printf("%c ", board[i][j]);
        }
        printf("< %d\n", i+1);
    }
    printf("     ^ ^ ^ ^ ^\n     1 2 3 4 5\n");
}

void game(){
    //Initial check of how many baord spaces are pre-filled. Used for winning condition check.
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (isdigit(board[i][j]) != 0)
                filledBoardSpaces++;

    //Initialize variables that store user input and incorrect input flags
    char piece = '-';
    int row = -1, col = -1;
    int invalidPiece = 0, invalidRow = 0, invalidCol = 0;

    //Skyscrapers game logic
    while (gameOver == 0){
        printBoard();

        //Checks if correct piece is chosen
        invalidPiece = 0;
        while(invalidPiece == 0) {
            printf("Choose a piece (1-5) or q to quit: ");
            scanf(" %s", choice);
            if (isValidChoice('p', choice) == 2){
                gameOver = 2;
                break;
            }
            if (isValidChoice('p', choice) != 0){
                printf("Invalid Choice. ");
                continue;
            }
            piece = choice[0];
            invalidPiece = 1;
        }
        if (gameOver == 2)
            break;
        
        
        //Checks if correct row is chosen
        invalidRow = 0; 
        while (invalidRow == 0){
            printf("Choose a row (0-4): ");
            scanf(" %s", choice);
            if (isValidChoice('r', choice) != 0){
                printf("Invalid Choice. ");
                continue;
            }
            row = choice[0] - '0';
            invalidRow = 1;
        } 
        

        //Checks if correct column is chosen
        invalidCol = 0;
        while(invalidCol == 0){
            printf("Choose a column (0-4): ");
            scanf(" %s", choice);
            if (isValidChoice('c', choice) != 0){
                printf("Invalid Choice. ");
                continue;
            }
            col = choice[0] - '0';
            invalidCol = 1;
        }
        

        //Checks if board space is empty
        if (board[row][col] != '-')
            printf("Invalid choice. That space is already occupied.\n");
        else {
            board[row][col] = piece;
            filledBoardSpaces++;
        }

        if (filledBoardSpaces == BOARD_SIZE){
            gameOver = 1;
            printf("Congratulations, you have filled the board!\n");
            printBoard();
        }
    }
}


int isValidChoice(char question, char response[]){
    if (strcmp(response, "q") == 0)
        return 2;
    if (strlen(response) > 1)
        return 3;
    
    char res = response[0];
    res -= '0';
    switch (question)
    {
    case 'p':
        if (res < 1 || res > 5)
            return 1;
        break;
    case 'r': case 'c':
        if (res < 0 || res > 4)
            return 1;
        break;
    default:
        printf("Unexpected behavior in choice validity checking");
        exit(FAILURE);
        break;
    }

    return 0;
}