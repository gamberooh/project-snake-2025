//
// Created by gambe on 27/11/2024.
//

#include <iostream>
#include <fstream>
#include "writeLog.h"
using namespace std;

void writeLog(char player[], unsigned int level, unsigned int score, bool game_over) {
    ofstream writer = fileOut("log.txt");
    if (writer.is_open()) {
        writer << "Player: " << player << "\n";
        writer << "Level: " << level << "\n";
        writer << "Score: " << score << "\n";
        writer << "Game Over: " << game_over << "\n";
        writer.flush();
        writer.close();
        cout << "Scrittura completata!" << endl;
    } else {
         cerr << "Errore nell'apertura del file!" << endl;
    }
}
