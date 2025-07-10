#include "../include/singleLevel.h"
#include <iostream>

Stat::Stat() {
    id = 1;
    timeLimit = 60;
    timePassed = 0.0;
    snakeSpeed = 3;
    currentScore = 0;
    endLevelBonus = 50;
    foodValue = 5;
    bestScore=0;
    alreadyTakeBonus=false;
}

void Stat::computeLevelStats(const int id) {
    this -> id = id;
    int multiplier = id*1.3;  //si può mettere qualcosa di più interressante

    snakeSpeed = 3 + id;
    foodValue = 5*id;
    endLevelBonus = 50 + 25*id;
}

//controllore dopo eventuali future modifiche  !!!
void Stat::resetLevel(){
    currentScore = 0;
    timePassed = 0;
    alreadyTakeBonus = false;
}

SingleLevel::SingleLevel(){
    arena.setWindow();
}

void SingleLevel::setLevelStat(const int prevLevelId) {
    stat.computeLevelStats(prevLevelId+1);
    snake.initializeSnake(stat.snakeSpeed, arena);
    food.setPosition(snake, arena);
    food.setValue(stat.foodValue);
}

//true -> proseguo normale -- false-> è sucesso qualcosa
bool SingleLevel::updateLevelStat(double deltaTime){
    if(stat.alreadyTakeBonus) return false; //il livello è gia stato terminato
    //score
    stat.bestScore = std::max(stat.currentScore, stat.bestScore);

    //updateTime
    stat.timePassed += (deltaTime/1000);
    if(stat.timePassed >= stat.timeLimit){
        stat.timePassed = stat.timeLimit; 
        //endlLevelBonus
        stat.alreadyTakeBonus = true;
        stat.currentScore += stat.endLevelBonus;
        stat.bestScore = std::max(stat.currentScore, stat.bestScore);
        return false;
    }
    return true;
}