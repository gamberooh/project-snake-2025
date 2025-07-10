#include "../include/log.h"
#include <cstring>

Log::Log(){}


bool Log::buildFilePath(char* buffer, char* nickname) {
    size_t totSize = strlen("../log/")+ strlen(nickname) + strlen(".txt") + 1;
    if (totSize > MAX_PATH) {
        return false;
    }
    buffer[0] = '\0';
    strcpy(buffer, "../log/");
    strncat(buffer, nickname, totSize);
    strncat(buffer, ".txt", totSize);
    return true;
}

bool Log::exists(char* nickname) {
    char filepath[MAX_PATH];
    if (!buildFilePath(filepath, nickname)) {
        return false;
    }
    std::ifstream log(filepath);
    return log.is_open();
}

void Log::writeLine(char* nickname, int levelId, int levelScore) {
    char filepath[MAX_PATH];
    if (!buildFilePath(filepath, nickname)) {
        std::cerr << "Percorso file oltre il massimo presabilito!";
        return;
    }
    std::ofstream log(filepath, std::ofstream::app); //metodo di scrittura append
    log << levelId;
    log << ",";
    log << levelScore;
    log << "\n";
}

int Log::getLevelScore(char* nickname, int levelId) {
    char filepath[MAX_PATH];
    if (!buildFilePath(filepath, nickname)) {
        std::cerr << "Percorso file oltre il massimo presabilito!";
        return -1;
    }
    std::ifstream log(filepath);

    if (!log.is_open()) {
        std::cerr << "Impossibile aprire il file";
        return -1;
    }

    //inizializazione
    int id = 0;
    char characterCheck = '\0';
    int score = 0;

    while (log >> id) {
        if (log >> characterCheck && characterCheck == ',') {
            if (log >> score) {
                if (id == levelId) {
                    log.close();
                    return score;
                }
            } else {
                log.clear(); //errore nella trascrizione dello score
            }
        } else {
            log.clear(); //errore nella trasrcizione della virgola
        }
        char ch;
        while (log.get(ch) && ch != '\n'){
            //se per caso ci fossero stati errori in inserimento
            //verrebbero bypassati da questo ciclo che fa arrivare
            //alla fine della linea
        }
    }
    //non trovato il livello
    log.close();
    return -1;
}


