#include "lab1.h"

using namespace std;

int menu(List *list){
    int chooseAction = 0;
    
    do {
        #ifdef WIN32
        system("cls");
        #else
        system("clear");
        #endif
        cout << "1. Add item" << endl
            << "2. Count list" << endl
            << "3. Get index by pointer" << endl
            << "4. Get pointer by index" << endl
            << "5. Delete item" << endl
            << "6. Remove item" << endl
            << "7. Clear list" << endl
            << "8. Insert item" << endl
            << "9. Print all list" << endl
            << "0. Exit" << endl;
        cin >> chooseAction;
    } while (chooseAction < 0 || chooseAction > 9);
    switch (chooseAction)
    {
    case 0:
        exit(0);
        break;
    case 1: {
        CD *itemLoc = new CD;
        return addItem(list, itemLoc);
    }
    case 2: {
        int count = countList(list);
        cout << "Count list = " << count << endl;
        cout << "Press any key for contien" << endl;
        getchar(); getchar();
        return 1;
    }
    case 3:{
        CD *itemLoc;
        printList(list);
        scanf("%p", &itemLoc);
        int result = getIndexByPointer(list, itemLoc);
        // cout << "Result: " << result << endl;
        // getchar();
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
        CD *itemSearch = NULL;
        printList(list);
        cout << "Enter index: ";
        cin >> indexSearch;
        itemSearch = getPointerByIndex(list, indexSearch);
        if (itemSearch) {
            cout << "Found pointer: " << itemSearch << endl;
            getchar(); getchar();
            return 1; //Если не НУЛ, то возвращаем, что успешно
        }
        else return 0; //Иначе, что НУЛ
    }
    case 5: {
        int index;
        CD *result = NULL;
        printList(list);
        cout << "Enter index for removing: ";
        cin >> index;
        result = getPointerByIndex(list, index);
        if (result == NULL) return 0;
        
        cout << "Deleted pointer - " << result << endl;
        deleteItem(list, index);
        printList(list);
        return 1;
    }
    case 6: {
        int index;
        CD *result = NULL;
        printList(list);
        cout << "Enter index for removing: ";
        cin >> index;
        result = removeItem(list, index);
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
        CD *itemLoc = new CD;
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
    case 9:
        printList(list);
        break;
    default:
        break;
    }
    return 1;
}

int addItem(List *list, CD *item) {
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
        getchar(); getchar();
        return;
    }
    //printItem(list->head);
    CD *med = list->head;
    int i = 0;
    do {
        printf("%i.\t\t\t%4p\t\t\t%4p\t\t\t%4p\n", i, med->prev, med, med->next);
        med = med->next;
        i++;
    } while (med != NULL);
    //cout << "Press any key for contien" << endl;
    //sgetchar(); getchar();
}

int countList(List *list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }
    int count = 0;
    CD *med = list->head;
    do {
        count++;
        med = med->next;
    } while (med != NULL);
    return count;
}

int getIndexByPointer(List *list, CD *search) {
    if (list == NULL) return -1;
    if (search == NULL) return -2;
    CD *med = list->head;
    int count = countList(list);
    for(int index = 0; med; index++) {
        if (med == search) return index;
        med = med->next;
    }
    return -3;
}

CD* getPointerByIndex(List *list, int index = 0) {
    if (list == NULL) return NULL;
    if (index < 0 || index > countList(list)) return NULL;
    int i = 0;
    CD *med = list->head;
    while (i < index && med != NULL) {
        i++;
        med = med->next;
    }   
    return med;
}

CD* removeItem(List *list, int index) {
    if (list == NULL) return NULL;
    if (index < 0 || index > countList(list)) return NULL;

    CD *item = getPointerByIndex(list, index);
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
    delete(list);
    return 1;
}

int insertItem(List *list, CD *item, int index) {

    if (index >= countList(list)){
        addItem(list,item);
        return 1;
    }

    CD *pointer = getPointerByIndex(list, index);

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