// #include "../include/log.h"
// #include <cstring>

// Log::Log(){}

// #define levelStat head->value.stat

// void Log::loadGame(char* nickname, utl::Node<SingleLevel>* head){
//     while(head!=NULL){
//         levelStat.bestScore = getLevelScore(nickname, levelStat.id);
//     }
// }

// //ausilarie
// void Log::swapPath(char* originalPath, char* tempPath) {
//     if (std::remove(originalPath) != 0) {
//         std::cerr << "Impossibile elimiminare il file originale!";
//     }

//     if (std::rename(tempPath, originalPath) !=0) {
//         std::cerr << "Impossibile rinominare il file temporaneo";
//     }
// }

// bool Log::buildFilePath(char* buffer, char* nickname) {
//     size_t totSize = strlen("../log/")+ strlen(nickname) + strlen(".txt") + 1;
//     if (totSize > MAX_PATH) {
//         return false;
//     }
//     buffer[0] = '\0';
//     strcpy(buffer, "../log/");
//     strncat(buffer, nickname, totSize);
//     strncat(buffer, ".txt", totSize);
//     return true;
// }

// bool Log::exists(char* nickname) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         return false;
//     }
//     std::ifstream log(filepath);
//     return log.is_open();
// }

// void Log::writeLine(char* nickname, int levelId, int levelScore, int maxScore, double timePassed) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return;
//     }
//     std::ofstream log(filepath, std::ofstream::app); //metodo di scrittura append
//     log << levelId;
//     log << ",";
//     log << levelScore;
//     log << ",";
//     log << maxScore;
//     log << ",";
//     log << timePassed;
//     log << "\n";
// }

// void Log::updateLine(char* nickname, int levelId, int levelScore, int maxScore, double timePassed) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return;
//     }
//     std::ifstream log(filepath);

//     if (!log.is_open()) {
//         std::cerr << "Impossibile aprire il file";
//         return;
//     }

//     char tmpath[MAX_PATH];
//     strcpy(tmpath, filepath);
//     strcat(tmpath, ".tmp");
//     if (strlen(tmpath) > MAX_PATH) {
//         std::cerr << "Percorso file temporaneo oltre il massimo presabilito!";
//         return;
//     }

//     std::ofstream tempLog(tmpath, std::ios::out);

//     if (!tempLog.is_open()) {
//         std::cerr << "Impossibile aprire il file temporaneo!";
//         return;
//     }

//     //non trovato il livello
//     log.close();
//     tempLog.close();
//     swapPath(filepath, tmpath);
// }

// int Log::getLevelScore(char* nickname, int levelId) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return -1;
//     }
//     std::ifstream log(filepath);

//     if (!log.is_open()) {
//         std::cerr << "Impossibile aprire il file";
//         return -1;
//     }

//     //inizializazione
//     int id = 0;
//     char commaCheck1 = '\0';
//     int score = 0;
//     char commaCheck2 = '\0';
//     char commaCheck3 = '\0';
//     int max = 0;
//     double time = 0;

//     while (log >> id) {
//         if (log >> commaCheck1 && commaCheck1 == ',') {
//             if (log >> score) {
//                 if (id == levelId) {
//                     log.close();
//                     return score;
//                 }
//                 if (log >> commaCheck2 && commaCheck2 == ',') {
//                     if (log >> max) {
//                         if (log >> commaCheck3 && commaCheck3 == ',') {
//                             if (log >> time) {
//                                 //devo semplicemente controllare che con ci siano errrori, non devo fare nient'altro
//                             } else {
//                                 log.clear();
//                                 std::cerr << "Errore lettura timePassed! Pulizia stream";
//                             }
//                         } else {
//                             log.clear();
//                             std::cerr << "Errore lettura della virgola 3! Pulizia stream";
//                         }
//                     } else {
//                         log.clear();
//                         std::cerr << "Errore lettura maxScore! Pulizia stream";
//                     }
//                 } else {
//                     log.clear();
//                     std::cerr << "Errore lettura della virgola 2! Pulizia stream";
//                 }
//             } else {
//                 log.clear(); //errore nella trascrizione dello score
//                 std::cerr << "Errore lettura levelScore! Pulizia stream";
//             }
//         } else {
//             log.clear(); //errore nella trasrcizione della virgola
//             std::cerr << "Errore lettura della virgola 1! Pulizia stream";
//         }

//         char ch;
//         while (log.get(ch) && ch != '\n'){
//             //se per caso ci fossero stati errori in inserimento
//             //verrebbero bypassati da questo ciclo che fa arrivare
//             //alla fine della linea
//         }
//     }
//     //non trovato il livello
//     log.close();
//     return -1;
// }

// int Log::getMaxScore(char* nickname, int levelId) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return -1;
//     }
//     std::ifstream log(filepath);

//     if (!log.is_open()) {
//         std::cerr << "Impossibile aprire il file";
//         return -1;
//     }

//     //inizializazione
//     int id = 0;
//     char commaCheck1 = '\0';
//     int score = 0;
//     char commaCheck2 = '\0';
//     int max = 0;
//     char commaCheck3 = '\0';
//     double time = 0;

//     while (log >> id) {
//         if (log >> commaCheck1 && commaCheck1 == ',') {
//             if (log >> score) {
//                 if (log >> commaCheck2 && commaCheck2 == ',') {
//                     if (log >> max) {
//                         if (id == levelId) {
//                             log.close();
//                             return max;
//                         }
//                         if (log >> commaCheck3 && commaCheck3 == ',') {
//                             if (log >> time) {
//                                 //devo semplicemente controllare che con ci siano errrori, non devo fare nient'altro
//                             } else {
//                                 log.clear();
//                                 std::cerr << "Errore lettura timePassed! Pulizia stream";
//                             }
//                         } else {
//                             log.clear();
//                             std::cerr << "Errore lettura della virgola 3! Pulizia stream";
//                         }
//                     } else {
//                         log.clear();
//                         std::cerr << "Errore lettura maxScore! Pulizia stream";
//                     }
//                 } else {
//                     log.clear();
//                     std::cerr << "Errore lettura della virgola 2! Pulizia stream";
//                 }
//             } else {
//                 log.clear(); //errore nella trascrizione dello score
//                 std::cerr << "Errore lettura levelScore! Pulizia stream";
//             }
//         } else {
//             log.clear(); //errore nella trasrcizione della virgola
//             std::cerr << "Errore lettura della virgola 1! Pulizia stream";
//         }

//         char ch;
//         while (log.get(ch) && ch != '\n'){
//             //se per caso ci fossero stati errori in inserimento
//             //verrebbero bypassati da questo ciclo che fa arrivare
//             //alla fine della linea
//         }
//     }
//     //non trovato il livello
//     log.close();
//     return -1;

// }

// double Log::getTimePassed(char* nickname, int levelId) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return -1;
//     }
//     std::ifstream log(filepath);

//     if (!log.is_open()) {
//         std::cerr << "Impossibile aprire il file";
//         return -1;
//     }

//     //inizializazione
//     int id = 0;
//     char commaCheck1 = '\0';
//     int score = 0;
//     char commaCheck2 = '\0';
//     int max = 0;
//     char commaCheck3 = '\0';
//     double time = 0;

//     while (log >> id) {
//         if (log >> commaCheck1 && commaCheck1 == ',') {
//             if (log >> score) {
//                 if (log >> commaCheck2 && commaCheck2 == ',') {
//                     if (log >> max) {
//                         if (log >> commaCheck3 && commaCheck3 == ',') {
//                             if (log >> time) {
//                                 if (id == levelId) {
//                                     log.close();
//                                     return time;
//                                 }
//                             } else {
//                                 log.clear();
//                                 std::cerr << "Errore lettura timePassed! Pulizia stream";
//                             }
//                         } else {
//                             log.clear();
//                             std::cerr << "Errore lettura della virgola 3! Pulizia stream";
//                         }
//                     } else {
//                         log.clear();
//                         std::cerr << "Errore lettura maxScore! Pulizia stream";
//                     }
//                 } else {
//                     log.clear();
//                     std::cerr << "Errore lettura della virgola 2! Pulizia stream";
//                 }
//             } else {
//                 log.clear(); //errore nella trascrizione dello score
//                 std::cerr << "Errore lettura levelScore! Pulizia stream";
//             }
//         } else {
//             log.clear(); //errore nella trasrcizione della virgola
//             std::cerr << "Errore lettura della virgola 1! Pulizia stream";
//         }

//         char ch;
//         while (log.get(ch) && ch != '\n'){
//             //se per caso ci fossero stati errori in inserimento
//             //verrebbero bypassati da questo ciclo che fa arrivare
//             //alla fine della linea
//         }
//     }
//     //non trovato il livello
//     log.close();
//     return -1.00;
// }

// void Log::deleteLog(char* nickname) {
//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return;
//     }
//     std::remove(filepath);

//     char filepath[MAX_PATH];
//     if (!buildFilePath(filepath, nickname)) {
//         std::cerr << "Percorso file oltre il massimo presabilito!";
//         return;
//     }
//     std::ifstream log(filepath);

//     if (!log.is_open()) {
//         std::cerr << "Impossibile aprire il file";
//         return;
//     }

//     //inizializazione
//     int id = 0;
//     char characterCheck = '\0';
//     int score = 0;

//     while (log >> id) {
//         if (log >> characterCheck && characterCheck == ',') {
//             if (log >> score) {
//                 if (id == levelId) {
//                     log.close();
//                     return score;
//                 }
//             } else {
//                 log.clear(); //errore nella trascrizione dello score
//             }
//         } else {
//             log.clear(); //errore nella trasrcizione della virgola
//         }
//         char ch;
//         while (log.get(ch) && ch != '\n'){
//             //se per caso ci fossero stati errori in inserimento
//             //verrebbero bypassati da questo ciclo che fa arrivare
//             //alla fine della linea
//         }
//     }
//     //non trovato il livello
//     log.close();
//     return;
// }



