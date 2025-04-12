#include "../include/game.h"
#include <cstring>

Game::Game() : isRunning(true), fps(60), openMenu(false){
    {
        initscr(); // Inizializza ncurses
        cbreak(); // Disabilita il buffering dell'input
        noecho(); // Non mostra i caratteri digitati
        curs_set(0); // Nasconde il cursore
        keypad(stdscr, TRUE); // Attiva gli special key
        nodelay(stdscr, TRUE); // getch non blocca
        use_default_colors(); // con -1 si indica la trasparenza ovvero il colore del terminale
        if (has_colors()) {
            start_color();
            if(can_change_color()) {  //modifica colori con rgb
                init_color(COLOR_BLACK, 0, 0, 0);
            }
            init_pair(0, COLOR_RED, COLOR_RED);
            init_pair(1, COLOR_GREEN, -1);
            init_pair(2, COLOR_RED, -1);
            init_pair(3, COLOR_YELLOW, -1);
        }
        refresh(); // Serve
    } //initialize ncurse
}

clock_t getElapsedTimeMS(clock_t &start){
    clock_t current = clock();
    clock_t elapsed = (current-start)*1000/CLOCKS_PER_SEC;
    //current-start => quanti tick sono passati dall'ultimo momento
    if(elapsed < 1) {
        return 0;
    }
    start = current;
    return elapsed;
}

void Game::run(){
    clock_t start = clock();
    clock_t updateTime = (1000/fps); // => 1/fps = second_per_frame => *1000 = millisecond_per_frame
    clock_t elapsed = 1000/fps; //esegue il primo frame

    while(isRunning) {   //bisogna mettere un modo per uscire (messo nel processInput)
        processInput();
        elapsed += getElapsedTimeMS(start);
        while(elapsed >= updateTime) {
            update(updateTime);
            elapsed -= updateTime;
        }
        render();
    }

    endwin(); //per sicurezza
}

void Game::processInput() {
    if(!openMenu) {
        switch (getch()) {
            case KEY_UP: case 'w':
                currentLevel.snake.changeDirection(0, -1);
            break;
            case KEY_DOWN: case 's':
                currentLevel.snake.changeDirection(0, 1);
            break;
            case KEY_LEFT: case 'a':
                currentLevel.snake.changeDirection(-1, 0);
            break;
            case KEY_RIGHT: case 'd':
                currentLevel.snake.changeDirection(1, 0);
            break;
            case 'q':
                isRunning = false;
                endwin();
                break;
            case 'm':
                openMenu = true;
                break;
            default:
                // Handle other key presses
                break;
        }
    }
    else {
        switch (getch()) {
            case 'm':
                clear();
                refresh();
                openMenu = false;
                break;
            default:
                break;
        }
    }
}

void Game::update(const clock_t updateTime) {


    if (!openMenu) {
        currentLevel.snake.update(updateTime, currentLevel.arena);
        if(currentLevel.food.update(currentLevel.snake,currentLevel.arena)) currentLevel.score += currentLevel.food.scoreValue;
    }
    else {
        const char str[] = "Menu aperto, da implementare";
        int rows, cols;
        getmaxyx(stdscr, rows, cols);
        cols = cols - (int)strlen(str);
        mvprintw(rows/2, cols/2, "%s", str);
    }

}

void Game::render() const{
    if(!openMenu) {
        currentLevel.arena.render(currentLevel.snake.body.head->value, currentLevel.food.spawnPos, currentLevel.score);
    }
}