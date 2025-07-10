//
// Created by gamberooh on 25/02/25.
//

#include "../include/ranking.h"

void Ranking::fixRank() {

    if (ranking.tail == NULL || ranking.tail->prev == NULL) {
        if (ranking.head !=  NULL) {
            ranking.head->value.setPos(1);
        }
        return;
     }

    utl::Node<SingleRank> *current = ranking.tail;
    //devo controllare sempre current->prev per come ho strutturato
    //l'inserimento al contrario in insert
    while (current != NULL && current->prev !=NULL && current->value.getBestTotScore() > current->prev->value.getBestTotScore()) {
        utl::Node<SingleRank> *prev = current->prev;
        //salvo gli adiacenti
        utl::Node<SingleRank> *nextOfCurrent = current->next;
        utl::Node<SingleRank> *prevOfPrev = prev->prev;

        //collego invertendo i nodi da intercambiare
        current->next = prev;
        prev->prev = current;

        //ripristino l'ordine della lista
        current->prev = prevOfPrev;
        if (prevOfPrev != NULL) {
            prevOfPrev->next = current;
        } else {
            ranking.head = current;
        }

        prev->next = nextOfCurrent;
        if (nextOfCurrent != NULL) {
            nextOfCurrent->prev = prev;
        } else {
            ranking.tail = prev;
        }

        int oldCurrPos = current->value.getPos();
        int oldPrevPos = prev->value.getPos();

        current->value.setPos(oldPrevPos);
        prev->value.setPos(oldCurrPos);
    }
}

Ranking::Ranking() = default;

//gestione della struttura dati
void Ranking::insert(SingleRank elem) {
    if (ranking.head == NULL || ranking.size < MAX_RANK) {
        ranking.newNodeAtTheEnd();
        ranking.tail->value.setNickname(elem.getNickname());
        ranking.tail->value.setPos(elem.getPos());
        ranking.tail->value.setBestTotScore(elem.getBestTotScore());
        fixRank();
        std::cout << "Elemento Inserito e posizionato correttamente in classifica";
        return;
    }

    if (ranking.size == MAX_RANK) {
        if (elem.getBestTotScore() < ranking.tail->value.getBestTotScore()) {
            std::cout << "Il giocatore non entra in classifica";
            return;
        } else {
            utl::Node<SingleRank> *toDel = ranking.tail;
            if (ranking.tail->prev != NULL) {
                ranking.tail = ranking.tail->prev;
                ranking.tail->next = NULL;
            } else {
                ranking.head = NULL;
                ranking.tail = NULL;
            }
            delete toDel;
            ranking.size--;
            ranking.newNodeAtTheEnd();
            ranking.tail->value.setNickname(elem.getNickname());
            ranking.tail->value.setPos(elem.getPos());
            ranking.tail->value.setBestTotScore(elem.getBestTotScore());
            fixRank();
            ranking.size++;
        }
    }
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

SingleRank Ranking::getRankElem (int searchPos) const {
    char filepath[MAX_PATH];
    strcpy(filepath, "../ranking/ranking.txt");
    std::ifstream rankingFile(filepath);

    if (!rankingFile.is_open()) {
        //std::cerr << "Impossibile aprire il file";
    }

    SingleRank searched = SingleRank();
    int pos = 0;
    char commaCheck1 = '\0';
    char nickname [MAX_NICKNAME];
    long bestScore = 0;

    while (rankingFile >> pos) {
        if (rankingFile >> commaCheck1 && commaCheck1 == ',') {
            if (rankingFile.getline(nickname, MAX_NICKNAME, ',')) {
                if (rankingFile >> bestScore) {
                    if (pos == searchPos) {
                        searched.setPos(pos);
                        searched.setNickname(nickname);
                        searched.setBestTotScore(bestScore);
                        return searched;
                    }
                } else {
                    //std::cerr << "Errore nel leggere bestScore! Pulisco lo stream. " << std::endl;
                    rankingFile.clear();
                }
            } else {
                //std::cerr << "Errore nel leggere nickname! Pulisco lo stream." << std::endl;
                rankingFile.clear();
            }
        } else {
            //std::cerr << "Errore la virgola! Pulisco lo stream." << std::endl;
            rankingFile.clear();
        }
        char ch;
        while (rankingFile.get(ch) && ch != '\n'){
            //se per caso ci fossero stati errori in inserimento
            //verrebbero bypassati da questo ciclo che fa arrivare
            //alla fine della linea
        }
    }

    //non trovato il livello
    rankingFile.close();
    return searched;
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
                    insert(elem);

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

// Helper per creare un file di ranking di esempio per i test
void Ranking::createDummyRankingFile(const char* filename) {
    // Tenta di rimuovere il file esistente per un test pulito
    if (std::remove(filename) == 0) {
        //std::cout << "File di test precedente '" << filename << "' rimosso." << std::endl;
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        //std::cerr << "ERRORE: Impossibile creare il file di test: " << filename << std::endl;
        return;
    }
    outFile << "1,Charlie,1200\n";
    outFile << "2,Alice,1000\n";
    outFile << "3,David Spacey,900\n";
    outFile << "4,Bob,800\n";
    outFile << "5,Eve,700\n"; // 5 elementi per testare MAX_RANK
    outFile.close();
    //std::cout << "File di ranking di test creato: " << filename << std::endl;
}
