#include "../include/game.h"
#include <cstring>

Game::Game() : isRunning(true), openMenu(false), fps(60) {
    levelList.newNodeAtTheEnd();
    currentLevel = levelList.head;
    currentLevel -> value.setLevelStat(0); //0 perchè il parametro fa rimerifento all'id del livello precedente
}

clock_t getElapsedTimeMS(clock_t &start){
    const clock_t current = clock();
    const clock_t elapsed = (current-start)*1000/CLOCKS_PER_SEC;
    //current-start => quanti tick sono passati dall'ultimo momento
    if(elapsed < 1) {
        return 0;
    }
    start = current;
    return elapsed;
}

void Game::run(){
    clock_t start = clock();
    const clock_t updateTime = (1000/fps); // => 1/fps = second_per_frame => *1000 = millisecond_per_frame
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

#define snake currentLevel->value.snake
#define arena currentLevel->value.arena
#define food currentLevel->value.food
#define score currentLevel -> value.stat.currentScore


void Game::processInput() {
    if(!openMenu) {
        switch (getch()) {
            case KEY_UP: case 'w':
                snake.changeDirection(0, -1);
                // snake.changeDirection(0, -1);
            break;
            case KEY_DOWN: case 's':
                snake.changeDirection(0, 1);
                // snake.changeDirection(0, 1);
            break;
            case KEY_LEFT: case 'a':
                snake.changeDirection(-1, 0);
                // snake.changeDirection(-1, 0);
            break;
            case KEY_RIGHT: case 'd':
                snake.changeDirection(1, 0);
                // snake.changeDirection(1, 0);

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
                openMenu = false;
                break;
            case KEY_RIGHT:
                if(currentLevel->next != NULL) currentLevel = currentLevel->next;
            case KEY_LEFT:
                if(currentLevel->prev != NULL) currentLevel = currentLevel->prev;
            default:
                break;
        }
    }
}

void Game::update(const clock_t updateTime) const {
    if (!openMenu) {
        snake.update(updateTime, arena);
        if(food.update(snake,arena)) score += food.scoreValue;
    }
    else {

    }

}

void printTestMenu() {
    const char *str[6] ={
        R"(                  _        )",
        R"(                 | |       )",
        R"(  ___ _ __   __ _| | _____ )",
        R"( / __| '_ \ / _` | |/ / _ \)",
        R"( \__ \ | | | (_| |   <  __/)",
        R"( |___/_| |_|\__,_|_|\_\___|)",
       };
    //R serve per raw string non interpreta le sequenze di escape
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    rows -= 6;
    cols -= (int)strlen(str[0]);
    for(int i = 0; i < 6; i++) {
        mvprintw(rows/2+i, cols/2, "%s", str[i]);
    }
}

void Game::render() const{
    if(!openMenu) {
        arena.render(snake.body.head->value, food.spawnPos, score);
    }
    else {
        erase();
        printTestMenu();
    }
}