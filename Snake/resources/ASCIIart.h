#ifndef ASCIIART_H
#define ASCIIART_H

#include "../include/utility.h"

//GeneralPrint
void print(const char*[], const int size, int row, int col, utl::colorPair color);

void printGameoverArt();

void printStunnedSnakeArt();

void printSnakeHomeArt();

void printRankingArt();

void printLeafArt();

void printHappySnakeArt();
int getHappySnakeSize();

#endif //ASCIIART_H