#include "../include/singleLevel.h"

SingleLevel::SingleLevel() : snake(5, arena), score(0) {
    //snake initialized in the constructor
    arena.setWindow();
    food.setPosition(snake, arena);
}

