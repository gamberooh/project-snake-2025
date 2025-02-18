#ifndef UTILITY_H
#define UTILITY_H

//personalized data structure
namespace utl {
    struct Position {
        int x, y;
        void add(Position a);
    };

    struct posNode{
        Position pos;
        posNode *next;
        posNode *prev;
    };

    typedef posNode* p_posNode;

    struct DoubleLinkedList{
        p_posNode head;
        p_posNode tail;

        DoubleLinkedList();
        p_posNode create_node(Position pos);
        void insert(int x, int y);
        void moveLastFront();
        bool isMember(Position val) const;
    };
}
#endif //UTILITY_H
