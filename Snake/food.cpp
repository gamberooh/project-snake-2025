#include "food.h"
#include <cstdlib>
#include <ctime>


Food::Food() : scoreValue(10) {}

void Food::setPosition(const Snake &snake, Arena &arena) {

    do {
        spawnPos.x = rand()%arena.width;
        spawnPos.y = rand()%arena.height;
    }while(snake.body.isMember(spawnPos));

    arena.arena[spawnPos.y][spawnPos.x] = true;
}

bool Food::update(const Snake &snake, Arena &arena) {
    if(snake.body.head->pos.x == spawnPos.x && snake.body.head->pos.y == spawnPos.y) {
        setPosition(snake, arena);
        return true;

    }
    return false;
}
