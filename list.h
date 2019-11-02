#include <iostream>

class ListItem {
private:
    ListItem *prev = NULL;
    ListItem *next = NULL;
public:
    ListItem *GetPrev();
    ListItem *GetNext();
    void SetPrev(ListItem *item = NULL);
    void SetNext(ListItem *item = NULL);
    
    int addItem(List *list, ListItem *item);
    void printList(List *list);
    void printExtendedList(List *list);
    int countList(List *list);
    int getIndexByPointer(List *list, ListItem *search);
    ListItem* getPointerByIndex(List *list, int index = 0);
    int deleteItem(List *list, int index);
    ListItem* removeItem(List *list, int index);
    int clearList(List *list);
    int insertItem(List *list, ListItem *item, int index);
};
class List {
private:
    ListItem *head = NULL;
    ListItem *tail = NULL;
public: 
    ListItem *GetHead();
    ListItem *GetTail();
    void SetHead(ListItem *item = NULL);
    void SetTail(ListItem *item = NULL);
};
