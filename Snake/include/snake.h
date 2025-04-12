#ifndef SNAKE_H
#define SNAKE_H

#include <ctime>
#include "utility.h"
#include "arena.h"

class Snake{
  public:
      Snake(int length, Arena &arena);
      utl::DoubleLinkedListPos body;

      void changeDirection(int x, int y);
      void update(clock_t updateTime, Arena &arena);

  private:
      int characterPerSecond;
      clock_t lastUpdateTime;
      utl::Position direction;
      void moveSnake(Arena &arena);
};


#endif //SNAKE_H
