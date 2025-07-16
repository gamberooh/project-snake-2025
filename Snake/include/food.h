#ifndef FOOD_H
#define FOOD_H

#include "utility.h"
#include "snake.h"
#include "arena.h"

class Food {
    public:
        Food();
        utl::Position spawnPos;
        int scoreValue;

        void setPosition(const Snake &snake, Arena &arena);
        void setValue(const int value);
        bool update(const Snake &snake, Arena &arena);
};

#endif //FOOD_H