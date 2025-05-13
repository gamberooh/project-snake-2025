#ifndef SNAKE_H
#define SNAKE_H

#include <ctime>
#include "utility.h"
#include "arena.h"

class Snake{
    public:
        Snake();
        utl::DoubleLinkedListPos body;

        void initializeSnake(int speed, Arena &arena);
        void changeDirection(int x, int y);
        void update(clock_t updateTime, Arena &arena);

    private:
        int characterPerSecond;
        int length;
        clock_t lastUpdateTime;
        utl::Position direction;
        bool enableDirectionChange;

        void moveSnake(Arena &arena);
        void setSpawnPos(Arena &arena);
};


#endif //SNAKE_H
