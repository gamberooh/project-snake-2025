#ifndef GAME_H
#define GAME_H

#include <ctime>
#include "singleLevel.h"
#include <ncurses.h>
#include "utility.h"

class Game {
    public:
        Game();
        void run();

    private:
        bool isRunning;
        bool openMenu;
        int fps;
        SingleLevel currentLevel;


        void processInput();
        void update(clock_t updateTime);
        void render() const;
};



#endif //GAME_H
