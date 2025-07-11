# Project Snake 2025 🐍

**Snake** una versione giocabile da terminale del classico gioco Snake, realizzata in C++ con interfaccia testuale (ncurses). Include livelli progressivi, ranking, bonus, animazioni ASCII e una gestione avanzata delle statistiche di gioco.

---

## Struttura delle cartelle

- **src/**  
  Contiene tutti i file sorgente (.cpp) del gioco, suddivisi per funzionalità (menu, snake, livelli, ranking, ecc).

- **include/**  
  Contiene tutti i file header (.h) con le dichiarazioni delle classi e delle funzioni principali.

- **resources/**  
  Contiene tutte le ASCII art presenti nel gioco e le relative funzioni per stamparle.

- **build/**  
   Cartella dove vengono generati gli eseguibili o i file oggetto dopo la compilazione. Se non presente verrà genereta prima della compilazione.

---

## Come avviare il gioco

1. **Assicurarsi di avere installato le librerie ncurses:**
    > Ubunto/Debian
   ```sh
   sudo apt install libncurses-dev
   ```
   > MacOS
   ```sh
   brew install ncurses
   ```
2. **Assicurarsi di avere installato le librerie cmake (facoltativo):**
    > Ubunto/Debian
   ```sh
   sudo apt install cmake
   ```
   > MacOS
   ```sh
   brew install cmake
   ```

3. **Compila il progetto con cmake (consigliato):**   
    Dalla cartella principale del progetto, eseguire:
   ```sh
   mkdir build
   cd build
   cmake ..
   make
   ```
   > Questi comandi creano una cartella ed accedono ad essa. Questa conterrà tutti i file di compilazione compreso l'eseguibile.

4. **Compilazione diretta senza cmake:**  
    Si consiglia comunque di creare la cartella buld.
    ```sh
    mkdir build
    cd build
    g++ ../main.cpp ../src/*.cpp ../resources/ASCIIart.cpp -lncurses -o Snake
    ```

5.  **Avvia il gioco (compatibile con entrambe le versioni di compilazione):**  
     Dalla cartella build
    ```sh
     ./Snake
     ```
---

## Gruppo

Davide Gamberini, Mattia Graziani, Samuele Grillini
