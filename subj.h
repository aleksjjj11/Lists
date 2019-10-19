#include <locale.h>
#include <string>
#include "list.h"

//Вариант 3 
enum TypesCD {
    TData = 0,
    TAudio = 1,
    TMP3 = 2,
    TVideo = 3,
    TDVD = 4
};

enum TypeSort {
    Title = 0,
    InuseMemory = 1,
    Duration = 2
};

struct BaseCD : ListItem {
    //todo type должен быть enum //done
    TypesCD type;
    std::string title = "";
    long totalMemory = 0;
    long inuseMemory = 0;
    bool isAppending = false;
    bool isRewriting = false;
};
struct DataCD : BaseCD {};

// todo разделить автора и режиссера //done
struct PlayCD : BaseCD {
    long duration = 0;
};

struct AudioCD : PlayCD {
    std::string artist = "";
};

struct MP3CD : AudioCD {};

struct VideoCD : PlayCD {
    std::string director = "";
};

struct DVD : VideoCD {
    int numSections = 1;
};

//возвращаемое значение нужно для отладки
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
int menu(List *list);
//Требуют реализации
// добавить input на все дочерние структуры //done
BaseCD *createCD(int pickType);
int inputBaseCD(BaseCD &item); //done
int inputAudioCD(AudioCD &item); //done mb
int inputVideoCD(VideoCD &item); //done mb
int inputDVD(DVD &item); //done
int inputMP3CD(MP3CD &item);
int sort(List *list, TypeSort type);
BaseCD **searchByType(List *list, TypesCD search); //done
BaseCD **searchByArtist(List *list, std::string search); //done
BaseCD **searchByDirector(List *list, std::string search); //done
BaseCD **searchByUnusedMemory(List *list, int search);//По достаточному количеству свободной памяти
//For help
//swap
int changeNeighbor(BaseCD &thisItem, BaseCD &nextItem);
int printInformationItem(BaseCD *item);
int printInformationItem(List *list, int index);
bool shouldSwap(BaseCD *obj1, BaseCD *obj2, TypeSort type);
