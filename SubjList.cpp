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
            break;
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
            cout << "Press any key for contien" << endl;
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
            itemSearch = (BaseCD *)list->getPointerByIndex(indexSearch);
            if (itemSearch) {
                cout << "Found pointer: " << itemSearch << endl;
                getchar(); getchar();
                return 1; //Если не НУЛ, то возвращаем, что успешно
            }
            else return 0; //Иначе, что НУЛ
        }
        case 5: {
            int index;
            BaseCD *result = NULL;
            list->print();
            cout << "Enter index for removing: ";
            cin >> index;
            result = (BaseCD *)list->getPointerByIndex(index);
            if (result == NULL) return 0;

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
            result = (BaseCD *)list->removeItem(index);
            if (result == NULL) return 0;

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
            BaseCD *itemLoc = new BaseCD;
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
            //Есть возможность использовать все найденные элементы, так как функция возвращает массив указателей
            ((SubjList *)list)->searchByArtist(artist);
            getchar(); getchar();
            break;
        }
        case 12: {
            long memorySearching;
            cout << "Enter amount of unused memory: ";
            cin >> memorySearching;
            //функции поиска должны возвращать массив указателей
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
            ((SubjList *)list)->printInformationItem(index);
            getchar(); getchar();
            break;
        }
        default:
            break;
    }
    return 1;
}

BaseCD *createCD(int pickType) {
    BaseCD *itemLoc;
    switch (pickType)
    {
        case 1: {
            itemLoc = (BaseCD *)(new DataCD());
            inputBaseCD(*itemLoc);
            break;
        }
        case 2: {
            itemLoc = (BaseCD *)(new AudioCD());
            inputAudioCD(*((AudioCD *)itemLoc));
            break;
        }
        case 3: {
            itemLoc = (BaseCD *)(new MP3CD());
            inputAudioCD(*((AudioCD *)itemLoc));
            break;
        }
        case 4: {
            itemLoc = (BaseCD *)(new VideoCD());
            inputVideoCD(*((VideoCD *)itemLoc));
            break;
        }
        case 5: {
            itemLoc = (BaseCD *)(new DVD);
            inputDVD(*((DVD *)itemLoc));
            break;
        }
        default:
            NULL;
    }
    return itemLoc;
}
//Input base information about BaseCD
int inputBaseCD(BaseCD &item) {
    if (&item == NULL) return -1;

    string title;
    long capacity;
    bool status;
    cout << "Title: ";
    cin >> title;
    item.setTitle(title);
    cout << "Total memory: ";
    cin >> capacity;
    item.setTotalMemory(capacity);
    cout << "Inuse memory: ";
    cin >> capacity;
    item.setInuseMemory(capacity);
    if (item.getInuseMemory() > item.getTotalMemory()) item.setInuseMemory(item.getTotalMemory());
    cout << "Is appending (true[1]/false[0]): ";
    cin >> status;
    item.setIsAppending(status);
    cout << "Is rewriting (true[1]/false[0]): ";
    cin >> status;
    item.setIsRewriting(status);
    item.setType(TData);
    return 1;
}

int inputAudioCD(AudioCD &item) {
    if (&item == NULL) return -2;

    inputBaseCD(item);
    string artist;
    int duration;
    cout << "Artist: ";
    cin >> artist;
    item.setArtist(artist);
    cout << "Duration(seconds): ";
    cin >> duration;
    item.setDuration(duration);
    item.setType(TAudio);
    return 1;
}

int inputMP3CD(MP3CD &item) {
    if (&item == NULL) return -2;

    inputAudioCD((AudioCD &)item);
    item.setType(TMP3);
    return 1;
}

int inputVideoCD(VideoCD &item) {
    if (&item == NULL) return -2;

    inputBaseCD((BaseCD &)item);
    string director;
    long duration;
    cout << "Director: ";
    cin >> director;
    item.setDirector(director);
    cout << "Duration(seconds): ";
    cin >> duration;
    item.setDuration(duration);
    item.setType(TVideo);
    return 1;
}

int inputDVD(DVD &item) {
    if (&item == NULL) return -2;

    inputVideoCD((VideoCD &)item);
    cout << "Enter amount sections: ";
    int number;
    cin >> number;
    item.setNumSections(number);
//    item.numSections;
    item.setType(TDVD);
    return 1;
}

TypeCD BaseCD::getType() {
    return this->type;
}

void BaseCD::setType(TypeCD typeCd) {
    this->type = typeCd;
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
    (capacity < 0) ? this->totalMemory = 0 : this->totalMemory = capacity;
}

long BaseCD::getInuseMemory() {
    return this->inuseMemory;
}

void BaseCD::setInuseMemory(long capacity) {
    (capacity < 0) ? this->inuseMemory = 0 : this->inuseMemory = capacity;
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

void BaseCD::setIsRewriting(bool isRewriting) {
    this->isRewriting = isRewriting;
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

std::string VideoCD::getDirector() {
    return this->director;
}

void VideoCD::setDirector(std::string name) {
    this->director = name;
}

int DVD::getNumSections() {
    return this->numSections;
}

void DVD::setNumSections(int number) {
    (number < 0) ? this->numSections = 0 : this->numSections = number;
}

void SubjList::printExtended() {
    if (this->getHead() == NULL) {
        cout << "Empty" << endl;
        return;
    }
    for (int i = 0; i < this->count(); i++) {
        cout << "\t\t\t\tElement " << i << endl;
        this->printInformationItem(i);
    }
}

BaseCD** SubjList::searchByType(TypeCD search) {
    cout << "Found items: " << endl;
    int amount = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < this->count(); i++) {
        BaseCD * item = (BaseCD *)this->getPointerByIndex(i);
        if (item->getType() == search) {
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
        BaseCD * item = (BaseCD *)this->getPointerByIndex(i);
        if (item->getType() == TAudio || item->getType() == TMP3) {
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
        BaseCD * item = (BaseCD *)this->getPointerByIndex(i);
        if (item->getType() == TVideo || item->getType() == TDVD) {
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
        BaseCD * item = (BaseCD *)this->getPointerByIndex(i);
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

int SubjList::printInformationItem(BaseCD *item) {
    if (item == NULL) {
        return 0;
    }

    cout << "Title: " << item->getTitle() << endl << "Type: " << item->getType() << endl
         << "Total memory(mb): " << item->getTotalMemory() << endl
         << "Inuse memory(mb): " << item->getInuseMemory() << endl
         << "Is appending: " << item->getIsAppending() << endl
         << "Is rewriting: " << item->getIsRewriting1() << endl;

    if (item->getType() == TypeCD::TAudio || item->getType() == TypeCD::TMP3) {
        cout << "Artist: " << ((AudioCD *)item)->getArtist() << endl
             << "Duration(seconds): " << ((PlayCD *)item)->getDuration() << endl;
        return 1;
    }
    if (item->getType() == TypeCD::TVideo || item->getType() == TypeCD::TDVD) {
        cout << "Artist: " << ((AudioCD *)item)->getArtist() << endl
             << "Duration(seconds): " << ((PlayCD *)item)->getDuration() << endl;
    }
    if (item->getType() == TypeCD::TDVD) {
        cout << "Available sections: " << ((DVD *)item)->getNumSections() << endl;
    }
    return 1;
}

int SubjList::printInformationItem(int index) {
    ListItem *item = this->getPointerByIndex(index);
    return printInformationItem((BaseCD *)item);
}

bool SubjList::shouldSwap(BaseCD *obj1, BaseCD *obj2, TypeSort type) {
    switch (type)
    {
        case TypeSort::Title: {
            return obj1->getTitle().compare(obj2->getTitle()) > 0;
        }
        case TypeSort::InuseMemory: {
            return obj1->getInuseMemory() > obj2->getInuseMemory();
        }
        case TypeSort::Duration: {
            if (obj1->getType() == TypeCD::TData && obj2->getType() != TypeCD::TData)
                return true;

            if (obj1->getType() == TypeCD::TData && obj2->getType() == TypeCD::TData)
                return false;

            if (((PlayCD *)obj1)->getDuration() > ((PlayCD *)obj2)->getDuration())
                return true;
            else
                return false;
        }

        default:
            break;
    }
}

int SubjList::changeNeighbor(BaseCD &thisItem, BaseCD &nextItem) {
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

int SubjList::sort(TypeSort type) {
    for (int j = 0; j < this->count(); j++) {
        for (int i = 0; i < this->count() - 1; i++) {
            BaseCD *thisItem = (BaseCD *)this->getPointerByIndex(i);
            BaseCD *nextItem = (BaseCD *)this->getPointerByIndex(i+1);
            //If getNext() item nearer than this item than change their positions
            if (shouldSwap(thisItem, nextItem, type)) {
                changeNeighbor(*thisItem, *nextItem);

                if (i == 0) this->setHead(nextItem);
                if (i == this->count() - 1) this->setTail(thisItem);
            }
        }
    }
    return 0;
}