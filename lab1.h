#include <iostream>
#include <locale.h>
#include <string>
//Вариант 3 
struct CD {
    CD *prev = NULL;
    CD *next = NULL;
    std::string type = "";
    std::string title = "";
    long totalMemory = 0;
    long inuseMemory = 0;
    bool isAppending = false;
    bool isRewriting = false;
    
    int numSections = 1;
};
struct DataCD : CD {};

struct PlayCD : CD {
    long duration = 0;
    std::string author = "";
};

struct AudioCD : PlayCD {};

struct MP3CD : PlayCD {};

struct VideoCD : PlayCD {};

struct DVD : PlayCD {
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
int inputBaseCD(CD &item); //done
int inputPlayCD(PlayCD &item); //done
int sortByTitle(List *list); //done
int sortByDuration(List *list); //done
int sortByInuseMemory(List *list); //done
int searchByType(List *list, std::string search); //done
int searchByAuthor(List *list, std::string search); //done
CD *searchBy();//По достаточному количеству свободной памяти
//For help
int changeNeighbor(CD &thisItem, CD &nextItem);
int printInformationItem(CD *item);
int printInformationItem(List *list, int index);
