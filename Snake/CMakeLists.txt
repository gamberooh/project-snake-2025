cmake_minimum_required(VERSION 3.26)
project(Snake)

# Specifica lo standard C++ da utilizzare
set(CMAKE_CXX_STANDARD 20)

# Trova la libreria NCurses
find_package(Curses REQUIRED)
# Aggiungi le directory di inclusione di NCurses
include_directories(${CURSES_INCLUDE_DIR})

# Aggiungi l'eseguibile
add_executable(Snake main.cpp
                game.cpp
                utility.cpp
                snake.cpp
                arena.cpp
                food.cpp
                menu.cpp
                ranking.cpp
                levels.cpp
)

# Collega le librerie NCurses all'eseguibile
target_link_libraries(Snake ${CURSES_LIBRARIES})