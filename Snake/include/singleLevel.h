#ifndef SINGLELEVEL_H
#define SINGLELEVEL_H

#include "snake.h"
#include "arena.h"
#include "food.h"

struct Stat {
    int id;  //numero del livello
    //tempo
    double timeLimit;
    double timePassed;  // con il tempo passato e la durata totale si riesce a capire lo stato del livello, iniziato, nuovo, finito
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
        Arena arena;  //non invertire queste due se no da errore perchè arena non è ancora definita e snake ci accede;
        Snake snake;
        Food food;
        Stat stat;

        void setLevelStat(int levelId);
        bool updateLevelStat(double deltaTime);
        //più i metodi che vorrai implementare
};


#endif //SINGLELEVEL_H
