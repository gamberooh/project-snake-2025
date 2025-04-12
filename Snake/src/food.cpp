#include "../include/food.h"
#include <cstdlib>
#include <ctime>


Food::Food() : scoreValue(10), spawnPos(0, 0) {}

void Food::setPosition(const Snake &snake, Arena &arena) {

    do {
        spawnPos.x = rand()%arena.width;
        spawnPos.y = rand()%arena.height;
    }while(snake.body.isMember(spawnPos));

    arena.arena[spawnPos.y][spawnPos.x] = true;
}

bool Food::update(const Snake &snake, Arena &arena) {
    if(snake.body.head->value == spawnPos) {
        setPosition(snake, arena);
        return true;
    }
    return false;
}
