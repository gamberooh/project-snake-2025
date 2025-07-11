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
        Stat getStat(const int levelId, char* nickname);
        void swapPath(char* originalPath, char* tempPath);
        std::ofstream create(char* nickname);
        void writeLine(char* nickname, int levelId, int levelScore, int maxScore, double timePassed);
        void deleteLog(char* nickname);
        int getLevelScore(char* nickname, int levelId);
        // int getMaxScore(char* nickname, int levelId);
        //double getTimePassed(char* nickname, int levelId);

    public:
        Log();
        void loadGame(char* nickname, utl::Node<SingleLevel>* head);
        void buildFilePath(char* nickname);
        void createGame(char* nickname, utl::Node<SingleLevel>* head);
        Stat getLevelStat(char* nickname, int levelId);
        void createLog(char*nickname, utl::Node<SingleLevel>* head);
        /*
            #define levelStat head->value.stat

            chiamata loadGame(char *nickname, utl::Node<SingleLevel>* head) -> c'è un log
            Stat currentStat;
            for(int i=1; i<=50; i++){
                currentStat = getLevelStat(i, nickname);
                levelStat.score = currentStat.score;
                levelStat.bestSCore = currentStat.bestScore;
                levelStat.timePassed = currentStat.timePassed;
            }
                               
        */


        /* menu.cpp -> setupGAme();
            if(log.exist(nickname)
                loadGame(...)
            else
                createLog(utl::Node<SingleLevel> head)        
        */

        /*
            #define levelStat head->value.stat

            createGame(char* nickname, utl::Node<SingleLevel>* head);{
                while(head != NULL){
                    writeLevel(nickname, levelStat.id, ...)
                }
            }
        */

        /* game.cpp -> handleInput/update (dove c'è update rank dovrebbero essere 4 volte in cui compare)
            -> quando si apre il menu per qualasi ragione
            //nuova funzione in menu + log come attributo privato

            #define currentLevel currentLevel->value.stat

            menu.updateLog(utl::Node<SingleLevel>* currentLevel){
                log.updateLine(nickname, currentLevel.id, current. ....)
            }
        */

        void updateLine(char* nickname, int levelId, int levelScore, int maxScore, double timePassed);
        bool exists(char* nickname);
};
#endif //LOG_H
