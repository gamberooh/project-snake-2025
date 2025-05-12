#ifndef ARENA_H
#define ARENA_H

#include <ncurses.h>
#include "utility.h"

class Arena {
    public:
        Arena();
        const int height;
        const int width;
        bool arena[30][30];

        void setWindow();
        //quando si passa per riferimento il const serve anche nella dichiarazione nel file.h
        void render(const utl::Position &snakeHead, const utl::Position &food, const int &score) const;


    private:
        void display(const utl::Position &snakeHead, const utl::Position &food) const;
        void setWindowPos() ;

        WINDOW *arenaWin;
};



#endif //ARENA_H
