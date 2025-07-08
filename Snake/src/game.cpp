#include "../include/game.h"
#include <cstring>

Game::Game() : isRunning(true), openMenu(false), fps(60) {
    levelList.newNodeAtTheEnd();
    currentLevel = levelList.head;
    currentLevel -> value.setLevelStat(0); //0 perchè il parametro fa rimerifento all'id del livello precedente
    addLevels(50);
}

void Game::addLevels(const int nLevels) {
    utl::Node<SingleLevel>* head = currentLevel;    //all'inizio currentLevel è la testa
    for (int i=1; i<nLevels; i++) {
        levelList.newNodeAtTheEnd();
        head = head -> next;
        head -> value.setLevelStat(i);
    }
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

    while(isRunning) {
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
    int key=getch();
    if(!openMenu) {
        switch (key) {
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
            case 'm':
                openMenu = true;
                break;
            default:
                // Handle other key presses
                break;
        }
    }
    else {
        openMenu = menu.handleInput(key, currentLevel, isRunning);
        if(!isRunning) endwin();
    }
}


void Game::update(const clock_t updateTime) const {
    if (!openMenu) {
        snake.update(updateTime, arena);
        if(food.update(snake,arena)) score += food.scoreValue;
    }
}


void Game::render() const{
    if(!openMenu) {
        arena.render(snake.body.head->value, food.spawnPos, score);
    }
    else {
        menu.renderCurrentPage(currentLevel, levelList.head, levelList.tail); 
    }
}