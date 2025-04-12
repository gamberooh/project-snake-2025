#include "arena.h"

Arena::Arena(): height(30), width(30){
    //initialize arena to false
   for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++)
          arena[i][j] = false;
}

void Arena::setWindow() {
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    arenaWin = newwin(height+2, width+2, 0, 0);
    setWindowPos();
}

void Arena::setWindowPos(){
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);
    int offsetX = (maxX-width)/2;
    int offsetY = (maxY-height)/2;

    if(maxX < width) {
        offsetX = 0;
    }
    if(maxY < height) {
        offsetY = 0;
    }
    mvwin(arenaWin, offsetY ,offsetX);
}

void Arena::display(const utl::Position &snakeHead, const utl::Position &food) const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arena[i][j] == true) {
                if (i == food.y && j == food.x) {
                    mvwaddch(arenaWin, i + 1, j + 1, '&' | COLOR_PAIR(2) | A_BOLD);
                }
                else if (i == snakeHead.y && j == snakeHead.x) {
                    mvwaddch(arenaWin, i + 1, j + 1, '@' | COLOR_PAIR(1) | A_BOLD);
                } else{
                    mvwaddch(arenaWin, i + 1, j + 1, '0' | COLOR_PAIR(1) | A_BOLD);
                }
            }
        }
    }
}

void Arena::render(const utl::Position &snakeHead, const utl::Position &food, const int &score) const{
    werase(arenaWin);
    box(arenaWin, 0, 0);
    {
        wattron(arenaWin, A_BOLD);
        mvwprintw(arenaWin, 0, 1, "Score:");
        wattron(arenaWin, COLOR_PAIR(3));
        mvwprintw(arenaWin, 0, 7, "%d", score);
        wattroff(arenaWin, COLOR_PAIR(3));
        wattron(arenaWin, A_BOLD);
    }//print score
    display(snakeHead, food);
    wrefresh(arenaWin);
}



