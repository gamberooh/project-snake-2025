#include <iostream>
#include <cstddef>
using namespace std;

#ifndef LEVELS_H
#define LEVELS_H

#endif //LEVELS_H

struct stat {
  int id;  //numero del livello
  //tempo
  double timeLimit;
  double time_passed;  // con il tempo passato e la durata totale si riesce a capire lo stato del livello, iniziato, nuovo, finito
  //velocita
  double speed;
  //punti
  int current_score;
  double multiplier;
  int bonus_end_level;
};

struct single_level{
  stat data;
  //puntatori
  single_level* next;
  single_level* back;
};

typedef single_level* plevel;


class Levels{
  protected:
    plevel curr;
    int nlevels;
    stat level_template;

    void pushBack(int id);
    stat newLevelStat(int id) const;

  public:
    Levels();
    void createLevels();
    void print_idLevels();
};

