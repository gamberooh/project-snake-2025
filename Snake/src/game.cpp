#include "../include/game.h"
#include <cstring>
#include <iostream>

Game::Game() : isRunning(true), openMenu(true), fps(60), nLevels(50) {
    levelList.newNodeAtTheEnd();
    currentLevel = levelList.head;
    currentLevel -> value.setLevelStat(0); //0 perchè il parametro fa rimerifento all'id del livello precedente
    //add levels
    {
        utl::Node<SingleLevel>* head = currentLevel;    //all'inizio currentLevel è la testa
        for (int i=1; i<nLevels; i++) {
            levelList.newNodeAtTheEnd();
            head = head -> next;
            head -> value.setLevelStat(i);
        }
    }
}

double getElapsedTimeMS(clock_t &start){
    const clock_t current = clock();
    const double elapsed = (current-start)*1000/CLOCKS_PER_SEC;
    //current-start => quanti tick sono passati dall'ultimo momento
    if(elapsed < 1) {
        return 0;
    }
    start = current;
    return elapsed;
}

void Game::run(){
    clock_t start = clock();
    const double updateTime = (1000/fps); // => 1/fps = second_per_frame => *1000 = millisecond_per_frame
    double elapsed = 1000/fps; //esegue il primo frame

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
#define levelStat currentLevel -> value.stat


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
                menu.updateRank(levelList.head);
                break;
            case 'l':
                openMenu = true;
                menu.updateRank(levelList.head);
                menu.setLevelPage();
            case KEY_RESIZE:
                if(!openMenu) arena.fixPos();
            default:
                // Handle other key presses
                break;
        }
    }
    else {
        openMenu = menu.handleInput(key, currentLevel, isRunning);
        if(!openMenu) arena.fixPos(); //se si chiude il menu e si torna al gioco, si deve sistemare la posizione dell'arena per sicurezza
        if(!isRunning) endwin();
    }
}


void Game::update(const double updateTime) {
    if (!openMenu) {
        //gameOver
        if(!snake.firstMovement) return; //se non si è ancora mosso il serpente stoppo la funzione
        if(!snake.update(updateTime, arena)){ // = a lo snake si è mangiato con se stesso
            openMenu = true;
            menu.updateRank(levelList.head);
            menu.setGameoverPage();
            //altre cose game over
        };  
        //check if food has been eaten
        if(food.update(snake,arena)) levelStat.currentScore += food.scoreValue;
        //end level
        if(!currentLevel->value.updateLevelStat(updateTime)){
            openMenu = true;
            menu.updateRank(levelList.head);
            menu.setLevelPage();
            //altre cose di fine livello
        }
    }//updateLevel();
}


void Game::render() const{
    if(!openMenu) {
        arena.render(snake.body.head->value, food.spawnPos, levelStat.currentScore, (levelStat.timeLimit-levelStat.timePassed));
    }
    else {
        menu.renderCurrentPage(currentLevel, levelList.head, levelList.tail); 
    }
}