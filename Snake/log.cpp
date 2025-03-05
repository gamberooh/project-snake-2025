#include "log.h"
using namespace std;

Log::Log(){}
Log::Log(char * nickname, plevel levels){
  strcpy(this->nickname, nickname);
  this->levels = levels;
}

void Log::setNickname(char * nickname) {
  strcpy(this->nickname, nickname);
}

char * Log::getNickname(){
  return nickname;
}

void Log::setLevels(plevel levels) {
  this->levels = levels;
}

plevel Log::getLevels () {
  return levels;
}

long Log::getTotalScore() {
  long tot = 0;
  plevel p = levels;
  while (p->next != NULL) {
	tot += p->score;
        p = p->next;
  }
  return tot;
}

//storico: problema id come lo salvo
// prende il num slot partita da un button?

void Log::writeLog(int match_slot) {
	char * fileName;
    strcpy(fileName, nickname);	//nickname deve essere univoco
    strcat(fileName, "_");
    char * buffer;
    sprintf (buffer, "%d", match_slot);
    strcat(fileName, buffer);
    strcat(fileName, ".csv");
    std::ofstream writer(fileName);
    if (writer) {
        writer << "Player,LevelId,Score";
        char * line;
        strcpy(line, nickname);
        strcat(line, ",");
        strcat(line, levels->id);
        strcat(line, ",");
        strcat(line, levels->score); //ci sono modi per gestgire il parsing
		writer << line;
        writer.flush();
        writer.close();
        cout << "Scrittura completata!" << endl;
    } else {
         cerr << "Errore nell'apertura del file!" << endl;
    }
}
