#include "list.h"
#include <cassert>

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
    std::string title;
    long totalMemory;
    long inuseMemory;
    bool isAppending;
    bool isRewriting;
public:
    BaseCD();
    virtual void print();
    virtual TypeCD getType() = 0;
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
    virtual void input();
    bool operator <(BaseCD *item);
    bool operator >(BaseCD *item);
    bool operator ==(BaseCD *item);
    bool operator ==(TypeCD type);
    bool operator !=(TypeCD type);
};
class DataCD : public BaseCD {
public:
    TypeCD getType() override;
};

class PlayCD : public BaseCD {
private:
    long duration = 0;
public:
    long getDuration();
    void setDuration(long duration);
    bool operator >(PlayCD *item);
};

class AudioCD : public PlayCD {
private:
    std::string artist = "";
public:
    std::string getArtist();
    void setArtist(std::string name);
    void input() final;
    TypeCD getType() override;
    void print() override;
};

class MP3CD : public AudioCD {
public:
    TypeCD getType() override;
};

class VideoCD : public PlayCD {
private:
    std::string director = "";
public:
    std::string getDirector();
    void setDirector(std::string name);
    void input() override;
    TypeCD getType() override;
    void print() override;
};

class DVD : public VideoCD {
private:
    int numSections = 1;
public:
    int getNumSections();
    void setNumSections(int number);
    void input() final;
    TypeCD getType() override;
    void print() override;
};

int menu(List *list);
BaseCD *createCD(int pickType);
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
private:
    int swap(BaseCD &thisItem, BaseCD &nextItem);
    static bool shouldSwap(BaseCD *obj1, BaseCD *obj2, TypeSort type);
};
#endif
