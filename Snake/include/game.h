#ifndef GAME_H
#define GAME_H

#include <ctime>
#include "singleLevel.h"
#include "utility.h"

class Game {
    public:
        Game();
        void run();

    private:
        bool isRunning;
        bool openMenu;
        int fps;
        utl::Node<SingleLevel>* currentLevel;
        utl::DoubleLinkedList<SingleLevel> levelList;

        void processInput();
        void update(clock_t updateTime) const;
        void render() const;
};



#endif //GAME_H
