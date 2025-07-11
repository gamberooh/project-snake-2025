#ifndef RANKING_H
#define RANKING_H

#include <fstream>
#include <cstring>
#include "utility.h"
#include "singleRank.h"
#include "singleLevel.h"
#include "log.h"
#define MAX_RANK 5
#define MAX_PATH 150


class Ranking {
private:
    utl::DoubleLinkedList<SingleRank> ranking;
    utl::Node<SingleRank>* currentPlayer;
    void loadPlayer(SingleRank elem);
    void fixRank();

public:
    Ranking();
    void updateRank(utl::Node<SingleLevel> *head);
    
    bool playerNotInRank() const;
    long getPlayerScore() const;
    int getRankSize() const;
    SingleRank getTail() const;
    utl::Node<SingleRank>* getHeadRankPointer() const;
    utl::Node<SingleRank>* getTailRankPointer() const;

    //scrittura su file
    void writeRankingFile();
    void insertPlayer(char* nickname);
    void buildListFromFile();
    
};

#endif //RANKING_H