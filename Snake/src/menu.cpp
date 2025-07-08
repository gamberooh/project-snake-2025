#include "../include/menu.h"
#include <cstring>
#include <iostream>

Menu::Menu() : currentPage(START), totalPages(3) {} //totalPages è a 3 perchè esculdo START e GAMEOVER

// Input

bool Menu::handleInput(int key, utl::Node<SingleLevel> *&currentLevel, bool &isRunning)
{
    //la logica è che ci sono tasti che vanno per tutte le pagine del menu e altri sepcifici, 
    //quindi controllo prima se è un di quelli generali e poi se è uno di quelli specifici

    switch (key)
    {
    case 'm':
        clear();
        printBackground(); // questo è un test
        refresh();
        return false;
        break;
    case 'q':
        isRunning = false;
        return false;
    case KEY_LEFT:
        if(currentPage-1 < 0) currentPage = static_cast<menuPage> (totalPages-1);
        else currentPage = static_cast<menuPage>(currentPage-1);
        break;
    case KEY_RIGHT:
        currentPage = static_cast<menuPage>((currentPage+1)%totalPages);
        break;
    default:
        switch (currentPage){
            case HOME:
                // funzione
            break;
            case LEVELS:
                return handleInputLevels(key, currentLevel);
                break;
            case RANKING:
                // funzione o if
                break;            
            case START:
                setupGame();
                break;
            case GAMEOVER:
                // funzione o if
                break;
            default:
                break;
        }
    }
    return true;
};

void Menu::setupGame()
{
}

bool Menu::handleInputLevels(int key, utl::Node<SingleLevel> *&currentLevel)
{
    //ho cambiato i tasti
    switch (key){
        case '+':
            if (currentLevel->next != NULL)
            currentLevel = currentLevel->next;
            break;
        case '-':
            if (currentLevel->prev != NULL)
                currentLevel = currentLevel->prev;
            break;
        default:
            break;
    }

    return true;
}

//Render

//Generic Render Things:

//diamond-shape page markers
void colorPagesDots(int maxRows, int maxCols, int pages, int actualPage) {
    for (int i = 1; i <= pages; i++)
        if (i == actualPage) {
            attron(COLOR_PAIR(3));
            mvaddch(maxRows-4, (maxCols - pages)/2+(i*2), ACS_DIAMOND);
            attroff(COLOR_PAIR(3));
        }
        else mvaddch(maxRows-4, (maxCols - pages)/2+(i*2), ACS_DIAMOND);
}

void drawFrame(const char* instructions, const char* title){
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);
    attron(COLOR_PAIR(utl::BLUE));

    // === Disegna bordo ===
    // Angoli
    mvaddch(0, 0, ACS_ULCORNER);
    mvaddch(0, maxCols - 1, ACS_URCORNER);
    mvaddch(maxRows - 1, 0, ACS_LLCORNER);
    mvaddch(maxRows - 1, maxCols - 1, ACS_LRCORNER);

    // Linee orizzontali
    for (int x = 1; x < maxCols - 1; x++) {
        mvaddch(0, x, ACS_HLINE);
        mvaddch(1, x, ACS_HLINE);
        mvaddch(maxRows - 5, x, ACS_HLINE);
        mvaddch(maxRows - 2, x, ACS_HLINE);
        mvaddch(maxRows - 1, x, ACS_HLINE);
    }

    // Linee verticali
    for (int y = 1; y < maxRows - 1; y++) {
        mvaddch(y, 0, ACS_VLINE);
        mvaddch(y, maxCols - 1, ACS_VLINE);
    }

    attroff(COLOR_PAIR(utl::BLUE));

    // === Titolo ===
    attron(A_BOLD);
    attron(COLOR_PAIR(utl::YELLOW));
    int titleX = (maxCols - strlen(title)) / 2;
    mvprintw(0, titleX, "%s", title);
    attroff(COLOR_PAIR(utl::YELLOW));

    // === Istruzioni ===
    //const char* instructions = "Usa [+] o [-] per muoverti, Invio o m per giocare, [<-]/[->] per cambiare pagina";
    int instrX = (maxCols - strlen(instructions)) / 2;
    mvprintw(maxRows - 2, instrX, "%s", instructions);
    attroff(A_BOLD);
}


void printSnake(){
    const int size = 6;
    const char *str[size] = {
        R"( ____              _          _   _                      )",
        R"(/ ___| _ __   __ _| | _____  | | | | ___  _ __ ___   ___ )",
        R"(\___ \| '_ \ / _` | |/ / _ \ | |_| |/ _ \| '_ ` _ \ / _ \)",
        R"( ___) | | | | (_| |   <  __/ |  _  | (_) | | | | | |  __/)",
        R"(|____/|_| |_|\__,_|_|\_\___| |_| |_|\___/|_| |_| |_|\___|)",
        R"(                                                         )",
    };
    // R serve per raw string non interpreta le sequenze di escape
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    rows -= size+1;
    cols -= (int)strlen(str[0]);
    for (int i = 0; i < size; i++)
    {
        mvprintw(rows / 2 + i, cols / 2, "%s", str[i]);
    }
}

void printGameOver(){
    const int size=5;
    const char *str[size] = {
        R"(  ____                         ___                 )",
        R"( / ___| __ _ _ __ ___   ___   / _ \__   _____ _ __ )",
        R"(| |  _ / _` | '_ ` _ \ / _ \ | | | \ \ / / _ \ '__|)",
        R"(| |_| | (_| | | | | | |  __/ | |_| |\ V /  __/ |   )",
        R"( \____|\__,_|_| |_| |_|\___|  \___/  \_/ \___|_|   )",
    };

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    rows -= size;
    cols -= (int)strlen(str[0]);
    for (int i = 0; i < size; i++)
    {
        mvprintw(rows / 2 + i, cols / 2, "%s", str[i]);
    }
}

void printRanking(){
    const int size=6;
    const char *str[size] = {
        R"(  ____             _    _              )",
        R"( |  _ \ __ _ _ __ | | _(_)_ __   __ _  )",
        R"( | |_) / _` | '_ \| |/ / | '_ \ / _` | )",
        R"( |  _ < (_| | | | |   <| | | | | (_| | )",
        R"( |_| \_\__,_|_| |_|_|\_\_|_| |_|\__, | )",
        R"(                                 |___/ )",
    };

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    rows -= size-1;
    cols -= (int)strlen(str[0]);
    for (int i = 0; i < size; i++)
    {
        mvprintw(rows / 2 + i, cols / 2, "%s", str[i]);
    }
}

void Menu::renderCurrentPage(utl::Node<SingleLevel> *currentLevel, utl::Node<SingleLevel>* head, utl::Node<SingleLevel>* tail) const
{
    erase();
    switch (currentPage)
    {
    case HOME:
        // drawFrame("caiosasc", "HOME");
        printSnake();
        break;
    case LEVELS:
        //renderLevels(currentLevel);
        renderLevels(currentLevel, head, tail);
        break;
    case RANKING:
        printRanking();
        break;
    case START:
        renderSetup();
        break;  
    case GAMEOVER:
        printGameOver();
        break;
    default:
        break;
    }
    refresh();
}

void Menu::renderSetup() const {

};

void Menu::renderLevels(utl::Node<SingleLevel> *currentLevel, utl::Node<SingleLevel>* head, utl::Node<SingleLevel>* tail) const{
    const int blockHeight = 7;
    const int blockWidth = 20;
    const int spacingX = 4;
    const int spacingY = 2;
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    drawFrame("Usa [+] o [-] per muoverti, Invio o m per giocare, [<-]/[->] per cambiare pagina", "LEVELS");

    int topFull = 2;
    int downFull = 5;
    int rightFull = 1;
    int leftFull = 1;
    int usableCols = maxCols - (rightFull + leftFull);     //una linea a destra e una a sinistra per bordi
    int usableRows = maxRows - (topFull + downFull);      //due line sopra e tre sotto per bordi e scritta  più uno spazio
    const int blocksPerRow = usableCols / (blockWidth + spacingX);
    const int blocksPerCol = usableRows / (blockHeight + spacingY);
    int row = 0, col = 0;
    int rowFactor = (usableRows - blocksPerCol * (blockHeight + spacingY))/2;
    int colFactor = (usableCols - blocksPerRow * (blockWidth + spacingX))/2;
    int startY = 0;
    int startX = 0;
    int pages = (tail -> value.stat.id + (blocksPerCol * blocksPerRow) - 1) / (blocksPerCol * blocksPerRow);      //tronca
    colorPagesDots(maxRows, maxCols, pages, 1);
    int currentPage = 1;
    while (head != NULL && ((currentPage - 1) * (blocksPerCol * blocksPerRow) >= currentLevel -> value.stat.id || currentPage * (blocksPerCol * blocksPerRow) < currentLevel -> value.stat.id)){  //per vedere la pagina gusta
        for (int i = 0; i<(blocksPerCol * blocksPerRow); i++)
            head = head -> next;
        currentPage++;
        colorPagesDots(maxRows, maxCols, pages, currentPage);
    }
    while(head != NULL && (row * (blockHeight + spacingY) + rightFull + leftFull + 2*rowFactor) < usableRows) {

        startY = row * (blockHeight + spacingY) + (topFull+downFull)/2 + rowFactor;
        startX = col * (blockWidth + spacingX) + (rightFull+leftFull)/2 + colFactor;
        // Colori
        int colorPair = 1;
        if (head -> value.stat.timePassed <= 1) colorPair = 2;
        else if (head -> value.stat.currentScore <= head -> value.stat.goal) colorPair = 3;
        if (currentLevel == head) colorPair = 4;
        attron(COLOR_PAIR(colorPair));

        for (int y = 0; y < blockHeight; ++y) {
            for (int x = 0; x < blockWidth; ++x) {
                int drawY = startY + y;
                int drawX = startX + x;
                if (y == 0 && x == 0)
                    mvaddch(drawY, drawX, ACS_ULCORNER);  // angolo alto sinistra
                else if (y == 0 && x == blockWidth - 1)
                    mvaddch(drawY, drawX, ACS_URCORNER);  // angolo alto destra
                else if (y == blockHeight - 1 && x == 0)
                    mvaddch(drawY, drawX, ACS_LLCORNER);  // angolo basso sinistra
                else if (y == blockHeight - 1 && x == blockWidth - 1)
                    mvaddch(drawY, drawX, ACS_LRCORNER);  // angolo basso destra
                else if (y == 0 || y == blockHeight - 1)
                    mvaddch(drawY, drawX, ACS_HLINE);     // linea sopra/sotto
                else if (x == 0 || x == blockWidth - 1)
                    mvaddch(drawY, drawX, ACS_VLINE);     // linea laterale
            }
        }

        attron(A_BOLD);
        mvprintw(startY, startX + 1, "Livello %d", head -> value.stat.id);
        attroff(A_BOLD);
        mvprintw(startY + 1, startX + 1, "Score: %d", head -> value.stat.currentScore);
        mvprintw(startY + 2, startX + 1, "Best:  %d", head -> value.stat.bestScore);
        mvprintw(startY + 3, startX + 1, "Goal:  %d", head -> value.stat.goal);
        mvprintw(startY + 4, startX + 1, "Total Time: %.2f", head -> value.stat.timeLimit);
        mvprintw(startY + 5, startX + 1, "Time Left: %.2f", (head -> value.stat.timeLimit - head -> value.stat.timePassed));
        attroff(COLOR_PAIR(colorPair));

        if (head->next != NULL && (col + 1 < blocksPerRow)) {
            int lineY = startY + blockHeight / 2;
            int lineStartX = startX + blockWidth;
            int lineEndX = lineStartX + spacingX - 1;

            for (int x = lineStartX; x <= lineEndX; x++) {
                if ((x - lineStartX) % 2 == 0) {
                    mvaddch(lineY, x, ACS_HLINE);
                }
            }
        }

        // Avanzamento nella griglia
        if (++col >= blocksPerRow) {
            col = 0;
            ++row;
        }

        head = head -> next;
    }
}

void Menu::printBackground() const{

}

// GG Davidoski


//
// Created by gamberooh on 03/07/25.
//

// #include "../include/menu.h"

// Menu::Menu(): height(30), width(30) {}

// void Menu::setWindow() {
//     int maxX, maxY;
//     getmaxyx(stdscr, maxY, maxX);
//     menuWin = newwin(height+2, width+2, 0, 0);
//     //setWindowPos();
// }


// void Menu::setNickname() {
//     utl::Position pos = utl::Position(4, 4);
//     echo(); //abilito la digitazione
//     curs_set(1); //mostro il cursore

//     mvwprintw(menuWin, pos.y, pos.x, nickname, sizeof(nickname)); //posso inserire fino a max 30 char
//     wmove(menuWin, pos.y, pos.x+2); //sposto il cursore per iniziare a scrivere
//     wrefresh(menuWin);

//     wgetnstr(menuWin, nickname, sizeof(nickname) -1);
//     nickname[sizeof(nickname) - 1] = '\0'; //termine stringa

// }

// void Menu::transmitInput() {
//     curs_set(0);
//     noecho();
    
//     //controllo su tutti i log nella cartella "../log"
//     // che esista un log con nickname.txt o .csv

//     // si -> finwstra carica partita o nuova
//     // no -> nuova partita
// }

// void Menu::processInput() {
//     while (nickname[0] == '\0') {
//         utl::Position pos = utl::Position(6, 4);
//         mvprintw(pos.y, pos.x, "Inserire il nome..");
//         wrefresh(menuWin);
//         setNickname();
//     }
   
//     if (wgetch(menuWin) == KEY_ENTER) {
//         transmitInput();
//     }



//     // button or getch()==enter
//         // transmitInput()
// }
