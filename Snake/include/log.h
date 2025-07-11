#include <iostream>
#include <fstream>
#ifndef LOG_H
#define LOG_H
#define MAX_PATH 100

class Log {
    public:
        Log();
        void writeLine(char* nickname, int levelId, int levelScore);
        //void deleteLog(char* nickname);
    private:
        bool buildFilePath(char* buffer, char* nickname);
        bool exists(char* nickname);
        std::ofstream create(char* nickname);
        int getLevelScore(char* nickname, int levelId);

};

#endif //LOG_H
