#include "../include/ranking.h"
#include <iostream>

Ranking::Ranking() : currentPlayer(NULL){}


void Ranking::fixRank() {
    if (ranking.head == NULL || ranking.size <= 1) {
        //inutile ordinare
        return;
    }
    bool swapped;
    utl::Node<SingleRank> *lastSorted = NULL; //ottimizzazione
    do {
        utl::Node<SingleRank> *current = ranking.head;
        swapped = false;
        while (current->next != lastSorted) {
            if (current->value.getBestTotScore() < current->next->value.getBestTotScore()) {
                utl::Node<SingleRank> *big = current->next;
                utl::Node<SingleRank> *min = current;
                // Collego gli adiacenti
                if (min->prev != NULL) {
                    min->prev->next = big;
                } else {
                    ranking.head = big;
                }
                if (big->next != NULL) {
                    big->next->prev = min;
                } else {
                    ranking.tail = min;
                }
                // Completo lo swap
                min->next = big->next;
                big->prev = min->prev;
                big->next = min;
                min->prev = big;
                current = big;
                int bigPos = big->value.getPos();
                int minPos = min->value.getPos();
                big->value.setPos(minPos);
                min->value.setPos(bigPos);
                swapped = true;
            } else {
                current = current->next;
               }
        }
        lastSorted = current;
    } while(swapped);
}

void Ranking::insertPlayer(char* nickname) {
    utl::Node<SingleRank> *p = ranking.head;
    bool toIns = true;
    while (p!=NULL and toIns) {
        if (strcmp(p->value.getNickname(), nickname) == 0) {
            currentPlayer = p;
            toIns = false;
        }
        p = p->next;
    }
    if (toIns) {
        ranking.newNodeAtTheEnd();
        ranking.tail->value.setNickname(nickname);
        ranking.tail->value.setPos(getRankSize());
        ranking.tail->value.setBestTotScore(0);
        currentPlayer = ranking.tail;
    }
}

long updatePlayerScore(utl::Node<SingleLevel> *head){
    long playerScore = 0;
    utl::Node<SingleLevel> *p = head;
    while (p != NULL) {
        playerScore += p->value.stat.bestScore;
        p = p->next;
    }
    return playerScore;
}

void Ranking::updateRank(utl::Node<SingleLevel> *head) {
    currentPlayer -> value.setBestTotScore(updatePlayerScore(head));
    fixRank();
}

void Ranking::loadPlayer(SingleRank elem) {
    ranking.newNodeAtTheEnd();
    ranking.tail->value.setNickname(elem.getNickname());
    ranking.tail->value.setPos(elem.getPos());
    ranking.tail->value.setBestTotScore(elem.getBestTotScore());
}

bool Ranking::playerNotInRank() const {
     return currentPlayer->value.getPos() > MAX_RANK;
}

long Ranking::getPlayerScore() const{
    return currentPlayer->value.getBestTotScore();
}


//ogni volta volta che il gioco termina viene riscritta in caso la classifica
//in base a cio' che e' presente nella lista
void Ranking::writeRankingFile() {
    char filepath[MAX_PATH];
    strcpy(filepath, "../ranking/ranking.txt");
    std::ofstream rankingFile(filepath, std::ios::out | std::ofstream::trunc); //sovrascrive il file precedente

    if (!rankingFile.is_open()) {
        std::cerr << "Impossibile aprire il file";
        return;
    }
    utl::Node<SingleRank> *p = ranking.head;
    while (p != NULL) {
        rankingFile << p->value.getPos();
        rankingFile << ",";
        rankingFile << p->value.getNickname();
        rankingFile << ",";
        rankingFile << p->value.getBestTotScore();
        rankingFile << "\n";
        p = p->next;
    }
}

SingleRank Ranking::getTail() const {
    return ranking.tail->value;
}

utl::Node<SingleRank>* Ranking::getHeadRankPointer() const {
    return ranking.head;
}
utl::Node<SingleRank>* Ranking::getTailRankPointer() const {
    return ranking.tail;
}

void Ranking::buildListFromFile(){
    //pulisco la lista
    utl::Node<SingleRank> *p = ranking.head;
    while (p != NULL) {
        utl::Node<SingleRank> *q = p->next;
        delete p;
        p = q;
    }

    char filepath[MAX_PATH];
    strcpy(filepath, "../ranking/ranking.txt");
    std::ifstream rankingFile(filepath);

    if (!rankingFile.is_open()) {
        std::cerr << "Impossibile aprire il file";
    }

    int pos = 0;
    char commaCheck1 = '\0';
    char nickname [MAX_NICKNAME];
    long bestScore = 0;

    while (rankingFile >> pos) {
        if (rankingFile >> commaCheck1 && commaCheck1 == ',') {
            if (rankingFile.getline(nickname, MAX_NICKNAME, ',')) {
                if (rankingFile >> bestScore) {
                    SingleRank elem = SingleRank(pos, nickname, bestScore);
                    loadPlayer(elem);

                } else {
                    std::cerr << "Errore nel leggere bestScore! Pulisco lo stream. " << std::endl;
                    rankingFile.clear();
                }
            } else {
                std::cerr << "Errore nel leggere nickname! Pulisco lo stream." << std::endl;
                rankingFile.clear();
            }
        } else {
            std::cerr << "Errore la virgola! Pulisco lo stream." << std::endl;
            rankingFile.clear();
        }
        char ch;
        while (rankingFile.get(ch) && ch != '\n'){
            //se per caso ci fossero stati errori in inserimento
            //verrebbero bypassati da questo ciclo che fa arrivare
            //alla fine della linea
        }
    }
}

int Ranking::getRankSize() const{
    return ranking.size;
}