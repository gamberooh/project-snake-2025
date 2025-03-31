#include "game.h"

Game::Game() : isRunning(true), snake(5, arena), fps(60), score(0){
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
    //snake initialized in the constructor
    arena.setWindow();
    food.setPosition(snake, arena);
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
}

void Game::processInput() {
    switch (getch()) {
        case KEY_UP: case 'w':
            snake.changeDirection(0, -1);
            break;
        case KEY_DOWN: case 's':
            snake.changeDirection(0, 1);
            break;
        case KEY_LEFT: case 'a':
            snake.changeDirection(-1, 0);
            break;
        case KEY_RIGHT: case 'd':
            snake.changeDirection(1, 0);
            break;
        case 'q':
            endwin();
            isRunning = false;
            break;
        case
        default:
            // Handle other key presses
            break;
    }
}

void Game::update(const clock_t updateTime) {
    snake.update(updateTime, arena);
    if(food.update(snake, arena)) score += food.scoreValue;
}

void Game::render() const{
    arena.render(snake.body.head->pos, food.spawnPos, score);
}