#ifndef SINGLELEVEL_H
#define SINGLELEVEL_H

#include "snake.h"
#include "arena.h"
#include "food.h"

struct Stat {
    int id;  //numero del livello
    //tempo
    double timeLimit;
    double timePassed;
    //velocità
    int snakeSpeed;
    //punti
    int currentScore;
    int endLevelBonus;
    int foodValue;
    bool alreadyTakeBonus;
    int bestScore;

    Stat();
    void computeLevelStats(const int id);
    void resetLevel();
};

class SingleLevel {
    public:
        SingleLevel();
        Arena arena;
        Snake snake;
        Food food;
        Stat stat;

        void setLevelStat(int levelId);
        bool updateLevelStat(double deltaTime);
};


#endif //SINGLELEVEL_H
