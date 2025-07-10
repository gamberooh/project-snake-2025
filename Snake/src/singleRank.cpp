#include "../include/singleRank.h"

SingleRank::SingleRank(): pos(0), bestTotScore(0) {
    nickname[0] = '\0';
}

SingleRank::SingleRank(int pos, char* nickname, long bestTotScore): pos(pos), bestTotScore(bestTotScore) {
    strncpy(this->nickname, nickname, MAX_NICKNAME-1);
    this->nickname[MAX_NICKNAME-1] = '\0';
}

int SingleRank::getPos(){
    return pos;
}

void SingleRank::setPos(int pos) {
    this->pos = pos;
}

char* SingleRank::getNickname(){
    return nickname;
}

void SingleRank::setNickname(char* nickname) {
    strcpy(this->nickname, nickname);
}

long SingleRank::getBestTotScore() {
    return bestTotScore;
}

void SingleRank::setBestTotScore(long bestTotScore) {
    this->bestTotScore = bestTotScore;
}

