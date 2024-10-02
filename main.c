#include<ncurses.h>
#include<curses.h>
#include<stdlib.h>
#include<time.h>

#ifndef GAME2048_H
#include "game2048.h"
#endif

int main()
{
    int i, game[5][5]={0}, val1, val2, poz1, poz2, points = 0, play, high;

    // initializing the screen and keypad processing
    initscr();
    keypad(stdscr, TRUE);
    clear();
    noecho();
    cbreak();
    curs_set(0);

    // processing the previous highest score
    FILE *results;
    results = fopen("results.txt", "r");
    fscanf(results, "%d", &high);
    fclose(results);

    // creating windows for the game grid and the menu
    WINDOW *cel[16], *menu = initscr();
    for (i = 0; i < 16; i++)
    {
        cel[i] = newwin(5, 10, (i / 4 + 1) * 5 + 4, (i % 4 + 1) * 10);
    }
    keypad(menu, TRUE);

    // creating the custom colours
    start_color();
    init_color(COLOR_LIGHT_PINK, 1000, 700, 800);
    init_color(COLOR_LIGHT_GREEN, 500, 1000, 500);
    init_color(COLOR_TURQUOISE, 0, 1000, 1000);
    init_color(COLOR_LAVENDER, 800, 600, 1000);
    init_color(COLOR_LIGHT_ORANGE, 1000, 600, 0);
    
    // initializing the colour pairs for colouring cells
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_LIGHT_ORANGE, COLOR_BLACK);
    init_pair(9, COLOR_LIGHT_PINK, COLOR_BLACK);
    init_pair(10, COLOR_LIGHT_GREEN, COLOR_BLACK);
    init_pair(11,COLOR_LAVENDER, COLOR_BLACK);
    init_pair(12, COLOR_TURQUOISE, COLOR_BLACK);

    refresh();

    int option = 0, choice = 0;
    
    // processing the keys pressed by the player
    while (FOREVER)
    {
        // display menu
        PrintMainMenu(menu, option);
        choice = wgetch(menu);

        // navigating the menu using the up arrow / down arrow keys
        switch (choice)
        {
            case KEY_UP:
                option = (option + 2) % 3;
                break;
            case KEY_DOWN:
                option = (option + 1) % 3;
                break;
            case '\n':
            {
                // by pressing ENTER, the player chooses an option from the menu
                if (option == 2)
                {
                    // QUIT => exit the game
                    endwin();
                    return 0;
                }
                else
                {
                    clear();
                    if (option == 1 && CheckZero(game) == 1)
                    {
                        // the player chose RESUME but no previous game is
                        // available; a message is displayed
                        clear();
                        printw("RESUME option unavailable. ");
                        printw("Please start a new game\n");
                        printw("Press any key to return to the menu");
                        getch();
                        refresh();
                    }
                    else
                    {
                        if (option == 0)
                        {
                            // NEW GAME option

                            // initializing a new game matrix and two random
                            // cells to start the game
                            points = 0;
                            MatrZero(game);
                            poz1 = generator_random(game, &val1);
                            game[poz1 / 4][poz1 % 4] = val1;

                            do
                            {
                                poz2 = generator_random(game, &val2);
                            } while (poz1 == poz2);

                            game[poz2/ 4][poz2 % 4] = val2;
                        }

                        // starting / continuing the game
                        play = Play2048(game, cel, &points);
                        if (play == 1)
                        {
                            // the game is over
                            clear();
                            wclear(menu);
                            
                            // checking if the current score is higher than
                            // the previous best
                            if (points > high)
                            {
                                high = points;
                                results = fopen("results.txt", "w");
                                fprintf(results, "%d", high);
                                fclose(results);
                            }

                            // display a GAME OVER message, the score and
                            // the highest score
                            printw("GAME OVER :(\n");
                            printw("Your score: %d\n", points);
                            printw("Highest score: %d\n", high);

                            // if the player reached a new best score
                            // display a congratulatory message
                            if (high == points)
                            {
                                printw("NEW RECORD! GOOD JOB!\n");
                            }

                            // the player can return to the menu by pressing
                            // any key
                            printw("\nPress any key to return to the menu\n");
                            getch();

                            MatrZero(game);
                            wrefresh(menu);
                            refresh();
                        }

                        if (play == 2)
                        {
                            // the player has won

                            // display a message, the score and the
                            //  highest score
                            wclear(menu);
                            printw("YOU WON!! :)\n");
                            printw("Your score: %d\n", points);
                            printw("Highest score: %d\n", high);

                            // check if current score is higher than
                            // the previous best
                            if (points > high)
                            {
                                high = points;
                                results = fopen("results.txt", "w");
                                fprintf(results, "%d", high);
                                fclose(results);
                            }

                            if (high == points)
                            {
                                // display a congratulatory message
                                printw("NEW RECORD! GOOD JOB!\n");
                            }

                            // return to the menu if player presses any key
                            printw("\nPress any key to return to the menu\n");

                            MatrZero(game);
                            getch();
                            wrefresh(menu);
                        }
                    }
                }
                break;
            }
        }
    }

    getch();
    endwin();
    
    return 0;
}
