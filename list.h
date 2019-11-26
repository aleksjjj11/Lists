#include <iostream>

#ifndef LIST_LISTITEM_H
#define LIST_LISTITEM_H

class List;

class ListItem {
private:
    ListItem *prev;
    ListItem *next;
    List *list;
public:
    ListItem();
    ~ListItem();
    ListItem *getPrev();
    ListItem *getNext();
    void setList(List *list);
    void setPrev(ListItem *item = NULL);
    void setNext(ListItem *item = NULL);
};
#endif

#ifndef LIST_LIST_H
#define LIST_LIST_H
class List {
private:
    ListItem *head;
    ListItem *tail;
public: 
    ListItem *getHead();
    ListItem *getTail();
    List();
    ~List();
    void setHead(ListItem *item = NULL);
    void setTail(ListItem *item = NULL);
    int addItem(ListItem *item);
    void print();
    int count();
    int getIndexByPointer(ListItem *search);
    ListItem* getPointerByIndex(int index = 0);
    int deleteItem(int index);
    ListItem* removeItem(int index);
    int clear();
    int insertItem(ListItem *item, int index);

    virtual ListItem *operator [](int index);
};
#endif