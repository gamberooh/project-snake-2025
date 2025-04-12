#include "../include/snake.h"
#include <cstdlib>
#include <ctime>

Snake::Snake(const int length, Arena &arena) : characterPerSecond(7), lastUpdateTime(0), direction(0, 0){
    //da rivedere il punto di spawn
    srand(time(NULL));

    int spawnX = rand() % (arena.width/2) + arena.width/4;
    int spawnY = rand() % (arena.height/2) + arena.height/4;

    for(int i = 0; i < length; i++) {
        body.insert(spawnX - i, spawnY);
        arena.arena[spawnY][spawnX-i] = true;
    }
}


void Snake::changeDirection(int x, int y) {
    // verso destra = 1 0 => verso sinistra = -1 0 quindi se la somma è zero non posso andarci
    // all'inizio direction = 0 quindi fermo fin che non si preme un tasto
    if((direction.x + x)!=0) direction.x = x;
    if((direction.y + y)!=0) direction.y = y;
}

void Snake::update(clock_t updateTime, Arena &arena) {
    lastUpdateTime += updateTime;
    if(lastUpdateTime >= (1000/characterPerSecond)) {
        moveSnake(arena);
        lastUpdateTime = 0;
    }
}

utl::Position boundCheckUpdate(utl::Position pos, const int width, const int height) {
    if(pos.x < 0) pos.x = width-1;
    if(pos.x >= width) pos.x = 0;
    if(pos.y < 0) pos.y = height-1;
    if(pos.y >= height) pos.y = 0;
    return pos;
}

void Snake::moveSnake(Arena &arena) {
    utl::Position newpos;
    newpos.x = direction.x;
    newpos.y = direction.y;
    newpos.add(body.head->value);
    newpos = boundCheckUpdate(newpos, arena.width, arena.height);

    //check self collision
    if(body.isMember(newpos)) return;

    arena.arena[body.tail->value.y][body.tail->value.x] = false;
    body.moveLastFront();
    body.head->value = newpos;
    arena.arena[body.head->value.y][body.head->value.x] = true;
}



