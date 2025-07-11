#include <cstring>
#include "../include/menu.h"
#include "../resources/ASCIIart.h"
#include "../include/singleRank.h"

Menu::Menu() : currentPage(START), totalPages(3)
{
    ranking.buildListFromFile();
} // totalPages è a 3 perchè esculdo START e GAMEOVER

// Input

bool Menu::handleInput(int key, utl::Node<SingleLevel> *&currentLevel, bool &isRunning)
{
    // Pagine Speciali
    switch (currentPage)
    {
    case START:
        setupGame(currentLevel);
        clear();
        currentPage = HOME;
        break;
    case GAMEOVER:
        return handleInputGameover(key, isRunning);
        break;
        return true;
    }

    // Pagine Normali
    //  la logica è che ci sono tasti che vanno per tutte le pagine del menu e altri sepcifici,
    //  quindi controllo prima se è un di quelli generali e poi se è uno di quelli specifici

    switch (key)
    {
    case 'm':
        clear();
        printLeavesArt();
        refresh();
        currentPage = HOME;
        return false;
        break;
    case 'q':
        // lETSGOSKI
        ranking.writeRankingFile();
        isRunning = false;
        return false;
    case KEY_LEFT:
        if (currentPage > totalPages)
            currentPage = LEVELS;
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
            if (!handleInputLevels(key, currentLevel))
            {
                currentPage = HOME;
                return false;
            };
            break;
        case RANKING:
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
    case 'r':
        currentLevel->value.stat.resetLevel();
        currentLevel->value.snake.reset(currentLevel->value.arena, currentLevel->value.stat.snakeSpeed);
        break;
    case 10: // 10 = KEY_ENTER
        clear();
        printLeavesArt(); // questo è un test
        refresh();
        return false;
        break;
    default:
        break;
    }

    return true;
}

bool Menu::handleInputGameover(int key, bool &isRunning)
{
    switch (key)
    {
    case 'l':
    case 10:
        currentPage = LEVELS;
        break;
    case 'q':
        // DAVIDOSKI
        isRunning = false;
        return false;
        break;
    default:
        break;
    }
    return true;

    // si può aggiunger il ritenta
}

// Set Page
void Menu::setGameoverPage()
{
    currentPage = GAMEOVER;
}

void Menu::setLevelPage()
{
    currentPage = LEVELS;
}

void Menu::updateRank(utl::Node<SingleLevel>* head) {
    ranking.updateRank(head);
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

    if (currentPage == START || currentPage == GAMEOVER)
        return; // Non stampa il titolo

    // Calcolo larghezza totale del menu
    int menuWidth = 0;
    for (int i = 0; i < totalPages; i++)
    {
        menuWidth += strlen(menuPages[i]);
    }
    menuWidth += (totalPages - 1) * strlen(divider);
    int titleX = (maxCols - menuWidth) / 2; // Centra i titoli
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
void drawBoxBorder(int startY, int startX, int height, int width)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
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

void Menu::setupGame(utl::Node<SingleLevel>* head)  //head e currenteLevel all'inizio sono uguali
{
    int maxCol, maxRow;
    int offsetY;
    const int nicknameLenght = 31;
    const char *prompt = "Nickname: ";
    char input[nicknameLenght] = "";
    int pos = 0;

    nodelay(stdscr, FALSE); //attende l'input
    echo();
    curs_set(1);

    bool inserting = true;

    while (inserting)
    {
        getmaxyx(stdscr, maxRow, maxCol);
        offsetY = (2 + (maxRow - 5 - getHappySnakeSize())) / 2;

        erase();
        printVineArt();
        printHappySnakeArt(); 
        drawFrame("inserisci il nickname e premi ENTER", START); 

        // Stampa il prompt e l’input attuale centrato orizzontalmente

        int offsetX = (maxCol - strlen(prompt) - strlen(input)) / 2;
        
        mvprintw(offsetY, offsetX, "%s", prompt);
        mvprintw(offsetY, offsetX + strlen(prompt), "%s", input);

        // Posiziona il cursore in fondo all’input digitato
        move(offsetY, offsetX + strlen(prompt) + pos);
        refresh();

        int ch = getch();

        switch (ch){
            case 10: //tasto ENTER
                if(input[0] != '\0')
                    inserting = false;  // se qualcosa è stato scritto, esce dal loop
                break;
            case KEY_RESIZE:
                continue;
                break;
            case KEY_BACKSPACE:
                if(pos > 0){
                    pos --;
                    input[pos] = '\0';
                    mvaddch(offsetY, offsetX + strlen(prompt) + pos , ' ');
                }
                break;
            default:
                if (isprint(ch) && pos <  nicknameLenght - 1){
                    input[pos] = ch;
                    pos++;
                    input[pos] = '\0';
                }
                
        }
    }

    strncpy(nickname, input, nicknameLenght);

    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    //load game se esiste
    if(log.exists(nickname))
        log.loadGame(nickname, head);

    //inserting player in the ranking
    ranking.insertPlayer(nickname);
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
    drawFrame("Usa [+] o [-] per muoverti, ENTER o [m] per giocare - [r] per resettare il livello - [<-]/[->] per cambiare pagina - [q] per chiudere e salvare", currentPage);
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
        int colorPair = utl::GREEN;

        if (head->value.stat.timePassed <= 0)
            colorPair = utl::RED;
        else if (head->value.stat.timePassed < currentLevel->value.stat.timeLimit)
            colorPair = utl::YELLOW;

        if (currentLevel == head)
            colorPair = utl::WHITE;

        attron(COLOR_PAIR(colorPair));

        drawBoxBorder(startY, startX, blockHeight, blockWidth);

        // Testi nel blocco
        attron(A_BOLD);
        mvprintw(startY, startX + 1, "Livello %d", head->value.stat.id);
        attroff(A_BOLD);

        mvprintw(startY + 1, startX + 1, "Score: %d", head->value.stat.currentScore);
        if(head->value.stat.bestScore > 0){
            mvprintw(startY + 2, startX + 1, "Best: ");
            attron(COLOR_PAIR(utl::YELLOW) | A_BOLD);
            mvprintw(startY + 2, startX + 7, "%d", head->value.stat.bestScore);
            attroff(A_BOLD);
            attron(COLOR_PAIR(colorPair));
        }
        else    
            mvprintw(startY + 2, startX + 1, "Best:  %d", head->value.stat.bestScore);
        mvprintw(startY + 3, startX + 1, "Bonus: %d", head->value.stat.endLevelBonus);
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

void Menu::renderRank() const {
    printLeavesArt();
    drawFrame("[<-]/[->] per cambiare pagina - [q] per chiudere e salvare", currentPage);

    const int boxHeigth=6, boxWidth=50, spacing=1, maxRank=5;
    int maxCol, maxRow;
    getmaxyx(stdscr, maxRow, maxCol);
    int offsetY = (maxRow - maxRank*boxHeigth - (maxRank-1)*spacing)/2, 
    offsetX=(maxCol-boxWidth)/2;
    utl::Node<SingleRank>* tailRank = ranking.getTailRankPointer();

    int position = 1;
    long scoreToReach; //nel caso il giocatore non sia tra i primi 5 salvo i punti del quinto
    utl::Node<SingleRank>* headRank = ranking.getHeadRankPointer();

    while (headRank != NULL && position <= maxRank) {
        drawBoxBorder(offsetY, offsetX, boxHeigth, boxWidth);
        const int size = 30;
        char string[size];
        attron(A_BOLD);
        switch(position){
            case 1:
                attron(COLOR_PAIR(utl::YELLOW) | A_UNDERLINE);
                break;
            case 2:
                attron(COLOR_PAIR(utl::CYAN) | A_UNDERLINE);
                break;
            case 3:
                attron(COLOR_PAIR(utl::GREEN) | A_UNDERLINE);
                break;
            case 5:
                scoreToReach = headRank -> value.getBestTotScore();
            default:
                attron(COLOR_PAIR(utl::WHITE));
                break;
            
        }
        snprintf(string, size, "%d: %s", position, headRank -> value.getNickname());
        mvwprintw(stdscr, offsetY+2, (maxCol-strlen(string))/2, "%s", string);
        switch(position){
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
        //Total score
        snprintf(string, size, "Total score: %ld", headRank -> value.getBestTotScore());
        mvwprintw(stdscr, offsetY+3, (maxCol-strlen(string))/2, "%s", string);
        offsetY += boxHeigth + spacing;
        attroff(A_BOLD);
        headRank = headRank -> next;
        position++;
    }
    if (ranking.playerNotInRank()){
        long playerScore = ranking.getPlayerScore();
        scoreToReach -= playerScore;
        const int size = 100;
        char msg[size];
        attron(COLOR_PAIR(utl::RED)| A_BLINK | A_UNDERLINE | A_BOLD);
        snprintf(msg, size, "Punti mancanti alla TOP %d: %ld", MAX_RANK, scoreToReach);
        mvwprintw(stdscr, offsetY+3, (maxCol-strlen(msg))/2, "%s", msg);
        attroff(COLOR_PAIR(utl::RED)| A_BLINK | A_UNDERLINE | A_BOLD);
    }
}


void Menu::renderGameover() const
{
    drawFrame("Usa [l] o premi ENTER per tornare alla selezione dei livelli - [q] per chiudere e salvare", GAMEOVER);
    printStunnedSnakeArt();
    printGameoverArt();
}

void Menu::renderHome() const
{
    printVineArt();
    drawFrame("[<-]/[->] per cambiare pagina - [q] per chiudere e salvare", currentPage);
    int maxRow, maxCol;
    getmaxyx(stdscr, maxRow, maxCol);
    const char *instructions;
    const int sugegstedValueBottom = 50, sugegstedValueTop = 60;

    if (maxRow > sugegstedValueTop)
    {
        instructions = "Si consiglia di ingrandire la pagina, utilizzando CTRL + [+]";
        attron(COLOR_PAIR(utl::WHITE) | A_BOLD);
        mvprintw(maxRow / 2, (maxCol - strlen(instructions)) / 2, "%s", instructions);
        attroff(COLOR_PAIR(utl::WHITE) | A_BOLD);
    }
    else if (maxRow < sugegstedValueBottom)
    {
        instructions = "Si consiglia di rimpicciolire la pagina, utilizzando CTRL + [-]";
        attron(COLOR_PAIR(utl::WHITE) | A_BOLD);
        mvprintw(maxRow / 2, (maxCol - strlen(instructions)) / 2, "%s", instructions);
        attroff(COLOR_PAIR(utl::WHITE) | A_BOLD);
    }
    else
    {
        printSnakeHomeArt();
        char currentPlayer[50]; //50 è un valre safe perchè abbastanzapiù garnde della lunghezza del nome massima
        snprintf(currentPlayer, 50, "Current Player: %s", nickname);

        //current player
        attron(COLOR_PAIR(utl::WHITE) | A_BOLD);
        mvprintw(maxRow/2, (maxCol- strlen(currentPlayer))/2, "Current Player: ");
        attron(COLOR_PAIR(utl::YELLOW) | A_BOLD);
        mvprintw(maxRow/2, (maxCol- strlen(currentPlayer))/2 + strlen("Current Player: "), "%s", nickname);
        attroff(COLOR_PAIR(utl::YELLOW) | A_BOLD);

        //piccola animazione per i credits
        const char *creditText = ">>> Davide Gamberini <<<          >>> Mattia Graziani <<<          >>> Samuele Grillini <<<          ";
        const int height = 3, width = 61;
        const int offsetX = (maxCol - width) / 2;
        const int offsetY = (maxRow - height) / 2 + getHomeSnakeSize()-4;
        const int innerWidth = width - 2; // esclusi i botdi

        drawBoxBorder(offsetY, offsetX, height, width);

        int textLen = strlen(creditText);
        int y = offsetY + height / 2;
        int delayMs = 100;

        static int offset = 0;
        mvhline(y, offsetX + 1, ' ', innerWidth); //mvhline stampa lo stesso carattere (passato come parametro) per tutta la riga

        // Disegna solo la parte del testo visibile nel box
        for (int i = 0; i < innerWidth; ++i)
        {
            int textPos = (offset + i) % textLen;
            if(creditText[textPos] != ' ' and creditText[textPos] != '<' and creditText[textPos]!= '>') attron(COLOR_PAIR(utl::CYAN) | A_BOLD);
            mvaddch(y, offsetX + 1 + i, creditText[textPos]);   
            attroff(COLOR_PAIR(utl::CYAN) | A_BOLD);
        }
        offset = (offset + 1) % textLen;
        
        napms(delayMs); //attende tot MS
    }
}

// GG Davidoski