#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include "utility.h"
#include "singleLevel.h"
#include "ranking.h"

enum menuPage{
    HOME,
    LEVELS,
    RANKING,
    START,
    GAMEOVER,
};

//se ne possono aggiungere altre come options

class Menu {

    public:
        Menu();
        bool handleInput(int key, utl::Node<SingleLevel>* &currentLevel, bool &isRunning);
        void renderCurrentPage(utl::Node<SingleLevel>* currentLevel, utl::Node<SingleLevel>* head, utl::Node<SingleLevel>* tail) const;
        void setGameoverPage();
        void setLevelPage();
        void updateRank(utl::Node<SingleLevel>* head);
        char nickname[31];

    private:
        const int totalPages;
        menuPage currentPage;
        Ranking ranking;

        //Setup
        void setupGame(utl::Node<SingleLevel>* head);
        //Levels
        bool handleInputLevels(int key, utl::Node<SingleLevel>* &currentLevel);
        void renderLevels(utl::Node<SingleLevel>* currentLevel, utl::Node<SingleLevel>* head, utl::Node<SingleLevel>* tail) const;

        bool handleInputGameover(int key, bool &isRunning);
        void renderGameover() const;

        void renderHome() const;

        void renderRank() const;


};



#endif //MENU_H
