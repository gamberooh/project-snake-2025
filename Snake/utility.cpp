#include "utility.h"
#include <iostream>


void utl::Position::add(const Position a) {
    x += a.x;
    y += a.y;
}

utl::DoubleLinkedList::DoubleLinkedList() : head(NULL), tail(NULL) {}

utl::p_posNode utl::DoubleLinkedList::create_node(Position pos) {
    p_posNode newNode = new posNode;
    newNode->pos = pos;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void utl::DoubleLinkedList::insert(const int x, const int y) {
    utl::Position pos;
    pos.x = x;
    pos.y = y;
    p_posNode newnode = create_node(pos);

    if(head == NULL){
        tail = newnode;
        head = tail;
        newnode->next = NULL;
        newnode->prev = NULL;
    }
    else {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
    }
}

void utl::DoubleLinkedList::moveLastFront() {
    //nessuno o un solo elemento
    if(head == NULL || head == tail) return;

    p_posNode tmp = tail->prev;
    tmp->next = NULL;

    tail->next = head;
    tail->prev = NULL;
    head->prev = tail;
    head = tail;

    tail = tmp;
}

bool utl::DoubleLinkedList::isMember(Position const val) const {
    p_posNode tmp = head;
    while(tmp != NULL) {
        if(tmp->pos.x == val.x && tmp->pos.y == val.y) return true;
        tmp = tmp->next;
    }
    return false;
}


