#ifndef SNAKE_H
#define SNAKE_H

#include "utility.h"
#include "arena.h"

class Snake{
    public:
        Snake();
        utl::DoubleLinkedListPos body;
        bool firstMovement;

        void initializeSnake(int speed, Arena &arena);
        void changeDirection(int x, int y);
        bool update(double updateTime, Arena &arena);

    private:
        int characterPerSecond;
        int length;
        double lastUpdateTime;
        utl::Position direction;
        bool enableDirectionChange;

        bool moveSnake(Arena &arena);
        void setSpawnPos(Arena &arena);
};


#endif //SNAKE_H
