#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <ncurses.h>

#include "snake.h"
#include "arena.h"
#include "food.h"
#include "levels.h"

class Game {
    public:
        Game();
        void run();

    private:
        bool isRunning;
        Arena arena;  //non invertire queste due se no da errore perchè arena non è ancora definita e snake ci accede;
        Snake snake;
        Food food;
        Levels levels;

        int fps;
        int score;

        void processInput();
        void update(clock_t updateTime);
        void render() const;
};



#endif //GAME_H
