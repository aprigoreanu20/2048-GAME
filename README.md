# 2048 GAME
**OVERVIEW**

This project represents an implementation of the popular game 2048, using the ncurses
library in C. Players can slide the tiles in a grid in order to combine them and create
new tiles with greater powers of 2. The game ends either when the player creates the number
2048, or when there are no valid moves possible.

The game also has a menu feature, where the player can choose between three options: NEW
GAME, RESUME and QUIT.

The game displays a score panel, which shows the current score of the player, the date,
as well as the valid moves, highlighting which move is the most advantageous based on how
many cells it frees up. If the player waits 10 seconds without making any moves, the game
will automatically move in the best direction.


**MENU**

From the menu, the player can choose to either start a new game, resume an already started
game or to quit. The RESUME option will become available only if there is an already
existing game, otherwise, the game will display the following message: "RESUME option
unavailable. Please start a new game".

**2048 GAME**

The game board is represented by 16 identical cells. The player can press the following keys
in order to play:
* A: left move
* D: right move
* W: up move
* S: down move

In order to quit the game, the player must press Q, and the menu will be displayed. To continue,
the player must choose the RESUME option from the menu.\
After each move, a random value of either 2 or 4 appears in one of the free cells.
The game starts with 2 cells, and the player can slide the tiles in order to merge cells
that contain the same value, and thus create tiles with greater numbers.\
Based on the values they contain, the cells are coloured differently. Each power of 2 has
a different colour associated, using the predefined colours from the ncurses library, as
well as custom colours. This helps the player to identify cells that can be merged more easily.
The free cells are empty and coloured in white.\
The panel above the game grid helps the player, showing all of the valid moves, as well as a hint
(the best move). It is considered that the best move is the one that frees up the most cells. If
multiple moves free up the same number of cells, the best move is the one that generates the most
points. If the player does not make any move, the game waits for 10 seconds before automatically
applying the hint.\
If there are no more valid moves, the game ends, and the message "GAME OVER" is displayed,
as well as the score. If the current score is greater than the previous highest score, a
congratulatory message is displayed. Also, the highest score is updated. To return to the
menu, the player can press any key.

**FEATURES**

* Menu
* 4x4 grid
* Tile sliding and merging
* Score tracking
* Game over detection
* Highest score
* Resume game option
* Custom colours for tiles
* Valid moves panel with the best move highlighted
* Hint
* Automatic tile sliding after waiting time expires

**COMPILATION AND EXECUTION**

The project includes Makefile.
* To compile the project, type **make** in the terminal. This command will generate an executable named
2048
* To run the project, either run the generated executable by typing **./2048** in a terminal, or use the **make
run** command
* To remove the executable and other compiled files, type **make clean** in the terminal
