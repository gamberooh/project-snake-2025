#include "../include/utility.h"
#include "../include/singleLevel.h"
#include "../include/singleRank.h"
#include <iostream>

//Position
void utl::Position::add(const Position add) {
    x += add.x;
    y += add.y;
}

utl::Position::Position(const int x, const int y) {
    this->x = x;
    this->y = y;
}

utl::Position::Position() {
    this->x = 0;
    this->y = 0;
}


bool utl::Position::operator==(const Position &other) const {
    return (other.x == this->x && other.y == this->y);
}

//General DLL
template <typename T>
utl::DoubleLinkedList<T>::DoubleLinkedList() : head(NULL), tail(NULL), size(0) {}

template<typename T>
void utl::DoubleLinkedList<T>::newNodeAtTheEnd() {
    auto newNode = new Node<T>;
    if(head == NULL) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

//Position DLL
typedef utl::Node<utl::Position>* p_posNode;

template class utl::DoubleLinkedList<utl::Position>;

p_posNode createNode(utl::Position node) {
    auto newNode = new utl::Node<utl::Position>;
    newNode->value = node;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void utl::DoubleLinkedListPos::insert(const int x, const int y) {
    Position pos(x, y);  //pos{} initialize all parameters to default value
    p_posNode newNode = createNode(pos);

    if(head == NULL){
        tail = newNode;
        head = tail;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
}

void utl::DoubleLinkedListPos::moveLastFront() {
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

bool utl::DoubleLinkedListPos::isMember(Position val) const {
    p_posNode tmp = head;
    while(tmp != NULL) {
        if(tmp->value == val) return true;
        tmp = tmp->next;
    }
    return false;
}

template class utl::DoubleLinkedList<SingleLevel>;

//SingleRanking DDL
template class utl::DoubleLinkedList<SingleRank>;