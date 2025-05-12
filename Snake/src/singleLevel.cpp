#include "../include/singleLevel.h"

Stat::Stat() {
    id = 1;
    timeLimit = 60.0;
    timePassed = 0.0;
    snakeSpeed = 3;
    currentScore = 0;
    endLevelBonus = 100;
}

void Stat::computeLevelStats(const int id) {
    this -> id = id;
    int multiplier = id*2;  //si può mettere qualcosa di più interressante

    snakeSpeed *= multiplier;
    endLevelBonus *= multiplier;
}

SingleLevel::SingleLevel(){
    arena.setWindow();
}

void SingleLevel::setLevelStat(const int prevLevelId) {
    stat.computeLevelStats(prevLevelId+1);
    snake.initializeSnake(stat.snakeSpeed, arena);
    food.setPosition(snake, arena);
}



