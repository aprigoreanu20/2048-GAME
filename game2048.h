#ifndef GAME2048_H
#define GAME2048_H

#define FOREVER 1

// custom colours definitions for cells
#define COLOR_LIGHT_ORANGE 8
#define COLOR_LIGHT_PINK 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LAVENDER 11
#define COLOR_TURQUOISE 12

// headers for functions used to implement 2048 game

// function for saving the free cells from a game grid into an array
int ValidCells(int (*)[5], int *);

// function for generating a random cell and a random value (2 or 4)
// after each move the player makes, a new value appears into one
//  of the free cells
// the random cell position is returned by the function, the random value
// is returned through the second parameter of the function
int generator_random(int (*)[5], int *);

// function that initializes the game grid (represented by a matrix) to 0
void MatrZero(int (*)[5]);

// function that creates a copy of the game matrix
void MatrCopy(int (*)[5], int (*)[5]);

// function that checks if the game matrix is null
int CheckZero(int (*)[5]);

// function that calculates the binary logarithm of a number 
int power(int);

// function that generates the left move in the 2048 game
int LeftMove(int (*)[5], int *);

// function that generates the right move in the 2048 game
int RightMove(int (*)[5], int *);

// function that generates the up move in the 2048 game
int UpMove(int (*)[5], int *);

// function that generates the down move in the 2048 game
int DownMove(int (*)[5], int *);

// function that checks if the game is over
int gameOver(int (*)[5]);

// function that determines the best move
int hint(int (*)[5], int *);

// function that clears the control panel
void ClearCtrlPanel();

// function that prints the date and hour (format dd-mm-yyyy hh:mm)
void PrintDate();

// function that displays all of the valid moves
void MovePanel(int (*)[5]);

// function that displays the cells of the game grid
void WindowPrint(WINDOW *, int, int);

// function for printing the main menu
void PrintMainMenu(WINDOW *, int);

// function for 2048 game
int Play2048(int (*)[5], WINDOW **, int *);

#endif