#include "../include/singleLevel.h"
#include <iostream>

Stat::Stat() {
    id = 1;
    timeLimit = 60.0;
    timePassed = 0.0;
    snakeSpeed = 3;
    currentScore = 0;
    endLevelBonus = 100;
    bestScore=0;
    goal=100;
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

//true -> proseguo normale -- false-> è sucesso qualcosa
bool SingleLevel::updateLevelStat(double deltaTime){
    //score
    stat.bestScore = std::max(stat.currentScore, stat.bestScore);

    //updateTime
    stat.timePassed += (deltaTime/1000);
    if(stat.timePassed >= stat.timeLimit){
        //endlLevelBonus
        stat.currentScore += stat.endLevelBonus;
        stat.bestScore = std::max(stat.currentScore, stat.bestScore);
        return false;
    }
    return true;
}