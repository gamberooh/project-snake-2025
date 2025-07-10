#ifndef ASCIIART_H
#define ASCIIART_H

#include "../include/utility.h"

//GeneralPrint
void print(const char*[], const int size, int row, int col, utl::colorPair color);

void printGameoverArt();

void printStunnedSnakeArt();

void printSnakeHomeArt();
int getHomeSnakeSize();

void printRankingArt();

void printLeavesArt();

void printHappySnakeArt();
int getHappySnakeSize();

void printVineArt();

#endif //ASCIIART_H