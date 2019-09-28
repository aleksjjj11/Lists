#include <iostream>
#include <locale.h>

struct ListItem{
    ListItem *prev = NULL;
    ListItem *next = NULL;    
};

struct List {
    ListItem *head = NULL;
    ListItem *tail = NULL;
};

//возвращаемое значение нужно для отладки
int addItem(List *list, ListItem *item);
void printList(List *list);
int countList(List *list);
int getIndexByPointer(List *list, ListItem *search);
ListItem* getPointerByIndex(List *list, int index = 0);
int deleteItem(List *list, int index);
ListItem* removeItem(List *list, int index);
int clearList(List *list);
int insertItem(List *list, ListItem *item, int index);
int menu(List *list);
int sortBy(List *list);