#include "list.h"

List::List() {
    this->head = NULL;
    this->tail = NULL;
}

List::~List() {
    delete this;
}

ListItem* List::GetHead() {
    return this->head;
}

void List::SetHead(ListItem *item) {
    this->head = item;
}

ListItem* List::GetTail() {
    return this->tail;
}

void List::SetTail(ListItem *item) {
    this->tail = item;
}

ListItem* ListItem::GetNext() {
    return this->next;
}

void ListItem::SetNext(ListItem *item) {
    this->next = item;
}

ListItem* ListItem::GetPrev() {
    return this->prev;
}

void ListItem::SetPrev(ListItem *item) {
    this->prev = item;
}