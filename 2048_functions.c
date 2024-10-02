#include<ncurses.h>
#include<curses.h>
#include<stdlib.h>
#include<time.h>

#ifndef GAME2048_H
#include "game2048.h"
#endif

// implementations of the functions from 2048.h file

// function for saving the free cells from a game grid into an array
// the game grid is represented by the game matrix
int ValidCells(int game[5][5], int valids[16])
{
    int i, j, k;
    k = 0;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (game[i][j] == 0)
            {
                // the value 0 in the matrix means that the corresponding
                // cell is free in the game grid
                valids[k] = i * 4 + j;
                k++;
            }
        }
    }

    // the function returns the number of free cells
    return k;
}

// function for generating a random cell and a random value (2 or 4)
// after each move the player makes, a new value appears into one
//  of the free cells
int generator_random(int game[5][5], int *val)
{
    int random_cell, pos;
    int valid_cells[16], nr_valids;

    // the new cell is generated randomly out of the free cells in the grid
    nr_valids = ValidCells(game, valid_cells);
    srand(time(NULL));
    pos = (rand() % nr_valids);
    random_cell = valid_cells[pos];

    // the random value that appears in the cell is either 2 or 4
    *val = (rand() % 2);
    if (*val == 0)
        *val = 2;
    else
        *val = 4;

    // the random cell position is returned by the function, the random value
    // is returned through the second parameter of the function
    return random_cell;
}

// function that initializes the game grid (represented by a matrix) to 0
// this is helpful when generating a new game
void MatrZero(int game[5][5])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            game[i][j] = 0;
        }
    }
}

// function that creates a copy of the game matrix
void MatrCopy(int game[5][5], int cp[5][5])
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            cp[i][j] = game[i][j];
        }
    }
}

// function that checks if the game matrix is null
int CheckZero(int game[5][5])
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (game[i][j] != 0)
            {
                // the function returns 0 if the matrix is not null
                return 0;
            }
        }
    }

    // the function returns 1 if the matrix is null
    return 1;
}

// function that calculates the binary logarithm of a number
int power(int n)
{
    // the function returns 0 if n is equal to 0
    if (n == 0)
        return 0;
    
    int p = 0;
    while (n > 1)
    {
        n /= 2;
        p++;
    }
    return p;
}

// function that generates the left move in the 2048 game
int LeftMove(int game[5][5], int *valid)
{
    int i, j, k, points, nr_zero, aux[5];

    // if the move is valid then the value transmitted through the second
    // parameter wil be 1, otherwise it will be 0
    *valid = 0;

    // the number of points won through this move
    points = 0;

    for (i = 0; i < 4; i++)
    {
        // checking if the left move is valid
        // a valid move either merges cells or slides cells

        // counting the number of empty cells on each row
        nr_zero = 0;
        for (j = 0; j < 4; j++)
        {
            if (game[i][j] == 0)
                nr_zero++;
        }

        // the left move is valid in either one of these cases
        if (nr_zero == 3 && game[i][0] == 0)
            *valid = 1;
        if (nr_zero == 2 && !(game[i][0] != 0 && game[i][1] != 0))
            *valid = 1;
        if (nr_zero == 1 && game[i][3] != 0)
            *valid = 1;
    
        // generating the left move by sliding the tiles to the left
        k = 0;
        for (j = 0; j < 4; j++)
        {
            if (game[i][j] != 0)
            {
                aux[k] = game[i][j];
                k++;
            }
        }
        for (k = 4 - nr_zero; k < 4; k++)
            aux[k] = 0;
        
        // merging adjacent cells that contain the same value
        if (aux[0] == aux[1] && aux[0] != 0)
        {
            aux[0] *= 2;
            points +=aux[0];
            aux[1] = 0;
            *valid = 1;
        }
        if (aux[2] == aux[1] && aux[1] != 0)
        {
            aux[1] *= 2;
            points += aux[1];
            aux[2] = 0;
            *valid = 1;
        }
        if (aux[3] == aux[2] && aux[2] != 0)
        {
            aux[2] *= 2;
            points +=aux[2];
            aux[3] = 0;
            *valid = 1;
        }

        // a new left move is necessary after sliding the cells to the left
        k = 0;
        for (j = 0; j < 4; j++)
        {
            if (aux[j] != 0)
            {
                game[i][k] = aux[j];
                k++;
            }
        }
        while (k < 4)
        {
            game[i][k] = 0;
            k++;
        }
    }

    // the function returns the number of points won after left move
    // if the move is valid then the value transmitted through the second
    // parameter wil be 1, otherwise it will be 0
    return points;
}

// function that generates the right move in the 2048 game
// this function follows the same logic as LeftMove function
int RightMove(int game[5][5], int *valid)
{
    int i, j, k, points, nr_zero, aux[4];
    
    *valid = 0;
    points = 0;

    for (i = 0; i < 4; i++)
    {
        // checking if the right move is valid
        // counting the number of empty cells on each row
        nr_zero = 0;

        for (j = 3; j >= 0; j--)
        {
            if(game[i][j] == 0)
            {
                nr_zero++;
            }
        }

        // the right move is valid in either one of these cases
        if (nr_zero == 3 && game[i][3] == 0)
            *valid = 1;
        if (nr_zero == 2 && !(game[i][3] != 0 && game[i][2] != 0))
            *valid = 1;
        if (nr_zero == 1 && game[i][0] != 0)
            *valid = 1;

        // generating the right move by sliding the tiles to the right
        k = 3;
        for (j = 3; j >= 0; j--)
        {
            if (game[i][j] != 0)
            {
                aux[k] = game[i][j];
                k--;
            }
        }
        while (k >= 0)
        {
            aux[k] = 0;
            k--;
        }

        // merging adjacent cells that contain the same value
        if (aux[3] == aux[2] && aux[3] != 0)
        {
            aux[3] *= 2;
            points +=aux[3];
            aux[2] = 0;
            *valid = 1;
        }
        if (aux[2] == aux[1] && aux[2] != 0)
        {
            aux[2] *= 2;
            points += aux[2];
            aux[1] = 0;
            *valid = 1;
        }
        if (aux[0] == aux[1] && aux[1] != 0)
        {
            aux[1] *= 2;
            points +=aux[1];
            aux[0] = 0;
            *valid = 1;
        }

        // a new right move is necessary after sliding the cells to the right
        k = 3;
        for (j = 3; j >= 0; j--)
        {
            if (aux[j] != 0)
            {
                game[i][k] = aux[j];
                k--;
            }
        }
        while (k >= 0)
        {
            game[i][k] = 0;
            k--;
        }
    }

    // the function returns the number of points won after right move
    return points;
}

// function that generates the up move in the 2048 game
int UpMove(int game[5][5], int *valid)
{
    int i, j, k, points, aux[5], nr_zero;

    points = 0;
    *valid = 0;

    for (j = 0; j < 4; j++)
    {
        // checking if the up move is valid
        // counting the number of empty cells on each column
        nr_zero = 0;

        for (i = 0; i < 4; i++)
        {
            if (game[i][j] == 0)
                nr_zero++;
        }

        // the up move is valid in either one of these cases
        if (nr_zero == 3 && game[0][j] == 0)
            *valid = 1;
        if (nr_zero == 2 && !(game[0][j] != 0 && game[1][j] != 0))
            *valid = 1;
        if (nr_zero == 1 && game[3][j] != 0)
            *valid = 1;

        // generating the up move by sliding the tiles up
        k = 0;
        for (i = 0; i < 4; i++)
        {
            if (game[i][j] != 0)
            {
                aux[k] = game[i][j];
                k++;
            }
        }
        while (k < 4)
        {
            aux[k] = 0;
            k++;
        }

        // merging adjacent cells that contain the same value
        if (aux[0] == aux[1] && aux[0] !=0)
        {
            aux[0] *= 2;
            points += aux[0];
            aux[1] = 0;
            *valid = 1;
        }
        if (aux[1] == aux[2] && aux[1] != 0)
        {
            aux[1] *= 2;
            points += aux[1];
            aux[2] = 0;
            *valid = 1;
        }
        if (aux[2] == aux[3] && aux[2] != 0)
        {
            aux[2] *= 2;
            points += aux[2];
            aux[3] = 0;
            *valid = 1;
        }

        // a new up move is necessary after sliding the cells up
        k = 0;
        for (i = 0; i < 4; i++)
        {
            if (aux[i] != 0)
            {
                game[k][j] = aux[i];
                k++;
            }
        }
        while (k < 4)
        {
            game[k][j] = 0;
            k++;
        }
    }

    // the function returns the number of points won after up move
    return points;
}

int DownMove(int game[5][5], int *valid)
{
    int i, j, k, points, aux[5], nr_zero;


    points = 0;
    *valid = 0;

    for (j = 0; j < 4; j++)
    {
        // checking if the down move is valid
        // counting the number of empty cells on each column
        nr_zero = 0;

        for (i = 3; i >= 0; i--)
        {
            if (game[i][j] == 0)
                nr_zero++;
        }

        // the down move is valid in either one of these cases
        if (nr_zero == 3 && game[3][j] == 0)
            *valid = 1;
        if (nr_zero == 2 && !(game[3][j] != 0 && game[2][j] != 0))
            *valid = 1;
        if (nr_zero == 1 && game[0][j] != 0)
            *valid = 1;

        // generating the down move by sliding the tiles down
        k = 3;
        for (i = 3; i >= 0; i--)
        {
            if (game[i][j] != 0)
            {
                aux[k] = game[i][j];
                k--;
            }
        }
        while (k >= 0)
        {
            aux[k] = 0;
            k--;
        }

        // merging adjacent cells that contain the same value
        if (aux[2] == aux[3] && aux[3] != 0)
        {
            aux[3] *= 2;
            points += aux[3];
            aux[2] = 0;
            *valid = 1;
        }
        if (aux[1] == aux[2] && aux[2] != 0)
        {
            aux[2] *= 2;
            points += aux[2];
            aux[1] = 0;
            *valid = 1;
        }
        if (aux[0] == aux[1] && aux[1] != 0)
        {
            aux[1] *= 2;
            points += aux[1];
            aux[0] = 0;
            *valid = 1;
        }

        // a new down move is necessary after sliding the cells down
        k = 3;
        for (i = 3; i >= 0; i--)
        {
            if (aux[i] != 0)
            {
                game[k][j] = aux[i];
                k--;
            }
        }
        while (k >= 0)
        {
            game[k][j] = 0;
            k--;
        }
    }

    // the function returns the number of points won after down move
    return points;
}

// function that checks if the game is over
// return 0 => game can continue
// return 1 => game over
// return 2 => the player won
int gameOver(int game[5][5])
{
    int i, j, play;

    play = 1;

    // jucatorul castiga daca reuseste sa formeze 2048
    // este necesara parcurgerea intregii matrici game pentru
    // a determina daca jucatorul a castigat

    // the value 2048 is searched in the entire game grid
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (game[i][j] == 2048)
            {
                // the player wins after forming 2048
                return 2;
            }

            // the game can continue if there are empty cells in the grid
            //  or if there are cells that can be merged
            if (game[i][j] == 0)
                play = 0;
            
            if (i + 1 < 4 && game[i + 1][j] == game[i][j])
                play = 0;
            
            if (j + 1 < 4 && game[i][j + 1] == game[i][j])
                play = 0;
        }
    }

    // the function returns either 0, 1 or 2 based on the state of the game
    return play;
}

// function that determines the best move
// return 0 => left move
// return 1 => right move
// return 2 => up move
// return 3 => down move
// it is considered that the best move frees up the most cells
// the function also determines which of the 4 moves are valid
// and stores them into the valid array
int hint(int game[5][5], int valid[5])
{
    int i, j, vpoints[5], maxim, cp_game[5][5], nr_zero[5] = {0};

    // for each direction (left, right, up or down), the game calculates
    // how many empty cells would be in the grid after making the move
    MatrCopy(game, cp_game);
    vpoints[0] = LeftMove(cp_game, &valid[0]);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (cp_game[i][j] == 0)
                nr_zero[0]++;
        }
    }

    MatrCopy(game, cp_game);
    vpoints[1] = RightMove(cp_game, &valid[1]);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (cp_game[i][j] == 0)
                nr_zero[1]++;
        }
    }

    MatrCopy(game, cp_game);
    vpoints[2] = UpMove(cp_game, &valid[2]);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (cp_game[i][j] == 0)
                nr_zero[2]++;
        }
    }

    MatrCopy(game, cp_game);
    vpoints[3] = DownMove(cp_game, &valid[3]);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (cp_game[i][j] == 0)
                nr_zero[3]++;
        }
    }

    // se determina miscarea cea mai avantajoasa prin obtinerea
    // maximului din vectorul 'nr_zero'
    // the best move is determined by comparing the number of null cells
    // that each move would bring
    maxim = 0;
    for (i = 0; i < 4; i++)
    {
        if (valid[maxim] == 0 && valid[i] == 1)
            maxim = i;

        if (nr_zero[i] > nr_zero[maxim] && valid[i] == 1)
            maxim = i;
            
        // if two moves free up the same number of cells, the best move is the
        // one that yields the greater number of points
        if (nr_zero[i] == nr_zero[maxim] && vpoints[i] > vpoints[maxim])
            maxim = i;
    }

    // the function returns the best move in the game
    return maxim;
}

// function that clears the control panel
void ClearCtrlPanel()
{
    move(0,0);
    int i;

    // clearing the date and hour
    for (i = 1; i <= 22; i++)
        printw(" ");
    printw("\n");

    // eliminating each of the lines in the panel
    for (i = 1; i <= 14; i++)
        printw(" ");
    printw("\n");
    
    for (i = 1; i <= 35; i++)
        printw(" ");
    printw("\n");
    
    for (i = 1; i <= 36; i++)
        printw(" ");
    printw("\n");
    
    for (i = 1; i <= 33; i++)
        printw(" ");
    printw("\n");
    
    for (i = 1; i <= 35; i++)
        printw(" ");
    printw("\n");

    // clearing the score
    printw("            ");
}

// function that prints the date and hour (format dd-mm-yyyy hh:mm)
void PrintDate()
{
    int day, month, year, hour, minute;
    time_t time_scs;
    struct tm *time_str;

    time(&time_scs);
    time_str = localtime(&time_scs);

    day = time_str->tm_mday;
    month = time_str->tm_mon + 1;
    year= 1900 + time_str->tm_year;
    hour = time_str->tm_hour;
    minute = time_str->tm_min;

    move(0,0);
    printw("Date: %02d-%02d-%d %02d:%02d\n", day, month, year, hour, minute);
}

// function that displays all of the valid moves
void MovePanel(int game[5][5])
{
    int valid[5], rec, i, nr_valid = 0;

    // this function uses 'hint' in order to determine the valid moves
    rec = hint(game, valid);

    // printing the number of valid moves
    for (i = 0; i < 4; i++)
    {
        if (valid[i] == 1)
            nr_valid++;
    }
    printw("Valid moves: %d\n", nr_valid);

    // printing each of the valid moves (up, down, right, left)
    // and highlighting the best move
    if (valid[0] == 1)
    {
        printw("Press 'A' for left move");
        if (rec == 0)
            printw(" - best move");
        printw("\n");
    }

    if (valid[1] == 1)
    {
        printw("Press 'D' for right move");
        if (rec == 1)
            printw(" - best move");
        printw("\n");
    }

    if (valid[2] == 1)
    {
        printw("Press 'W' for up move");
        if (rec == 2)
            printw(" - best move");
        printw("\n");
    }

    if (valid[3] == 1)
    {
        printw("Press 'S' for down move");
        if (rec == 3)
            printw(" - best move");
        printw("\n");
    }

    for (i = 1; i <= 4 - nr_valid; i++)
        printw("\n");
}


// function that displays the cells of the game grid
void WindowPrint(WINDOW *win, int value, int color_pair)
{
    if (value != 0)
    {
        // cells are coloured based on the value they contain
        wattron(win, COLOR_PAIR(color_pair));
        box(win, ACS_VLINE, ACS_HLINE);
        mvwprintw(win, 2, 4, "%d", value);
        wattroff(win, COLOR_PAIR(color_pair));
    }
    else
    {
        // empty cells are coloured in white 
        wattron(win, COLOR_PAIR(0));
        box(win, ACS_VLINE, ACS_HLINE);
        wattroff(win, COLOR_PAIR(0));
    }
}

// function for printing the main menu
void PrintMainMenu(WINDOW *menu, int option)
{
    wclear(menu);
    
    // the menu options are displayed in white
    wattron(menu, COLOR_PAIR(0));
    mvwprintw(menu, 1, 2, "MAIN MENU");
    mvwprintw(menu, 3, 2, "New Game");
    mvwprintw(menu, 4, 2, "Resume");
    mvwprintw(menu, 5, 2, "Quit");
    wattroff(menu, COLOR_PAIR(0));

    // when an option is selected, it is coloured in yellow
    wattron(menu, COLOR_PAIR(3));
    if (option == 0)
    {
        mvwprintw(menu, 3, 2, "New Game");
    }
    if (option == 1)
    {
        mvwprintw(menu, 4, 2, "Resume");
    }
    if (option == 2)
    {
        mvwprintw(menu, 5, 2, "Quit");
    }
    wattroff(menu, COLOR_PAIR(3));

    wrefresh(menu);
}

// function for 2048 game
int Play2048(int game[5][5], WINDOW *cel[16], int *points)
{
    int i, j, poz, play, option, p, valid, ValidMove[5], val, gen;
    char ch;

    refresh();
    keypad(stdscr, TRUE);

    play = 0;

    // displaying the score and moves panel
    ClearCtrlPanel();
    PrintDate();
    MovePanel(game);
    printw("SCORE: %d\n", *points);

    // displaying the cells
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            wclear(cel[i * 4 + j]);
            p = power(game[i][j]);
            if (p >= 7)
            {
                p++;
            }
            WindowPrint(cel[i * 4 + j], game[i][j], p);
            wrefresh(cel[i * 4 + j]);
        }
    }
    
    // for the automatic move, the time of the last move is saved
    // after a wait time of 10 seconds, the game automatically moves
    nodelay(stdscr, TRUE);
    time_t start_time = time(NULL);
    int wait_time = 10;

    // processing the keys pressed by the player
    while (FOREVER)
    {
        if (play != 0)
        {
            // the game can continue as long as play is not equal to 0
            break;
        }

        // processing the key pressed by the player
        ch = getch();

        if (ch != ERR)
        {
            // this means that the player has pressed a key during the wait time
            if (ch == 'w' || ch == 'W')
            {
                // generating the up move
                *points += UpMove(game, &valid);

                if (valid == 1)
                {
                    // if the up move is valid
                    // then a value appears in a random cell
                    gen = 0;
                    mvprintw(8, 0,"Please wait...");
                    refresh();

                    do
                    {
                        poz = generator_random(game, &val);
                        if (game[poz / 4][poz % 4] == 0 && gen == 0)
                        {
                            game[poz / 4][poz % 4] = val;
                            gen = 1;
                        }
                    }while (gen == 0);

                    mvprintw(8, 0, "              ");
                    refresh();
                }
            }

            if (ch == 's' || ch == 'S')
            {
                // generating the down move
                *points += DownMove(game, &valid);

                if (valid == 1)
                {
                    // if the down move is valid
                    // then a value appears in a random cell
                    gen = 0;
                    mvprintw(8, 0,"Please wait...");
                    refresh();

                    do
                    {
                        poz = generator_random(game, &val);
                        if (game[poz / 4][poz % 4] == 0 && gen == 0)
                        {
                            game[poz / 4][poz % 4] = val;
                            gen = 1;
                        }
                    }while (gen == 0);

                    mvprintw(8, 0, "              ");
                    refresh();
                }
            }

            if (ch == 'a' || ch == 'A')
            {
                // generating the left move
                *points += LeftMove(game, &valid);

                if (valid == 1)
                {
                    // generating a new value in a random cell
                    // if the move is valid
                    gen = 0;
                    mvprintw(8, 0,"Please wait...");
                    refresh();

                    do
                    {
                        poz = generator_random(game, &val);
                        if (game[poz / 4][poz % 4] == 0 && gen == 0)
                        {
                            game[poz / 4][poz % 4] = val;
                            gen = 1;
                        }
                    }while (gen == 0);

                    mvprintw(8, 0, "              ");
                    refresh();
                }
            }

            if (ch == 'd' || ch == 'D' || ch == KEY_RIGHT)
            {
                // generating the right move
                *points += RightMove(game, &valid);

                if (valid == 1)
                {
                    // generating a new value in a random cell
                    // if the move is valid
                    gen =0;
                    mvprintw(8, 0,"Please wait...");
                    refresh();

                    do
                    {
                        poz = generator_random(game, &val);
                        if (game[poz / 4][poz % 4] == 0 && gen == 0)
                        {
                            game[poz / 4][poz % 4] = val;
                            gen = 1;
                        }
                    }while (gen == 0);

                    mvprintw(8, 0, "              ");
                    refresh();
                }
            }

            if (ch == 'q' || ch == 'Q')
            {
                // the player wishes to return to the menu, so the
                // game is interrupted
                break;
            }

            // displaying the score panel
            ClearCtrlPanel();
            PrintDate();
            MovePanel(game);
            printw("SCORE: %d", *points);

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    wclear(cel[i * 4 + j]);
                    p = power(game[i][j]);
                    if (p >= 7)
                        p++;
                    WindowPrint(cel[i * 4 + j], game[i][j], p);
                    wrefresh(cel[i * 4 + j]);
                }
            }

            // start time is updated after each move
            start_time = time(NULL);
        }

        if (time(NULL) - start_time >= wait_time)
        {
            // the player has not pressed any keys in 10 seconds
            //  the game automatically moves in the most
            // advantageous direction
            option = hint(game, ValidMove);

            // move in the best advantageous direction and generate a new cell
            switch (option)
            {
                case 0:
                    *points += LeftMove(game, &valid);

                    if (valid == 1)
                    {
                        gen = 0;
                        mvprintw(8, 0,"Please wait...");
                        refresh();

                        do
                        {
                            poz = generator_random(game, &val);
                            if (game[poz / 4][poz % 4] == 0 && gen == 0)
                            {
                                game[poz / 4][poz % 4] = val;
                                gen = 1;
                            }
                        }while (gen == 0);

                        mvprintw(8, 0, "              ");
                        refresh();
                    }

                    break;

                case 1:
                    *points += RightMove(game, &valid);

                    if (valid == 1)
                    {
                        gen = 0;
                        mvprintw(8, 0,"Please wait...");
                        refresh();

                        do
                        {
                            poz = generator_random(game, &val);
                            if (game[poz / 4][poz % 4] == 0 && gen == 0)
                            {
                                game[poz / 4][poz % 4] = val;
                                gen = 1;
                            }
                        }while (gen == 0);

                        mvprintw(8, 0, "              ");
                        refresh();
                    }

                    break;

                case 2:
                    *points += UpMove(game, &valid);

                    if (valid == 1)
                    {
                        gen = 0;
                        mvprintw(8, 0,"Please wait...");
                        refresh();

                        do
                        {
                            poz = generator_random(game, &val);
                            if (game[poz / 4][poz % 4] == 0 && gen == 0)
                            {
                                game[poz / 4][poz % 4] = val;
                                gen = 1;
                            }
                        }while (gen == 0);

                        mvprintw(8, 0, "              ");
                        refresh();
                    }
                    break;
                case 3:
                    *points += DownMove(game, &valid);

                    if (valid == 1)
                    {
                        gen = 0;
                        mvprintw(8, 0,"Please wait...");
                        refresh();

                        do
                        {
                            poz = generator_random(game, &val);
                            if (game[poz / 4][poz % 4] == 0 && gen == 0)
                            {
                                game[poz / 4][poz % 4] = val;
                                gen = 1;
                            }
                        }while (gen == 0);

                        mvprintw(8, 0, "              ");
                        refresh();
                    }
                    break;
            }

            // display the score panel
            ClearCtrlPanel();
            PrintDate();
            MovePanel(game);
            printw("SCORE: %d", *points);

            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    wclear(cel[i * 4 + j]);
                    p = power(game[i][j]);
                    if (p >= 7)
                        p++;
                    WindowPrint(cel[i * 4 + j], game[i][j], p);
                    wrefresh(cel[i * 4 + j]);
                }
            }

            // update start time after a move is made
            start_time = time(NULL);
        }

        // check if the game can continue
        play = gameOver(game);

        refresh();
    }
    nodelay(stdscr,FALSE);

    // return 1 for game over
    // return 0 if the game can continue (the player pressed Q)
    return play;
}
