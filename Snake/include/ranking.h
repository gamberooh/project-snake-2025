#ifndef RANKING_H
#define RANKING_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "utility.h"
#include "singleRank.h"
#include "log.h"
#define MAX_RANK 10


class Ranking {
private:
    utl::DoubleLinkedList<SingleRank> ranking;
    void fixRank();

public:
    Ranking();
    //gestione della struttura dati
    void insert(SingleRank elem);
    void writeRankingFile();    
    SingleRank getRankElem (int searchPos) const;

    void buildListFromFile();
    int getRankSize() const;

    //Funzioni Test 
    void createDummyRankingFile(const char* filename);
};

#endif //RANKING_H
