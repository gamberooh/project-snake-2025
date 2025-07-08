#ifndef UTILITY_H
#define UTILITY_H

//personalized data structure
namespace utl {
    struct Position {
        int x, y;
        Position(int x, int y);
        Position();

        void add(Position add);
        bool operator==(const Position &other) const;
    };

    //Colors
    enum colorPair {
        BLACK,  // init_pair(0, COLOR_BLACK, -1);
        GREEN,   // init_pair(1, COLOR_GREEN, -1);
        RED,     // init_pair(2, COLOR_RED, -1);
        YELLOW,  // init_pair(3, COLOR_YELLOW, -1);
        WHITE,   // init_pair(4, COLOR_WHITE, -1);
        BLUE,     // init_pair(5, COLOR_BLUE, -1);
    };
    //COLORE SCRITTA _ COLORE SFONDO
    //se lo sfondo è trasparente nulla

    template <typename T>
    struct Node{
        T value;
        Node *next;
        Node *prev;
    };

    template <typename T>
    struct DoubleLinkedList{
        Node<T> *head;
        Node<T> *tail;
        DoubleLinkedList();
        void newNodeAtTheEnd();
    };

    struct DoubleLinkedListPos : DoubleLinkedList<Position> {
        void moveLastFront();
        void insert(int x, int y);
        bool isMember(Position val) const;
    };

}
#endif //UTILITY_H
