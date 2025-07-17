#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include "utility.h"
#include "singleLevel.h"

#define MAX_PATH 150

class Log {

    private:
        char filePath[MAX_PATH];
        void writeLine(char* nickname, int levelId, int levelScore, int maxScore, double timePassed);
        Stat getLevelStat(char* nickname, int levelId);

    public:
        Log();
        void loadGame(char* nickname, utl::Node<SingleLevel>* head);
        void buildFilePath(char* nickname);
        void createLog(char*nickname, utl::Node<SingleLevel>* head);
        bool exists(char* nickname);
        void update(char* nickname, utl::Node<SingleLevel>* head);
};
#endif //LOG_H