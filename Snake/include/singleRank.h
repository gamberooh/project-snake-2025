
#ifndef SINGLERANK_H
#define SINGLERANK_H

#define MAX_NICKNAME 100

#include <iostream>
#include <cstring>

class SingleRank {
    private:
        int pos;
        char nickname[MAX_NICKNAME];
        long bestTotScore;
    public:
        SingleRank();
        SingleRank(int pos, char* nickname, long bestTotScore);

        int getPos();
        void setPos(int pos);

        char* getNickname();
        void setNickname(char* nickname);

        long getBestTotScore();
        void setBestTotScore(long bestTotScore);
};

#endif //SINGLERANK_H
