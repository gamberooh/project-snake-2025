#include <cstring>
#include "../include/menu.h"
#include "../resources/ASCIIart.h"
#include "../include/singleRank.h"


Menu::Menu() : currentPage(START), totalPages(3) {
    ranking.createDummyRankingFile("../ranking/ranking.txt");
    ranking.buildListFromFile();
} // totalPages è a 3 perchè esculdo START e GAMEOVER

// Input

bool Menu::handleInput(int key, utl::Node<SingleLevel> *&currentLevel, bool &isRunning)
{
    //Pagine Speciali
    switch(currentPage){
        case START:
            setupGame();
            clear();
            printLeafArt();
            refresh();
            return false;
            break;
        case GAMEOVER:
            return handleInputGameover(key, isRunning);
            break;
    }
    
    //Pagine Normali
    // la logica è che ci sono tasti che vanno per tutte le pagine del menu e altri sepcifici,
    // quindi controllo prima se è un di quelli generali e poi se è uno di quelli specifici    

    switch (key)
    {
    case 'm':
        clear();
        printLeafArt();
        refresh();
        currentPage = HOME;
        return false;
        break;
    case 'q':
        //lETSGOSKI
        isRunning = false;
        return false;
    case KEY_LEFT:
        if(currentPage > totalPages) currentPage = LEVELS;
        if (currentPage - 1 < 0)
            currentPage = static_cast<menuPage>(totalPages - 1);
        else
            currentPage = static_cast<menuPage>(currentPage - 1);
        break;
    case KEY_RIGHT:
        currentPage = static_cast<menuPage>((currentPage + 1) % totalPages);
        break;
    default:
        switch (currentPage)
        {
        case HOME:
            // funzione
            break;
        case LEVELS:
            if(!handleInputLevels(key, currentLevel)){
                currentPage=HOME;
                return false;
            };
            break;
        case RANKING:
            handleInputRank(key);
            break;
        default:
            break;
        }
    }
    return true;
};

bool Menu::handleInputLevels(int key, utl::Node<SingleLevel> *&currentLevel)
{
    // ho cambiato i tasti
    switch (key)
    {
    case '+':
        if (currentLevel->next != NULL)
            currentLevel = currentLevel->next;
        break;
    case '-':
        if (currentLevel->prev != NULL)
            currentLevel = currentLevel->prev;
        break;
    case 10:  //10 = KEY_ENTER
        clear();
        printLeafArt(); // questo è un test
        refresh();
        return false;
        break;
    default:
        break;
    }

    return true;
}

void Menu::handleInputRank(int key){
    switch(key){
        case KEY_UP:
            //...
            break;
        case KEY_DOWN:
            //..
            break;
        default:
            break;
    }
}

bool Menu::handleInputGameover(int key, bool &isRunning){
    switch (key) {
    case 'l':
    case 10:
        currentPage = LEVELS;
        break;
    case 'q':
        //DAVIDOSKI
        isRunning = false;
        return false;
        break;
    default:
        break;
    }
    return true;

    //si può aggiunger il ritenta
}

//Set Page
void Menu::setGameoverPage(){
    currentPage = GAMEOVER;
}

void Menu::setLevelPage(){
    currentPage = LEVELS;
}

// Render

// Generic Render Things:

// diamond-shape page markers
void colorPagesDots(int maxRows, int maxCols, int pages, int actualPage)
{
    for (int i = 1; i <= pages; i++)
        if (i == actualPage)
        {
            attron(COLOR_PAIR(utl::YELLOW));
            mvaddch(maxRows - 4, (maxCols - pages) / 2 + (i * 2), ACS_DIAMOND);
            attroff(COLOR_PAIR(utl::YELLOW));
        }
        else
            mvaddch(maxRows - 4, (maxCols - pages) / 2 + (i * 2), ACS_DIAMOND);
}

void drawFrame(const char *instructions, menuPage currentPage)
{
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
    for (int x = 1; x < maxCols - 1; x++)
    {
        mvaddch(0, x, ACS_HLINE);
        mvaddch(1, x, ACS_HLINE);
        mvaddch(maxRows - 5, x, ACS_HLINE);
        mvaddch(maxRows - 2, x, ACS_HLINE);
        mvaddch(maxRows - 1, x, ACS_HLINE);
    }

    // Linee verticali
    for (int y = 1; y < maxRows - 1; y++)
    {
        mvaddch(y, 0, ACS_VLINE);
        mvaddch(y, maxCols - 1, ACS_VLINE);
    }

    attroff(COLOR_PAIR(utl::BLUE));
    attron(A_BOLD | COLOR_PAIR(utl::WHITE));

    // === Istruzioni ===
    int instrX = (maxCols - strlen(instructions)) / 2;
    mvprintw(maxRows - 2, instrX, "%s", instructions);


    // === Titolo ===
    const int totalPages = 3;
    const char *menuPages[totalPages] = {" HOME", "LEVELS", "RANKING "};
    const char *divider = " - ";

    if(currentPage == START || currentPage == GAMEOVER) return; //Non stampa il titolo
    
    // Calcolo larghezza totale del menu
    int menuWidth = 0;
    for (int i = 0; i < totalPages; i++) {
        menuWidth += strlen(menuPages[i]);
    }
    menuWidth += (totalPages - 1) * strlen(divider);
    int titleX = (maxCols - menuWidth) / 2; //Centra i titoli
    for (int i = 0; i < totalPages; i++)
    {
        if (static_cast<int>(currentPage) == i)
            attron(COLOR_PAIR(utl::YELLOW));
        mvprintw(0, titleX, "%s", menuPages[i]);
        titleX += strlen(menuPages[i]);
        if (static_cast<int>(currentPage) == i)
            attron(COLOR_PAIR(utl::WHITE));
        if (i != (totalPages - 1))
        {
            mvprintw(0, titleX, "%s", divider);
            titleX += strlen(divider);
        }
    }
    attroff(COLOR_PAIR(utl::YELLOW));
    attroff(COLOR_PAIR(utl::WHITE));
    attroff(A_BOLD);
}

// Disegna un bordo rettangolare con angoli e linee
void drawBoxBorder(int startY, int startX, int height, int width) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int drawY = startY + y;
            int drawX = startX + x;
            if (y == 0 && x == 0)
                mvwaddch(stdscr, drawY, drawX, ACS_ULCORNER);
            else if (y == 0 && x == width - 1)
                mvwaddch(stdscr, drawY, drawX, ACS_URCORNER);
            else if (y == height - 1 && x == 0)
                mvwaddch(stdscr, drawY, drawX, ACS_LLCORNER);
            else if (y == height - 1 && x == width - 1)
                mvwaddch(stdscr, drawY, drawX, ACS_LRCORNER);
            else if (y == 0 || y == height - 1)
                mvwaddch(stdscr, drawY, drawX, ACS_HLINE);
            else if (x == 0 || x == width - 1)
                mvwaddch(stdscr, drawY, drawX, ACS_VLINE);
        }
    }
}

void Menu::setupGame()
{   
    //Set UP -> get Nickname
    erase();
    printHappySnakeArt();
    drawFrame("inserisci il nickname e premi ENTER", START);
    int maxCol = getmaxx(stdscr);
    int offsetY = (2 + (getmaxy(stdscr) - 5 - getHappySnakeSize())) / 2;
    mvprintw(offsetY, (maxCol-strlen("Nickname"))/2, "Nickname: ");
    refresh();

    nodelay(stdscr, FALSE);
    echo();
    curs_set(1); //mostro il cursore

    do{
        getnstr(nickname, sizeof(nickname) - 1); // legge stringa con lunghezza massima
        move(offsetY, (maxCol-strlen("Nickname"))/2 + strlen("Nickname: "));
    } while(nickname[0] == '\0');
    //Ripristina la Normalità
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0); 
    currentPage = HOME;
}

void Menu::renderCurrentPage(utl::Node<SingleLevel> *currentLevel, utl::Node<SingleLevel> *head, utl::Node<SingleLevel> *tail) const
{
    erase();
    switch (currentPage)
    {
    case HOME:
        renderHome();
        break;
    case LEVELS:
        renderLevels(currentLevel, head, tail);
        break;
    case RANKING:
        renderRank();
        break;
    case GAMEOVER:
        renderGameover();
        break;
    default:
        break;
    }
    refresh();
}

void Menu::renderLevels(utl::Node<SingleLevel> *currentLevel, utl::Node<SingleLevel> *head, utl::Node<SingleLevel> *tail) const
{
    drawFrame("Usa [+] o [-] per muoverti, Invio o m per giocare - [<-]/[->] per cambiare pagina - [q] per chiudere e salvare", currentPage);
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    // Margini per i bordi e spaziatura
    constexpr int topMargin = 2;
    constexpr int bottomMargin = 5;
    constexpr int rightMargin = 1;
    constexpr int leftMargin = 1;   
    
    constexpr int blockHeight = 7;
    constexpr int blockWidth = 20;
    constexpr int spacingX = 4;
    constexpr int spacingY = 2;

    int usableWidth = maxCols - (rightMargin + leftMargin);
    int usableHeight = maxRows - (topMargin + bottomMargin);

    int blocksPerRow = usableWidth / (blockWidth + spacingX);
    int blocksPerCol = usableHeight / (blockHeight + spacingY);

    int rowPadding = (usableHeight - blocksPerCol * (blockHeight + spacingY)) / 2;
    int colPadding = (usableWidth - blocksPerRow * (blockWidth + spacingX)) / 2;

    int totalBlocksPerPage = blocksPerRow * blocksPerCol;
    int totalPages = (tail->value.stat.id + totalBlocksPerPage - 1) / totalBlocksPerPage;

    // Disegna i pallini delle pagine
    colorPagesDots(maxRows, maxCols, totalPages, 1);

    int currentPage = 1;
    // Avanza 'head' fino alla pagina contenente il livello corrente
    while (head != nullptr && 
          ((currentPage - 1) * totalBlocksPerPage >= currentLevel->value.stat.id || 
           currentPage * totalBlocksPerPage < currentLevel->value.stat.id)) 
    {
        for (int i = 0; i < totalBlocksPerPage && head != nullptr; ++i)
            head = head->next;
        currentPage++;
        colorPagesDots(maxRows, maxCols, totalPages, currentPage);
    }

    int row = 0, col = 0;
    // Ciclo di rendering blocchi nella pagina corrente
    while (head != nullptr && (row * (blockHeight + spacingY) + rightMargin + leftMargin + 2 * rowPadding) < usableHeight) 
    {
        int startY = row * (blockHeight + spacingY) + (topMargin + bottomMargin) / 2 + rowPadding;
        int startX = col * (blockWidth + spacingX) + (rightMargin + leftMargin) / 2 + colPadding;

        // Determina il colore in base allo stato del livello
        int colorPair = 1;
        if (head->value.stat.timePassed <= 1)
            colorPair = 2;
        else if (head->value.stat.currentScore <= head->value.stat.goal)
            colorPair = 3;
        if (currentLevel == head)
            colorPair = 4;

        attron(COLOR_PAIR(colorPair));

        drawBoxBorder(startY, startX, blockHeight, blockWidth);

        // Testi nel blocco
        attron(A_BOLD);
        mvprintw(startY, startX + 1, "Livello %d", head->value.stat.id);
        attroff(A_BOLD);

        mvprintw(startY + 1, startX + 1, "Score: %d", head->value.stat.currentScore);
        mvprintw(startY + 2, startX + 1, "Best:  %d", head->value.stat.bestScore);
        mvprintw(startY + 3, startX + 1, "Goal:  %d", head->value.stat.goal);
        mvprintw(startY + 4, startX + 1, "Total Time: %.2f", head->value.stat.timeLimit);
        mvprintw(startY + 5, startX + 1, "Time Left: %.2f", (head->value.stat.timeLimit - head->value.stat.timePassed));

        attroff(COLOR_PAIR(colorPair));

        // Disegna linea orizzontale tra blocchi se non ultimo colonna
        if (head->next != nullptr && (col + 1 < blocksPerRow)) 
        {
            int lineY = startY + blockHeight / 2;
            int lineStartX = startX + blockWidth;
            int lineEndX = lineStartX + spacingX - 1;

            for (int x = lineStartX; x <= lineEndX; x++) 
            {
                if ((x - lineStartX) % 2 == 0)
                    mvaddch(lineY, x, ACS_HLINE);
            }
        }

        // Aggiorna posizione nella griglia
        if (++col >= blocksPerRow) 
        {
            col = 0;
            ++row;
        }

        head = head->next;
    }
}

void Menu::renderRank() const{
    printLeafArt();
    drawFrame("[^]/[v] per scorrere la classifica - [<-]/[->] per cambiare pagina - [q] per chiudere e salvare", currentPage);

    const int boxHeigth=6, boxWidth=50, spacing=1, rankPerPage=5;
    int maxCol, maxRow;
    getmaxyx(stdscr, maxRow, maxCol);
    int offsetY = (maxRow - rankPerPage*boxHeigth - (rankPerPage-1)*spacing)/2, 
    offsetX=(maxCol-boxWidth)/2;

    const int rankSize = ranking.getRankSize();

    for(int i=1; i<=rankSize && i<=rankPerPage; i++){
        drawBoxBorder(offsetY, offsetX, boxHeigth, boxWidth);
        SingleRank currentRank = ranking.getRankElem(i);


        //Nickname + pos
        const int size = 30;
        char string[size];
        attron(A_BOLD);
        switch(i){
            case 1:
                attron(COLOR_PAIR(utl::YELLOW) | A_UNDERLINE);
                break;
            case 2:
                attron(COLOR_PAIR(utl::CYAN) | A_UNDERLINE);
                break;
            case 3:
                attron(COLOR_PAIR(utl::GREEN) | A_UNDERLINE);
                break;
            default:
                attron(COLOR_PAIR(utl::WHITE));
                break;
        }
        snprintf(string, size, "%d: %s", i, currentRank.getNickname());
        mvwprintw(stdscr, offsetY+2, (maxCol-strlen(string))/2, "%s", string);
        switch(i){
            case 1:
                attroff(COLOR_PAIR(utl::YELLOW) | A_UNDERLINE);
                break;
            case 2:
                attroff(COLOR_PAIR(utl::CYAN) | A_UNDERLINE);
                break;
            case 3:
                attroff(COLOR_PAIR(utl::GREEN) | A_UNDERLINE);
                break;
            default:
                attroff(COLOR_PAIR(utl::WHITE) | A_UNDERLINE);
                break;
            
        }
        attroff(A_BOLD);

        //Total score
        snprintf(string, size, "Total score: %ld", currentRank.getBestTotScore());
        mvwprintw(stdscr, offsetY+3, (maxCol-strlen(string))/2, "%s", string);
        offsetY += boxHeigth + spacing;
    }
}

void Menu::renderGameover() const{
    drawFrame("Usa [l] o premi ENTER per tornare alla selezione dei livelli - [q] per chiudere e salvare", GAMEOVER);
    printStunnedSnakeArt();
    printGameoverArt();
}

void Menu::renderHome() const{
    drawFrame("[<-]/[->] per cambiare pagina - [q] per chiudere e salvare", currentPage);
    int maxRow, maxCol;
    getmaxyx(stdscr, maxRow, maxCol);
    const char *instructions;
    const int sugegstedValueBottom = 50, sugegstedValueTop=70;
    
    if(maxRow > sugegstedValueTop){
        instructions = "Si consigli di ingrandire la pagina, utlizzando CTRL + [+]"; 
        attron(COLOR_PAIR(utl::WHITE) | A_BOLD);
        mvprintw(maxRow/2, (maxCol-strlen(instructions))/2, "%s", instructions);
        attroff(COLOR_PAIR(utl::WHITE) | A_BOLD);
    }
    else if(maxRow < sugegstedValueBottom){
        instructions = "Si consigli di rimpicciolire la pagina, utlizzando CTRL + [-]"; 
        attron(COLOR_PAIR(utl::WHITE) | A_BOLD);
        mvprintw(maxRow/2, (maxCol-strlen(instructions))/2, "%s", instructions);
        attroff(COLOR_PAIR(utl::WHITE) | A_BOLD);
    }
    else {
        printSnakeHomeArt();
    }
}
// GG Davidoski