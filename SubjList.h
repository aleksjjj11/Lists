#include "list.h"

enum TypeCD {
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

class BaseCD : public ListItem {
private:
    TypeCD type;
    std::string title = "";
    long totalMemory = 0;
    long inuseMemory = 0;
    bool isAppending = false;
    bool isRewriting = false;
public:
    TypeCD getType();
    void setType(TypeCD typeCd);
    std::string getTitle();
    void setTitle(std::string str);
    long getTotalMemory();
    void setTotalMemory(long capacity);
    long getInuseMemory();
    void setInuseMemory(long capacity);
    bool getIsAppending();
    void setIsAppending(bool status);
    bool getIsRewriting1();
    void setIsRewriting(bool isRewriting);
};
class DataCD : public BaseCD {};

class PlayCD : public BaseCD {
private:
    long duration = 0;
public:
    long getDuration();
    void setDuration(long duration);
};

class AudioCD : public PlayCD {
private:
    std::string artist = "";
public:
    std::string getArtist();
    void setArtist(std::string name);
};

class MP3CD : public AudioCD {};

class VideoCD : public PlayCD {
private:
    std::string director = "";
public:
    std::string getDirector();
    void setDirector(std::string name);
};

class DVD : public VideoCD {
private:
    int numSections = 1;
public:
    int getNumSections();
    void setNumSections(int number);
};

int menu(List *list);
BaseCD *createCD(int pickType);
int inputBaseCD(BaseCD &item);
int inputAudioCD(AudioCD &item);
int inputVideoCD(VideoCD &item);
int inputDVD(DVD &item);
int inputMP3CD(MP3CD &item);

#ifndef LIST_SUBJLIST_H
#define LIST_SUBJLIST_H
class SubjList : public List {
public:
    void printExtended();
    int sort(TypeSort type);
    BaseCD **searchByType(TypeCD search);
    BaseCD **searchByArtist(std::string search);
    BaseCD **searchByDirector(std::string search);
    BaseCD **searchByUnusedMemory(int search);
    int printInformationItem(BaseCD *item);
    int printInformationItem(int index);
private:
    int changeNeighbor(BaseCD &thisItem, BaseCD &nextItem);
    bool shouldSwap(BaseCD *obj1, BaseCD *obj2, TypeSort type);
};
#endif
