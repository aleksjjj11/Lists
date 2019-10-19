#include "subj.h"

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
        
        return addItem(list, itemLoc);
    }
    case 2: {
        int count = countList(list);
        cout << "Count list = " << count << endl;
        cout << "Press any key for contien" << endl;
        getchar(); getchar();
        return 1;
    }
    case 3: {
        BaseCD *itemLoc;
        printList(list);
        scanf("%p", &itemLoc);
        int result = getIndexByPointer(list, itemLoc);
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
        printList(list);
        cout << "Enter index: ";
        cin >> indexSearch;
        itemSearch = (BaseCD *)getPointerByIndex(list, indexSearch);
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
        printList(list);
        cout << "Enter index for removing: ";
        cin >> index;
        result = (BaseCD *)getPointerByIndex(list, index);
        if (result == NULL) return 0;
        
        cout << "Deleted pointer - " << result << endl;
        deleteItem(list, index);
        printList(list);
        return 1;
    }
    case 6: {
        int index;
        BaseCD *result = NULL;
        printList(list);
        cout << "Enter index for removing: ";
        cin >> index;
        result = (BaseCD *)removeItem(list, index);
        if (result == NULL) return 0;
        
        cout << "Removed pointer - " << result << endl;
        printList(list);
        return 1;
    }
    case 7: {
        if (clearList(list) == 1) {
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
        printList(list);
        cout << "Enter position for inserting: ";
        cin >> position;
        cout << "Inserting list item: " << itemLoc << endl;
        if (insertItem(list, itemLoc, position) == 0) {
            cout << "Attempt to insert null pointer." << endl;
            cout << "Press any key for contien" << endl;
            getchar(); getchar();
            return 0;
        }
        return 1;
    }
    case 9: {
        printExtendedList(list);
        getchar(); getchar();
        break;
    }
    case 10: {
        int type;
        cout << "Choose type:\n0-Data\n1-Audio\n2-MP3\n3-Video\n4-DVD\nYour pick: "; 
        cin >> type;
        searchByType(list, (TypesCD)type);
        getchar(); getchar();
        break;
    }
    case 11: {
        string artist;
        cout << "Enter artist: "; 
        cin >> artist;
        //Есть возможность использовать все найденные элементы, так как функция возвращает массив указателей
        searchByArtist(list, artist);
        getchar(); getchar();
        break;
    }
    case 12: {
        long memorySearching;
        cout << "Enter amount of unused memory: ";
        cin >> memorySearching;
        //функции поиска должны возвращать массив указателей
        searchByUnusedMemory(list, memorySearching);
        getchar(); getchar();
        break;
    }
    case 13: {
        cout << "Before sorting" << endl; 
        printExtendedList(list);
        sort(list, TypeSort::Title);        
        cout << endl << "After sorting" << endl;
        printExtendedList(list);
        getchar(); getchar();
        break;
    }
    case 14: {
        cout << "Before sorting" << endl; 
        printExtendedList(list);
        sort(list, TypeSort::Duration);
        cout << endl << "After sorting" << endl;
        printExtendedList(list);
        getchar(); getchar();
        break;
    }
    case 15: {
        cout << "Before sorting" << endl; 
        printExtendedList(list);
        sort(list, TypeSort::InuseMemory);
        cout << endl << "After sorting" << endl;
        printExtendedList(list);
        getchar(); getchar();
        break;
    }
    case 16: {
        string director;
        cout << "Enter director: "; 
        cin >> director;
        searchByDirector(list, director);
        getchar(); getchar();
        break;
    }
    case 20: {
        printList(list);
        cout << "Enter index of item: ";
        int index;
        cin >> index;
        printInformationItem(list, index);
        getchar(); getchar();
        break;
    }
    default:
        break;
    }
    return 1;
}

int addItem(List *list, ListItem *item) {
    if (list == NULL) return -1;
    if (item == NULL) return -2;
    
    if (list->head == NULL) {
        list->head = item;
        list->tail = item;
        item->prev = NULL;
    } else {
        item->prev = list->tail;
        list->tail->next = item;

        list->tail = item;
    }
        item->next = NULL;
    printf("Added list item %p\n", item);
    printList(list);
    return 1;
}

void printList(List *list) {
    if (list == NULL || list->head == NULL) {
        cout << "List empty." << endl; 
        cout << "Press any key for contien" << endl;
        return;
    }
    BaseCD *med = (BaseCD *)list->head;
    int i = 0;
    do {
        cout << i << ".";
        if (med->prev != NULL) 
            cout << "\t\t\t" << ((BaseCD *)med->prev)->title << "\t\t\t";
        else 
            cout << "\t\t\t" << "NULL" << "\t\t\t";   

        if (med != NULL)
            cout << med->title << "\t\t\t";
        else 
            cout << "NULL" << "\t\t\t";
        
        if (med->next != NULL)
            cout << ((BaseCD *)med->next)->title << endl; 
        else 
            cout << "NULL" << endl; 

        med = (BaseCD *)med->next;
        i++;
    } while (med != NULL);
}

int countList(List *list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }
    int count = 0;
    ListItem *med = list->head;
    do {
        count++;
        med = med->next;
    } while (med != NULL);
    return count;
}

int getIndexByPointer(List *list, ListItem *search) {
    if (list == NULL) return -1;
    if (search == NULL) return -2;
    ListItem *med = list->head;
    int count = countList(list);
    for(int index = 0; med; index++) {
        if (med == search) return index;
        med = med->next;
    }
    return -3;
}

ListItem* getPointerByIndex(List *list, int index) {
    if (list == NULL) return NULL;
    if (index < 0 || index > countList(list)) return NULL;
    int i = 0;
    ListItem *med = list->head;
    while (i < index && med != NULL) {
        i++;
        med = med->next;
    }   
    return med;
}

ListItem* removeItem(List *list, int index) {
    if (list == NULL) return NULL;
    if (index < 0 || index > countList(list)) return NULL;

    BaseCD *item = (BaseCD *)getPointerByIndex(list, index);
    if (item == NULL) return NULL;

    if (countList(list) == 1) {
        list->head = NULL;
        list->tail = NULL;
        return item;
    }

    if (item == list->head) {
        list->head = item->next;
        item->next->prev = NULL;
        return item;        
    }
    if (item == list->tail) {
        list->tail = item->prev;
        item->prev->next = NULL;
        return item;
    }

    item->prev->next = item->next;
    item->next->prev = item->prev;
    return item;
}

int deleteItem(List *list, int index) {
    delete removeItem(list, index);
    return 1;
}

int clearList(List *list) {
    if (list == NULL || list->head == NULL) return 0;

    BaseCD *med = (BaseCD *)list->tail;
    while (med) {
        //todo использовать функцию deleteitem
        BaseCD *item = (BaseCD *)med->prev;
        deleteItem(list, countList(list) - 1);
        med = item;
    }
    delete list;
    return 1;
}

int insertItem(List *list, ListItem *item, int index) {

    if (index >= countList(list)){
        addItem(list,item);
        return 1;
    }

    ListItem *pointer = getPointerByIndex(list, index);

    if (pointer == NULL) return 0;

    if (pointer == list->head) {
        list->head = item;

        pointer->prev = item;
        item->next = pointer;
        item->prev = NULL;
        cout << "Pointer " << item << " was successfully inserted." << endl;
        printList(list);
        return 1;
    }

    item->prev = pointer->prev;
    item->next = pointer;

    pointer->prev->next = item;
    pointer->prev = item;
    cout << "Pointer " << item << " was successfully inserted." << endl;
    printList(list);
    return 1;
}

BaseCD *createCD(int pickType) {
    BaseCD *itemLoc;
    switch (pickType)
        {
        case 1: {
            itemLoc = new DataCD();
            inputBaseCD(*itemLoc);
            break;
        }
        case 2: {
            itemLoc = new AudioCD;
            inputAudioCD(*((AudioCD *)itemLoc));
            break;
        }
        case 3: {
            itemLoc = new MP3CD;
            inputAudioCD(*((AudioCD *)itemLoc));
            break;
        }
        case 4: {
            itemLoc = new VideoCD;
            inputVideoCD(*((VideoCD *)itemLoc));
            break;
        }
        case 5: {
            itemLoc = new DVD;
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

    cout << "Title: "; 
    cin >> item.title;
    cout << "Total memory: "; 
    cin >> item.totalMemory;
    cout << "Inuse memory: "; 
    cin >> item.inuseMemory;
    if (item.inuseMemory > item.totalMemory) item.inuseMemory = item.totalMemory;
    cout << "Is appending (true[1]/false[0]): "; 
    cin >> item.isAppending;
    cout << "Is rewriting (true[1]/false[0]): "; 
    cin >> item.isRewriting;
    item.type = TData;
    return 1;
}

int inputAudioCD(AudioCD &item) {
    if (&item == NULL) return -2;
    
    inputBaseCD((BaseCD &)item);
    cout << "Artist: "; 
    cin >> item.artist;
    cout << "Duration(seconds): "; 
    cin >> item.duration;
    item.type = TAudio;
    return 1;
}

int inputMP3CD(MP3CD &item) {
    if (&item == NULL) return -2;

    inputAudioCD((AudioCD &)item);
    item.type = TMP3;
    return 1;
}

int inputVideoCD(VideoCD &item) {
    if (&item == NULL) return -2;

    inputBaseCD((BaseCD &)item);
    cout << "Director: "; 
    cin >> item.director;
    cout << "Duration(seconds): "; 
    cin >> item.duration;
    item.type = TVideo;
    return 1;
}

int inputDVD(DVD &item) {
    if (&item == NULL) return -2;

    inputVideoCD((VideoCD &)item);
    cout << "Enter amount sections: "; 
    cin >> item.numSections;
    item.type = TDVD;
    return 1;
}

BaseCD **searchByType(List *list, TypesCD search) {
    if (list == NULL) return NULL;

    cout << "Found items: " << endl;
    int count = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < countList(list); i++) {
        BaseCD * item = (BaseCD *)getPointerByIndex(list, i);
        if (item->type == search) {
            if (count == 0) {
                arrayCD[count] = item;
            }
            arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(count+1));
            arrayCD[count] = item;
            
            printf("Index: %i - %p\n", i, item);
            count++;
        }
    }
    if (count == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

BaseCD **searchByArtist(List *list, string search) {
    if (list == NULL) return NULL;

    cout << "Found items: " << endl;
    int count = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < countList(list); i++) {
        BaseCD * item = (BaseCD *)getPointerByIndex(list, i);
        if (item->type == TAudio || item->type == TMP3) {
            if (((AudioCD *)item)->artist == search) {
                if (count == 0) {
                    arrayCD[count] = item;
                }
                arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(count+1));
                arrayCD[count] = item;

                printf("Index: %i - %p type: ", i, item);
                cout << item->type << endl;
                count++;
                continue;
            }
        }
        
    }
    if (count == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

BaseCD **searchByDirector(List *list, std::string search) {
    if (list == NULL) return NULL;

    cout << "Found items: " << endl;
    int count = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < countList(list); i++) {
        BaseCD * item = (BaseCD *)getPointerByIndex(list, i);
        if (item->type == TVideo || item->type == TDVD) {
            if (((VideoCD *)item)->director == search) {
                if (count == 0) {
                    arrayCD[count] = item;
                }
                arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(count+1));
                arrayCD[count] = item;

                printf("Index: %i - %p type: ", i, item);
                cout << item->type << endl;
                count++;
                continue;
            }
        }
        
    }
    if (count == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

BaseCD ** searchByUnusedMemory(List *list, int search) {
    if (list == NULL) return NULL;

    cout << "Found items: " << endl;
    int count = 0;
    BaseCD **arrayCD = (BaseCD **)malloc(sizeof(BaseCD *));

    for (int i = 0; i < countList(list); i++) {
        BaseCD * item = (BaseCD *)getPointerByIndex(list, i);
        if (item->totalMemory - item->inuseMemory >= search) {
            if (count == 0) {
                arrayCD[count] = item;
            }
            arrayCD = (BaseCD **)realloc(arrayCD, sizeof(BaseCD *)*(count+1));
            arrayCD[count] = item;

            printf("Index: %i - %p type: ", i, item);
            cout << item->type << endl;
            count++;
            continue;
        }
    }

    if (count == 0) {
        cout << "Nothing" << endl;
        return NULL;
    }
    return arrayCD;
}

int changeNeighbor(BaseCD &thisItem, BaseCD &nextItem) {
    BaseCD *med = (BaseCD *)nextItem.next;
    nextItem.next = &thisItem;
    thisItem.next = med;

    med = (BaseCD *)thisItem.prev;
    thisItem.prev = &nextItem;
    nextItem.prev = med;

    if (thisItem.next != NULL) thisItem.next->prev = &thisItem;
    if (nextItem.prev != NULL) nextItem.prev->next = &nextItem;

    return 1;
}

bool shouldSwap(BaseCD *obj1, BaseCD *obj2, TypeSort type) {
    switch (type)
    {
    case TypeSort::Title: {
        return obj1->title.compare(obj2->title) > 0;
    }
    case TypeSort::InuseMemory: {
        return obj1->inuseMemory > obj2->inuseMemory 
    }
    case TypeSort::Duration: {
        if (obj1->type == TypesCD::TData && obj2->type != TypesCD::TData) 
            return true;

        if (obj1->type == TypesCD::TData && obj2->type == TypesCD::TData)
            return false;

        if (((PlayCD *)obj1)->duration > ((PlayCD *)obj2)->duration)
            return true;
        else 
            return false;
    }
    
    default:
        break;
    }
}

int sort(List *list, TypeSort type) {
    if (list == NULL) return -1;

    for (int j = 0; j < countList(list); j++) {
        for (int i = 0; i < countList(list) - 1; i++) {
            BaseCD *thisItem = (BaseCD *)getPointerByIndex(list, i);
            BaseCD *nextItem = (BaseCD *)getPointerByIndex(list, i+1);
            //If next item nearer than this than change their positions
            if (shouldSwap(thisItem, nextItem, type)) {
                changeNeighbor(*thisItem, *nextItem);

                if (i == 0) list->head = nextItem;
                if (i == countList(list) - 1) list->tail = thisItem;
            }
        }
    }
    return 0;
}

int printInformationItem(BaseCD *item) {
    if (item == NULL) {
        cout << "Null pointer" << endl;
        return 0;
    }
    cout << "Title: " << item->title << endl << "Type: " << item->type << endl
         << "Total memory(mb): " << item->totalMemory << endl
         << "Inuse memory(mb): " << item->inuseMemory << endl
         << "Is appending: " << item->isAppending << endl
         << "Is rewriting: " << item->isRewriting << endl;

    if (item->type == TypesCD::TAudio || item->type == TypesCD::TMP3) {
        cout << "Artist: " << ((AudioCD *)item)->artist << endl
             << "Duration(seconds): " << ((PlayCD *)item)->duration << endl;
        return 1;
    }
    if (item->type == TypesCD::TVideo || item->type == TypesCD::TDVD) {
        cout << "Artist: " << ((AudioCD *)item)->artist << endl
             << "Duration(seconds): " << ((PlayCD *)item)->duration << endl;
    }
    if (item->type == TypesCD::TDVD) {
        cout << "Available sections: " << ((DVD *)item)->numSections << endl;
    }
    return 1;
}

int printInformationItem(List *list, int index) {
    ListItem *item = getPointerByIndex(list, index);
    
    printInformationItem((BaseCD *)item);
    return 1;
}

void printExtendedList(List *list) {
    if (list == NULL || list->head == NULL) {
        cout << "Empty" << endl;
        return;
    }
    for (int i = 0; i < countList(list); i++) {
        cout << "\t\t\t\tElement " << i << endl;
        printInformationItem(list, i);
    }
}

//todo сделать функцию подробного вывода всех элементов //done
//todo функции сортировки выводят подробный вывод списка //done
//todo элементы, не поддающиеся сортировке идут в конец //done
//todo inuse не может быть больше memory capacity //done
//todo вынести объектно ориентированную часть работы в отдельный модуль //done