#include "SubjList.h"

using namespace std;

int menu(List *list) {
    int chooseAction = 0;

    do {
#ifdef WIN32
        system("cls");
#else
        system("clear");
#endif
        cout << "1.  Add item" << endl
             << "2.  Count list" << endl
             << "3.  Get index by pointer" << endl
             << "4.  Get pointer by index" << endl
             << "5.  Delete item" << endl
             << "6.  Remove item" << endl
             << "7.  Clear list" << endl
             << "8.  Insert item" << endl
             << "9.  Print all list" << endl
             << "10. Searching by type" << endl
             << "11. Searching by artist" << endl
             << "12. Searching by unused memory" << endl
             << "13. Sorting by title" << endl
             << "14. Sorting by duration" << endl
             << "15. Sorting by inuse memory" << endl
             << "16. Searching by director" << endl
             << "20. Print all information item" << endl
             << "0. Exit" << endl;
        cin >> chooseAction;
    } while (chooseAction < 0 || chooseAction > 20);
    switch (chooseAction)
    {
        case 0:
            exit(0);
        case 1: {
            int chooseType = 0;
            do {
                rewind(stdin);
                cout << "Choose type of BaseCD, pls: \n1 - Data\n2 - Audio\n3 - MP3\n4 - Video\n5 - DVD" << endl;

            } while (scanf("%i", &chooseType) != 1 || chooseType > 5 || chooseType < 1);

            BaseCD *itemLoc = createCD(chooseType);
            //заменить на фабричную функцию Create

            list->addItem(itemLoc);
            printf("Added list item %p\n", itemLoc);
            list->print();
            return 0;
        }
        case 2: {
            int count = list->count();
            cout << "Count list = " << count << endl;
            cout << "Press any key for continue" << endl;
            getchar(); getchar();
            return 1;
        }
        case 3: {
            BaseCD *itemLoc;
            list->print();
            scanf("%p", &itemLoc);
            int result = list->getIndexByPointer(itemLoc);
            if (result > -1)
                cout << "Index = " << result;
            else
                cout << "Error: " << result;
            cout << "Press any key for contien" << endl;
            getchar(); getchar();
            return result;
        }
        case 4: {
            int indexSearch = 0;
            BaseCD *itemSearch = NULL;
            list->print();
            cout << "Enter index: ";
            cin >> indexSearch;
            try {
                itemSearch = (BaseCD *)(*list)[indexSearch];//(BaseCD *)list->getPointerByIndex(indexSearch);
                if (itemSearch == NULL) throw "Exception: using nullpointer";
                cout << "Found pointer: " << itemSearch << endl;
            } catch (char const* e) {
                cout << e << endl << "Try again" << endl;
                getchar(); getchar();
                return 0;
            }

            getchar(); getchar();
            return 1;
        }
        case 5: {
            int index;
            BaseCD *result = NULL;
            list->print();
            cout << "Enter index for removing: ";
            cin >> index;
            try {
                result = (BaseCD *)(*list)[index];
                if (result == NULL) throw "Exception: using nullpointer";
            } catch (char const* e) {
                cout << e << endl << "Try again" << endl;
                getchar(); getchar();
                return 0;
            }

            cout << "Deleted pointer - " << result << endl;
            list->deleteItem(index);
            list->print();
            return 1;
        }
        case 6: {
            int index;
            BaseCD *result = NULL;
            list->print();
            cout << "Enter index for removing: ";
            cin >> index;
            try {
                result = (BaseCD *)list->removeItem(index);
                if (result == NULL) throw "Exception: using nullpointer";
            } catch (char const* e) {
                cout << e << endl << "Try again" << endl;
                getchar(); getchar();
                return 0;
            }

            cout << "Removed pointer - " << result << endl;
            list->print();
            return 1;
        }
        case 7: {
            if (list->clear() == 1) {
                cout << "List was deleted." << endl;
                getchar(); getchar();
                return 1;
            } else {
                cout << "Attempt to delete null pointer." << endl;
                cout << "Press any key for contien" << endl;
                getchar(); getchar();
                return 0;
            }
        }
        case 8: {
            ListItem *itemLoc = new ListItem();
            int position = 0;
            list->print();
            cout << "Enter position for inserting: ";
            cin >> position;
            cout << "Inserting list item: " << itemLoc << endl;
            if (list->insertItem(itemLoc, position) == 0) {
                cout << "Attempt to insert null pointer." << endl;
                cout << "Press any key for contien" << endl;
                getchar(); getchar();
                return 0;
            }
            return 1;
        }
        case 9: {
           ((SubjList*)list)->printExtended();
            getchar(); getchar();
            break;
        }
        case 10: {
            int type;
            cout << "Choose type:\n0-Data\n1-Audio\n2-MP3\n3-Video\n4-DVD\nYour pick: ";
            cin >> type;
            ((SubjList *)list)->searchByType((TypeCD)type);
            getchar(); getchar();
            break;
        }
        case 11: {
            string artist;
            cout << "Enter artist: ";
            cin >> artist;
            ((SubjList *)list)->searchByArtist(artist);
            getchar(); getchar();
            break;
        }
        case 12: {
            long memorySearching;
            cout << "Enter amount of unused memory: ";
            cin >> memorySearching;
            ((SubjList *)list)->searchByUnusedMemory(memorySearching);
            getchar(); getchar();
            break;
        }
        case 13: {
            cout << "Before sorting" << endl;
            ((SubjList*)list)->printExtended();
            ((SubjList *)list)->sort(TypeSort::Title);
            cout << endl << "After sorting" << endl;
            ((SubjList*)list)->printExtended();
            getchar(); getchar();
            break;
        }
        case 14: {
            cout << "Before sorting" << endl;
            ((SubjList*)list)->printExtended();
            ((SubjList *)list)->sort(TypeSort::Duration);
            cout << endl << "After sorting" << endl;
            ((SubjList*)list)->printExtended();
            getchar(); getchar();
            break;
        }
        case 15: {
            cout << "Before sorting" << endl;
            ((SubjList*)list)->printExtended();
            ((SubjList *)list)->sort(TypeSort::InuseMemory);
            cout << endl << "After sorting" << endl;
            ((SubjList*)list)->printExtended();
            getchar(); getchar();
            break;
        }
        case 16: {
            string director;
            cout << "Enter director: ";
            cin >> director;
            ((SubjList *)list)->searchByDirector(director);
            getchar(); getchar();
            break;
        }
        case 20: {
            list->print();
            cout << "Enter index of item: ";
            int index;
            cin >> index;
            BaseCD *result;
            try {
                result = (BaseCD *)(*list)[index];
                if (result == NULL) throw "Exception: using nullpointer";
            } catch (char const* e) {
                cout << e << endl << "Try again" << endl;
                getchar(); getchar();
                return 0;
            }

            result->print();
            getchar(); getchar();
            break;
        }
        default:
            break;
    }
    return 1;
}

BaseCD *createCD(int pickType) {
    switch (pickType)
    {
        case 1: {
            DataCD *itemLoc = new DataCD();
            itemLoc->input();
            return itemLoc;
        }
        case 2: {
            AudioCD *itemLoc = new AudioCD();
            itemLoc->input();
            return itemLoc;
        }
        case 3: {
            MP3CD *itemLoc = new MP3CD();
            itemLoc->input();
            return itemLoc;
        }
        case 4: {
            VideoCD *itemLoc = new VideoCD();
            itemLoc->input();
            return itemLoc;
        }
        case 5: {
            DVD *itemLoc = new DVD;
            itemLoc->input();
            return itemLoc;
        }
        default:
            return NULL;
    }
}

bool BaseCD::operator <(BaseCD *item) {
    return this->inuseMemory < item->inuseMemory;
}

bool BaseCD::operator >(BaseCD *item) {
    return this->inuseMemory > item->inuseMemory;
}

bool BaseCD::operator ==(BaseCD *item) {
    return this->getInuseMemory() == item->getInuseMemory();
}

bool BaseCD::operator ==(TypeCD type) {
    return this->getType() == type;
}

bool BaseCD::operator !=(TypeCD type) {
    return this->getType() != type;
}

bool PlayCD::operator >(PlayCD *item) {
    return this->duration > item->getDuration();
}

void BaseCD::input() {
    long capacity;
    bool status;
    cout << "Title: ";
    cin >> title;
    cout << "Total memory: ";
    cin >> capacity;
    this->setTotalMemory(capacity);
    cout << "Inuse memory: ";
    cin >> capacity;
    this->setInuseMemory(capacity);
    cout << "Is appending (true[1]/false[0]): ";
    cin >> status;
    this->setIsAppending(status);
    cout << "Is rewriting (true[1]/false[0]): ";
    cin >> status;
    this->setIsRewriting(status);
}

void AudioCD::input() {
    BaseCD::input();
    string artist;
    int duration;
    cout << "Artist: ";
    cin >> artist;
    this->setArtist(artist);
    cout << "Duration(seconds): ";
    cin >> duration;
    this->setDuration(duration);
}

void VideoCD::input() {
    BaseCD::input();
    string director;
    long duration;
    cout << "Director: ";
    cin >> director;
    this->setDirector(director);
    cout << "Duration(seconds): ";
    cin >> duration;
    this->setDuration(duration);
}

void DVD::input() {
    VideoCD::input();
    cout << "Enter amount sections: ";
    int number;
    cin >> number;
    this->setNumSections(number);
}

std::string BaseCD::getTitle() {
    return this->title;
}

void BaseCD::setTitle(std::string str) {
    this->title = str;
}

long BaseCD::getTotalMemory() {
    return this->totalMemory;
}

void BaseCD::setTotalMemory(long capacity) {
    capacity < 0 ? this->totalMemory = 0 : this->totalMemory = capacity;
}

long BaseCD::getInuseMemory() {
    return this->inuseMemory;
}

void BaseCD::setInuseMemory(long capacity) {
    capacity < 0 ? this->inuseMemory = 0 : (capacity > this->totalMemory) ? this->inuseMemory = this->totalMemory : this->inuseMemory = capacity;
}

bool BaseCD::getIsAppending() {
    return this->isAppending;
}

void BaseCD::setIsAppending(bool status) {
    this->isAppending = status;
}

bool BaseCD::getIsRewriting1() {
    return this->isRewriting;
}

void BaseCD::setIsRewriting(bool value) {
    this->isRewriting = value;
}

BaseCD::BaseCD() {
    title = "";
    totalMemory = 0;
    inuseMemory = 0;
    isAppending = false;
    isRewriting = false;
}

void BaseCD::print() {
    printf("Title: %s\n", this->getTitle().data());
    printf("Type: %i\n", getType());
    printf("Total memory(mb): %li\n", getTotalMemory());
    printf("Inuse memory(mb): %li\n", getInuseMemory());
    printf("Is appending: %i\n", getIsAppending());
    printf("Is rewriting: %i\n", getIsRewriting1());
}

void PlayCD::setDuration(long duration) {
    (duration < 0) ? this->duration = 0 : this->duration = duration;
}

long PlayCD::getDuration() {
    return this->duration;
}

std::string AudioCD::getArtist() {
    return this->artist;
}

void AudioCD::setArtist(std::string name) {
    this->artist = name;
}

TypeCD AudioCD::getType() {
    return TAudio;
}

void AudioCD::print() {
    BaseCD::print();
    cout << "Artist: " << this->getArtist() << endl
         << "Duration(seconds): " << this->getDuration() << endl;
}

std::string VideoCD::getDirector() {
    return this->director;
}

void VideoCD::setDirector(std::string name) {
    this->director = name;
}

TypeCD VideoCD::getType() {
    return TVideo;
}

void VideoCD::print() {
    BaseCD::print();
    cout << "Artist: " << this->getDirector() << endl
         << "Duration(seconds): " << this->getDuration() << endl;
}

int DVD::getNumSections() {
    return this->numSections;
}

void DVD::setNumSections(int number) {
    (number < 0) ? this->numSections = 0 : this->numSections = number;
}

TypeCD DVD::getType() {
    return TDVD;
}

void DVD::print() {
    VideoCD::print();
    cout << "Available sections: " << this->getNumSections() << endl;
}

void SubjList::printExtended() {
    if (this->getHead() == NULL) {
        cout << "Empty" << endl;
        return;
    }
    for (int i = 0; i < this->count(); i++) {
        printf("\t\t\t\tElement %i\n", i);
        ((BaseCD*)((*this)[i]))->print();
    }
}

BaseCD** SubjList::searchByType(TypeCD search) {
    cout << "Found items: " << endl;
    int amount = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < this->count(); i++) {
        BaseCD * item; //= (BaseCD *)(*this)[i];//this->getPointerByIndex(i);
        try {
            item = (BaseCD *)(*this)[i];
            if (item == NULL) throw "Exception: using nullpointer";
        } catch (char const* e) {
            cout << e << endl << "Try again" << endl;
            getchar(); getchar();
            return 0;
        }
        if (*item == search) {
            if (amount == 0) {
                arrayCD[amount] = item;
            }
            arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(amount+1));
            arrayCD[amount] = item;

            printf("Index: %i - %p\n", i, item);
            amount++;
        }
    }
    if (amount == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

BaseCD** SubjList::searchByArtist(string search) {
    cout << "Found items: " << endl;
    int amount = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < this->count(); i++) {
        BaseCD * item = (BaseCD*)(*this)[i];//(BaseCD *)this->getPointerByIndex(i);
        if (*item == TAudio || *item == TMP3) {
            if (((AudioCD *)item)->getArtist() == search) {
                if (amount == 0) {
                    arrayCD[amount] = item;
                }
                arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(amount+1));
                arrayCD[amount] = item;

                printf("Index: %i - %p type: ", i, item);
                cout << item->getType() << endl;
                amount++;
                continue;
            }
        }

    }
    if (amount == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

BaseCD** SubjList::searchByDirector(string search) {
    cout << "Found items: " << endl;
    int amount = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < this->count(); i++) {
        BaseCD * item = (BaseCD*)(*this)[i];//(BaseCD *)this->getPointerByIndex(i);
        if (*item == TVideo || *item == TDVD) {
            if (((VideoCD *)item)->getDirector() == search) {
                if (amount == 0) {
                    arrayCD[amount] = item;
                }
                arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(amount+1));
                arrayCD[amount] = item;

                printf("Index: %i - %p type: ", i, item);
                cout << item->getType() << endl;
                amount++;
                continue;
            }
        }
    }
    if (amount == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

BaseCD** SubjList::searchByUnusedMemory(int search) {
    cout << "Found items: " << endl;
    int amount = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < this->count(); i++) {
        BaseCD * item = (BaseCD*)(*this)[i];//(BaseCD *)this->getPointerByIndex(i);
        if (item->getTotalMemory() - item->getInuseMemory() >= search) {
            if (amount == 0) {
                arrayCD[amount] = item;
            }
            arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(amount+1));
            arrayCD[amount] = item;

            printf("Index: %i - %p type: ", i, item);
            cout << item->getType() << endl;
            amount++;
            continue;
        }
    }

    if (amount == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

bool SubjList::shouldSwap(BaseCD *obj1, BaseCD *obj2, TypeSort type) {
    switch (type)
    {
        case TypeSort::Title: {
            return obj1->getTitle().compare(obj2->getTitle()) > 0;
        }
        case TypeSort::InuseMemory: {
            return obj1 > obj2;
        }
        case TypeSort::Duration: {
            if (*obj1 == TypeCD::TData && *obj2 != TypeCD::TData)
                return true;

            if (*obj1 == TypeCD::TData && *obj2 == TypeCD::TData)
                return false;

            return ((PlayCD *) obj1) > ((PlayCD *) obj2);
        }

        default:
            break;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"
int SubjList::swap(BaseCD &thisItem, BaseCD &nextItem) {
    BaseCD *med = (BaseCD *) nextItem.getNext();
    nextItem.setNext(&thisItem);
    thisItem.setNext(med);

    med = (BaseCD *) thisItem.getPrev();
    thisItem.setPrev(&nextItem);
    nextItem.setPrev(med);

    if (thisItem.getNext() != NULL) thisItem.getNext()->setPrev(&thisItem);
    if (nextItem.getPrev() != NULL) nextItem.getPrev()->setNext(&nextItem);

    return 1;
}
#pragma clang diagnostic pop

int SubjList::sort(TypeSort type) {
    for (int j = 0; j < this->count(); j++) {
        for (int i = 0; i < this->count() - 1; i++) {
            BaseCD *thisItem = (BaseCD*)(*this)[i];
            BaseCD *nextItem = (BaseCD*)(*this)[i+1];
            if (shouldSwap(thisItem, nextItem, type)) {
                swap(*thisItem, *nextItem);

                if (i == 0) this->setHead(nextItem);
                if (i == this->count() - 1) this->setTail(thisItem);
            }
        }
    }
    return 0;
}

TypeCD DataCD::getType() {
    return TData;
}

TypeCD MP3CD::getType() {
    return TMP3;
}

//todo exception array bounds