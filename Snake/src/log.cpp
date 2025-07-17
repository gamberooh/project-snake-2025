#include "../include/log.h"
#include <cstring>

Log::Log() {
    filePath[0] = '\0';
}

#define levelStat head->value.stat

void Log::createLog(char* nickname, utl::Node<SingleLevel>* head) {
      while (head != NULL) {
        writeLine(nickname, levelStat.id, levelStat.currentScore, levelStat.bestScore, levelStat.timePassed);
        head = head->next;
    }
}

//prende tutto dal file log e lo carica sui livelli
void Log::loadGame(char* nickname, utl::Node<SingleLevel>* head){
    while(head!=NULL){
        Stat currentStat = getLevelStat(nickname, levelStat.id);
        levelStat.id = currentStat.id;
        levelStat.bestScore = currentStat.bestScore;
        levelStat.currentScore = currentStat.currentScore;
        levelStat.timePassed = currentStat.timePassed;
        head = head->next;
    }
}

void Log::update(char* nickname, utl::Node<SingleLevel>* head){
    //esiste sempre il file, creato/caricato all'avvio
    std::ofstream log(filePath, std::ios::trunc);
    log.close();
    createLog(nickname, head);
}

void Log::buildFilePath(char* nickname) {
    size_t totSize = strlen("../log/")+ strlen(nickname) + strlen(".txt") + 1;
    if (totSize > MAX_PATH)
        return;
    strcpy(filePath, "../log/");
    strncat(filePath, nickname, totSize);
    strncat(filePath, ".txt", totSize);
}

bool Log::exists(char* nickname) {
    if (filePath[0] == '\0')
        return false;
    std::ifstream log(filePath);
    return log.is_open();
}

void Log::writeLine(char* nickname, int levelId, int levelScore, int maxScore, double timePassed) {
    std::ofstream log(filePath, std::ofstream::app); //metodo di scrittura append
    log << levelId;
    log << ",";
    log << levelScore;
    log << ",";
    log << maxScore;
    log << ",";
    log << timePassed;
    log << "\n";
    log.flush();
    log.close();
}

// da log crea statistca livelloa all'id level passato per parametro
Stat Log::getLevelStat(char* nickname, int levelId) {
    std::ifstream log(filePath);

    if (!log.is_open()) {
        std::cerr << "Impossibile aprire il file";
        return Stat();
    }
    //inizializazione
    Stat currentStat;
    int id = 0;
    char commaCheck1 = '\0';
    int score = 0;
    char commaCheck2 = '\0';
    int max = 0;
    char commaCheck3 = '\0';
    double time = 0;

    while (log >> id) {
        if (log >> commaCheck1 && commaCheck1 == ',') {
            if (log >> score) {
                if (log >> commaCheck2 && commaCheck2 == ',') {
                    if (log >> max) {
                        if (log >> commaCheck3 && commaCheck3 == ',') {
                            if (log >> time) {
                                if (id == levelId) {
                                    log.close();
                                    currentStat.id = id;
                                    currentStat.currentScore = score;
                                    currentStat.bestScore = max;
                                    currentStat.timePassed = time;
                                    return currentStat;
                                }
                            } else {
                                log.clear();
                                //std::cerr << "Errore lettura timePassed! Pulizia stream";
                            }
                        } else {
                            log.clear();
                            //std::cerr << "Errore lettura della virgola 3! Pulizia stream";
                        }
                    } else {
                        log.clear();
                        //std::cerr << "Errore lettura maxScore! Pulizia stream";
                    }
                } else {
                    log.clear();
                    //std::cerr << "Errore lettura della virgola 2! Pulizia stream";
                }
            } else {
                log.clear(); //errore nella trascrizione dello score
                //std::cerr << "Errore lettura levelScore! Pulizia stream";
            }
        } else {
            log.clear(); //errore nella trasrcizione della virgola
            //std::cerr << "Errore lettura della virgola 1! Pulizia stream";
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
    return Stat();
}



