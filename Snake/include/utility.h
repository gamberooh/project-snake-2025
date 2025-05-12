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
