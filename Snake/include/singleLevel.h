#ifndef SINGLELEVEL_H
#define SINGLELEVEL_H

#include "levels.h"

#include "snake.h"
#include "arena.h"
#include "food.h"

class SingleLevel //: public Levels  //si potrebbe aggiungere
{
public:
    SingleLevel();

    Arena arena;  //non invertire queste due se no da errore perchè arena non è ancora definita e snake ci accede;
    Snake snake;
    Food food;
    int score;
};


#endif //SINGLELEVEL_H
