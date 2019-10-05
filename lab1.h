#include <iostream>
#include <locale.h>
#include <string.h>
//Вариант 3 
struct CD {
    CD *prev = NULL;
    CD *next = NULL;
    string title = NULL;
    long totalMemory = 0;
    long inuseMemory = 0;
    bool isAppending = false;
    bool isRewriting = false;
    
    int numSections = 1;
};
struct DataCD : CD {};

struct AudioCD : CD {
    long duration = 0;
    string artist = NULL;
};

struct MP3CD : AudioCD {};

struct VideoCD : CD {
    string director = NULL;
    int duration = 0; 
};

struct DVD : VideoCD {
    int numSections = 1;
};

struct List {
    CD *head = NULL;
    CD *tail = NULL;
};

//возвращаемое значение нужно для отладки
int addItem(List *list, CD *item);
void printList(List *list);
int countList(List *list);
int getIndexByPointer(List *list, CD *search);
CD* getPointerByIndex(List *list, int index = 0);
int deleteItem(List *list, int index);
CD* removeItem(List *list, int index);
int clearList(List *list);
int insertItem(List *list, CD *item, int index);
int menu(List *list);
//Требуют реализации
int sortByTitle(List *list);
int sortByDuration(List *list);
int sortByInuseMemory(List *list);
CD *searchByType(List *list, string search);
CD *searchByAuthor(List *list, string search);
CD *searchBy();//По достаточному количеству свободной памяти
