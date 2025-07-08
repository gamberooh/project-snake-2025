#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include "utility.h"
#include "singleLevel.h"

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

    private:
        const int totalPages;
        menuPage currentPage;
        //Setup
        void setupGame();
        void renderSetup() const;
        //Levels
        bool handleInputLevels(int key, utl::Node<SingleLevel>* &currentLevel);
        void renderLevels(utl::Node<SingleLevel>* currentLevel, utl::Node<SingleLevel>* head, utl::Node<SingleLevel>* tail) const;
        //Uguale per le altre (le funzioni di render devono essere const)
        void printBackground() const;
};



#endif //MENU_H
