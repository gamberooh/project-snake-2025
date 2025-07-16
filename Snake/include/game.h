#ifndef GAME_H
#define GAME_H

#include <ctime>
#include "singleLevel.h"
#include "utility.h"
#include "menu.h"
#include "log.h"

class Game {
    public:
        Game();
        void run();

    private:
        bool isRunning;
        bool openMenu;
        Menu menu;
        const int fps;
        const int nLevels; 
        utl::Node<SingleLevel>* currentLevel;
        utl::DoubleLinkedList<SingleLevel> levelList;
    
        void processInput();
        void update(double updateTime);
        void render() const;
};

#endif //GAME_H
