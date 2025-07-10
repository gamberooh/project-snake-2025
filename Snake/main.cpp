#include "include/game.h"
#include <iostream>

#define DARK_GREEN 8

void initializeNcurses() {
    initscr(); // Inizializza ncurses
    cbreak(); // Disabilita il buffering dell'input
    noecho(); // Non mostra i caratteri digitati
    curs_set(0); // Nasconde il cursore
    keypad(stdscr, TRUE); // Attiva gli special key
    nodelay(stdscr, TRUE); // getch non blocca
    use_default_colors(); // con -1 si indica la trasparenza ovvero il colore del terminale
    
    if (has_colors()) {
        start_color();
        init_pair(0, COLOR_BLACK, -1);
        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_YELLOW, -1);
        init_pair(4, COLOR_WHITE, -1);
        init_pair(5, COLOR_BLUE, -1);
        init_pair(6, COLOR_CYAN, -1);
        if (can_change_color()) {
            //modifica colori con rgb
            init_color(COLOR_BLACK, 0, 0, 0);
            init_color(DARK_GREEN, 0, 500, 0);
            init_pair(7, DARK_GREEN, -1);
        }
        else {
            // fallback: usa il verde normale se non si può cambiare colore
            init_pair(7, COLOR_GREEN, -1);
        }
    }
    refresh(); // Serve
}


int main() {
    initializeNcurses();
    Game snake;
    snake.run();
}