#ifndef RANKING_H
#define RANKING_H

#include <fstream>
#include <cstring>
#include "utility.h"
#include "singleRank.h"
#include "singleLevel.h"
#include "log.h"
#define MAX_RANK 5


class Ranking {
private:
    utl::DoubleLinkedList<SingleRank> ranking;
    utl::Node<SingleRank>* currentPlayer;
    void loadPlayer(SingleRank elem);
    void fixRank();

public:
    Ranking();
    //gestione della struttura dati
    void updateRank(utl::Node<SingleLevel> *head);
    void writeRankingFile();

    bool playerNotInRank() const;
    SingleRank getTail() const;

    utl::Node<SingleRank>* getHeadRankPointer() const;
    utl::Node<SingleRank>* getTailRankPointer() const;

    void insertPlayer(char* nickname);

    void buildListFromFile();
    int getRankSize() const;
};

#endif //RANKING_H