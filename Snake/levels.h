#include <iostream>
#include <cstddef>
using namespace std;

#ifndef LEVELS_H
#define LEVELS_H

#endif //LEVELS_H

struct single_level{
  //numero del livello
  int id_level;
  //tempo
  double time_limit;
  double time_passed;  // con il tempo passato e la durata totale si riesce a capire lo stato del livello, iniziato, nuovo, finito
  //velocita
  double speed;
  //punti
  int current_score;
  double multiplier;
  int bonus_end_level;
  //puntatori
  single_level* next;
  single_level* back;
};
typedef single_level* plevel;

class Levels{
  protected:
    plevel head;
    int nlevels;
    void init();
    plevel push_back(plevel nLev, int id_level, double time_limit, double time_passed, double speed, int current_score, double multiplier, int bonus_end_level);
    single_level level_template;
  public:
    Levels();
    void create_levels();
    void print_id_levels();
};

