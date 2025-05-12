#include "include/game.h"

void initializeNcurse() {
    initscr(); // Inizializza ncurses
    cbreak(); // Disabilita il buffering dell'input
    noecho(); // Non mostra i caratteri digitati
    curs_set(0); // Nasconde il cursore
    keypad(stdscr, TRUE); // Attiva gli special key
    nodelay(stdscr, TRUE); // getch non blocca
    use_default_colors(); // con -1 si indica la trasparenza ovvero il colore del terminale
    if (has_colors()) {
        start_color();
        if (can_change_color()) {
            //modifica colori con rgb
            init_color(COLOR_BLACK, 0, 0, 0);
        }
        init_pair(0, COLOR_RED, COLOR_RED);
        init_pair(1, COLOR_GREEN, -1);
        init_pair(2, COLOR_RED, -1);
        init_pair(3, COLOR_YELLOW, -1);
    }
    refresh(); // Serve
}

int main() {
    initializeNcurse();
    Game snake;
    snake.run();
}
