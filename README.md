# 2048-GAME
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
In order to quit the game, the player must press Q, and the menu will be displayed. For
continuing, the player must choose the RESUME option from the menu.
After each move, a random value of either 2 or 4 appears in one of the free cells.
The game starts with 2 cells.
Based on the values they contain, the cells are coloured differently. Each power of 2 has
a different colour associated, using the predefined colours from the ncurses library, as
well as custom colours. This helps the player to identify cells that can be merged more easily.
The free cells are empty and coloured in white.
If there are no more valid moves, the game ends, and the message "GAME OVER" is displayed,
as well as the score. If the current score is greater than the previous highest score, a
congratulatory message is displayed. 

Tema contine o implementare a jocului 2048, cu un meniu principal.
Cerinte completate:
Cerinta 1: realizarea meniului
Meniul principal al programului contine optiunile:
NEW GAME: inceperea unui nou joc
RESUME: reluarea unui joc. In cazul in care jucatorul incearca selectarea
optiunii RESUME fara sa existe un joc disponibil, se va afisa mesajul:
"RESUME option unavailable. Please start a new game". Daca exista un joc
disponibil, atunci selectarea optiunii RESUME va duce la reluarea jocului din
punctul in care a fost abandonat.
QUIT: iesire din joc

Cerinta 2: tabla de joc & panou de control
Tabla de joc este formata din 16 celule de dimensiune identica. Atunci cand e
selectata optiunea NEW GAME, sunt generate cele 2 celule aleatorii. In timpul
jocului, panoul de control afiseaza data si ora (format: dd-mm-yyyy hh:mm), o
legenda a miscarilor valide, care precizeaza numarul miscarilor valide si
evidentiaza miscarea cea mai avantajoasa (miscarea in dreptul careia scrie
" - best move") si scorul curent.

Cerinta 3: implementarea jocului
Cu ajutorul functiilor LeftMove, RightMove, UpMove, DownMove, jocul deplaseaza
celulele in directia dorita de jucator. Pentru a juca, sunt folosite tastele:
A - mutare la stanga
W - mutare in sus
D - mutare la dreapta
S - mutare in jos
Q - optiunea de a iesi din joc (revenirea la meniu)
Dupa fiecare mutare, e generata o celula noua, este actualizat scorul si se
testeaza daca jocul poate continua. In cazul in care nu se mai pot efectua
miscari valide sau in cazul in care s-a format numarul 2048, jocul se incheie.
Este afisat un mesaj ("GAME OVER" / "YOU WON"), scorul obtinut, scorul record
si, optional, daca scorul obtinut reprezinta un record nou, un mesaj de
felicitare.
In functie de valorile continute, celulele de pe tabla de joc au culori
diferite. Celulele goale sunt colorate cu alb si nu afiseaza nicio valoare.
Celulele care contin aceeasi valoare sunt afisate cu aceeasi culoare. Am
folosit culorile definite de biblioteca ncurses, precum si alte culori, care
sunt initializate la inceputul functiei main.
Dupa efectuarea unei mutari valide, generarea unei celule aleatorie poate dura
ceva timp, intrucat programul genereaza celule aleatorii pana cand intalneste
o celula goala. Atunci cand se intampla acest lucru, programul afiseaza "Please
wait..." pe ecran, in continuarea panoului de control.

Cerinta 4: miscarea automata
Daca expira timpul de asteptare setat (10 secunde) fara ca jucatorul sa apese
vreo tasta, programul initiaza o miscare automata cu ajutorul functiei hint.
Aceasta functie returneaza cea mai avantajoasa directie de mutare in functie
de numarul de celule eliberate; daca mai multe directii elibereaza un numar
maxim de celule, atunci functia 'hint' va returna directia care determina
obtinerea unui punctaj maxim.

Cerinta 5: terminarea jocului
Dupa cum am mentionat mai sus, dupa efectuarea fiecarei miscari, programul
testeaza daca jocul poate continua. Acest lucru se realizeaza prin functia
'gameOver' care returneaza 0 daca jocul poate fi continuat, 1 daca in situatia
game-over si 2, daca jucatorul a castigat. Dupa terminarea jocului, este
afisat un mesaj, punctajul, recordul, iar jucatorul trebuie sa apese o tasta
pentru a reveni la meniu.

Pentru bonus:
- culorile celulelor: celulele cu aceeasi valoare sunt marcate prin aceeasi
culoare
- am definit culori cu ajutorul init_color pentru a evita repetarea culorilor
predefinite in biblioteca ncurses
- legenda mentioneaza si directia cea mai avantajoasa de mutare
- atunci cand este generata o noua celula, programul afiseaza mesajul "Please
wait...", prin care jucatorul e informat ca tasta pe care a apasat-o urmeaza
sa fie prelucrata de aplicatie
- atunci cand o runda de joc se termina, programul afiseaza un scor de record,
precum si un mesaj in cazul in care jucatorul a reusit sa doboare recordul
anterior
