#include <iostream>
#include <fstream>
#include <cstring>
//#include "utility.h"

#ifndef WRITELOG_H
#define WRITELOG_H

#endif //WRITELOG_H

// struttura che poi verra sostituita da levels di mattia

struct DoubleLinkedLevel {
  DoubleLinkedLevel* before;
  int id; //numero livello
  int score;
  bool completo; //esempio
  DoubleLinkedLevel* next;
};

typedef DoubleLinkedLevel * plevel;

class Log {
  private:
    char * nickname;
    plevel levels;

  public:
    Log();
    Log(char * nickname, plevel levels);

    void setNickname(char * nickname) ;
    char * getNickname();

    void setLevels(plevel levels) ;
    plevel getLevels () ;


    long getTotalScore() ;

    void writeLog(int slot_partita);
     //getLastLog();
};



