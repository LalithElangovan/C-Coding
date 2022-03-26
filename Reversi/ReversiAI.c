/* Lalith Vaishnav Elangovan*/

// Including the necessary libraries
//#include "project_reversi_skeleton.h" // DO NOT modify this line
//#include "lab8part2lib.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Note: You may want to add more function declarations here
// =========   Function declaration  ==========
bool hasMoves(char board[][26], int n, char colour);
int doMove(char board[][26], int n, int row, int col, char colour);
int makeSubMove(const char board[26][26], int n, char turn, int *row, int *col);
int doMove(char board[][26], int n, int row, int col, char colour);

// ========= Function implementation ==========

/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n)
{
    int i, j;
    printf("  ");
    for (int letters = 0; letters < n; letters++)
    {
        // printing out the characters using character addition. This is the first row identifier.
        printf("%c", 'a' + letters);
    }
    printf("\n");
    // To print the left hand sidee column along with the board
    for (i = 0; i < n; i++)
    {
        printf("%c ", 'a' + i);
        for (j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
            if (j == n - 1)
            {
                // Printing the final new line
                printf("\n");
            }
        }
    }
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col)
{
    // Returning true if the input is in bounds.
    if (row < n && col < n && row >= 0 & col >= 0)
        return true;
    return false;
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{   bool sandwiched = false;
    int toFlip = 0;
    //run sanity check
    if (deltaRow == 0 && deltaCol == 0)
    {
        return false;
    }
    //To check if move is within bounds
    if (positionInBounds(n, row, col)==false)
    {
        return false;
    }
    //To check if move can be placed
    if (board[row][col] != 'U')
    {
        return false;
    }
    //Move to next position    
    row += deltaRow;
    col += deltaCol;

    while (positionInBounds(n, row, col))
    {
        //Chain of characters is broken
        if (board[row][col] == 'U')
        {
            break;
        }
        //Chain ends here and end with same colour 
        if (board[row][col] == colour)
        {
            // To check if it is flanked by the same colour
            sandwiched = true;
            break;
        }
        //We have to add one to toFlip so that we flip the tile we are also on
        toFlip++;
        row += deltaRow;
        col += deltaCol;
    }

    if (sandwiched==true && toFlip>0)
    {
        return true;
    }
    else
        return false;
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col)
{
    //For each posssible move of the player, find the best reply of the opponent. Then we pick the move that gives 
    //the opponent the worst best reply
    //Best score is the biggest possible integer, that we aim to reduce
    unsigned int bestScore = -1;
    *row = 0;
    *col = 0;
    char copy[26][26];
    char opponent;
    //Set the colours of the players
    if (turn=='W'){
        opponent='B';
    }
    else{
        opponent = 'W';
    }
//This for loop is to iterate through all possible moves
    for (int tryRow = 0; tryRow < n; tryRow++)
    {
        for (int tryCol = 0; tryCol < n; tryCol++)
        {
            //Make a copy of the board
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    copy[i][j] = board[i][j];
                }
            }
            //Try making a move, if possible the function makes the move, else we try again with a different position
            if (doMove(copy, n, tryRow, tryCol, turn)==false)
                continue;

            int subRow, subCol;
            //See what the opponents highscore if they have to respond to the move made by our AI
            unsigned int score = makeSubMove(copy, n, opponent, &subRow, &subCol);
            //If opponent score is worse than before make this the best move to make
            if (score < bestScore)
            {
                bestScore = score;
                *row = tryRow;
                *col = tryCol;
            }
        }
    }
    //If we have no valid moves bestsocre + 1 = -1+1=0
    return bestScore + 1;
}

int makeSubMove(const char board[26][26], int n, char turn, int *row, int *col)
{
    char copy[26][26];
    int highscore = 0;
    int score;
    *row = 0;
    *col = 0;
//This for loop is to run through all possible moves that the computer can do
    for (int tryRow = 0; tryRow < n; tryRow++)
    {
        for (int tryCol = 0; tryCol < n; tryCol++)
        {
            //Copy the board state because we cannot change board
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    copy[i][j] = board[i][j];
                }
            //Score is the number of tiles that can be flipped
            score = doMove(copy, n, tryRow, tryCol, turn);
            //This is to enable the 'greedy part' to get the highest score
            if (score > highscore)
            {
                highscore = score;
                *row = tryRow;
                *col = tryCol;
            }
        }
    }

    return highscore;
}

//This function is to check whether player and comp have moves to do 
bool hasMoves(char board[][26], int n, char colour)
{
    //runs through all combinations to see if they are legal
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
            {
                for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
                {
                    if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

//This function does the move
int doMove(char board[][26], int n, int row, int col, char colour)
{
    char changes[26][26];
    int tilesFlipped = 0;
    int changeRow;
    int changeCol;
//sanity checks
    if (positionInBounds(n, row, col) == false)
    {
        return 0;
    }
    if (board[row][col] != 'U')
    {
        return 0;
    }
//creates a copy of the board to make changes on
    for (int copyRow = 0; copyRow < n; copyRow++)
    {
        for (int copyCol = 0; copyCol < n; copyCol++)
        {
            changes[copyRow][copyCol] = board[copyRow][copyCol];
        }
    }
//goes through all possible directions 
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++)
        {
            //If the move is legal on the board flip the pieces on the copy of the board
            if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol))
            {
                changeRow = row;
                changeCol = col;
                //Moves to the next character,will change row, col at the end 
                changeRow += deltaRow;
                changeCol += deltaCol;
            
                while (positionInBounds(n, changeRow, changeCol))
                {
                    //End of sequence
                    if (board[changeRow][changeCol] == colour)
                    {
                        break;
                    }
                    //This makes changes to each piece in the line and counts the number of pieces changed
                    changes[changeRow][changeCol] = colour;
                    tilesFlipped++;

                    changeRow += deltaRow;
                    changeCol += deltaCol;
                }
            }
        }
    }
//If no tiles were flipped no more valid moves 
    if (tilesFlipped>0)
    {
        changes[row][col] = colour;
//Then copy the changes back to the board
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                board[row][col] = changes[row][col];
            }
        }

        return tilesFlipped + 1;
    }

    else
        return 0;
}
