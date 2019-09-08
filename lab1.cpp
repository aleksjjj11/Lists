#include <iostream>
#include <locale.h>

using namespace std;

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
ListItem* getPointerByIndex(List *list, int index);
int deleteItem(List *list, int index);
ListItem* removeItem(List *list, int index);
int clearList(List *list);
int insertItem(List *list, ListItem *item, int index);

int menu(List *list);

int main(){
    setlocale(LC_CTYPE, "rus");
    int result = 0;
    List *listLoc = new List;
    do 
        result = menu(listLoc); 
    while (result > 0);
    return 0;
}

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
    }
    while (chooseAction < 0 || chooseAction > 9);
    switch (chooseAction)
    {
    case 0:
        exit(0);
        break;
    case 1: {
        ListItem *itemLoc = new ListItem;
        return addItem(list, itemLoc);
        //break;
    }
    case 2: {
        int count = countList(list);
        cout << "Count list = " << count << endl;
        getchar(); getchar();
        return 1;
        //break;
    }
    case 3:{
        ListItem *itemLoc;
        scanf("%p", &itemLoc);
        int result = getIndexByPointer(list, itemLoc);
        if (result > 0)
            cout << "Index = " << result;
        else 
            cout << "Error: " << result;
        getchar(); getchar();
        return result;
    }
    case 4: {
        int indexSearch = 0;
        ListItem *itemSearch = NULL;
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
        ListItem *result = NULL;
        printList(list);
        cout << "Enter index for removing: ";
        cin >> index;
        result = getPointerByIndex(list, index);
        if (result == NULL) return 0;
        
        cout << "Deleted pointer - " << result << endl;
        deleteItem(list, index);
        getchar(); getchar();
        return 1;
    }
    case 6: {
        int index;
        ListItem *result = NULL;
        printList(list);
        cout << "Enter index for removing: ";
        cin >> index;
        result = removeItem(list, index);
        if (result == NULL) return 0;
        
        cout << "Removed pointer - " << result << endl;
        getchar(); getchar();
        return 1;
    }
    case 7: {
        if (clearList(list) == 1) {
            cout << "List was deleted." << endl;
            getchar(); getchar();
            return 1;
        } else {
            cout << "Attempt to delete null pointer." << endl;
            getchar(); getchar();
            return 0;
        }
    }
    case 8: {
        ListItem *itemLoc = new ListItem;
        int position = 0;
        cout << "Enter position for inserting: ";
        cin >> position;
        cout << "Inserting list item: " << itemLoc << endl;
        if (insertItem(list, itemLoc, position) == 0) {
            cout << "Attempt to insert null pointer." << endl;
            getchar(); getchar();
            return 0;
        }

        cout << "Pointer " << itemLoc << " was successfully inserted." << endl;
        getchar(); getchar(); 
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

int addItem(List *list, ListItem *item) {
    if (list == NULL) return -1;
    if (item == NULL) return -2;
    
    if (list->head == NULL) {
        list->head = item;
        list->tail = item;
    } else {
        item->prev = list->tail;
        list->tail->next = item;

        item->next = NULL;
        list->tail = item;
    }
    printf("Added list item %p\n", item);
    getchar(); getchar();
    return 1;
}

void printList(List *list) {
    if (list == NULL || list->head == NULL) {
        cout << "List empty." << endl; 
        getchar(); getchar();
        return;
    }
    //printItem(list->head);
    ListItem *med = list->head;
    int i = 0;
    do {
        printf("%i. %p\n", i, med);
        med = med->next;
        i++;
    } while (med != NULL);
    getchar(); getchar();
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
    int index = 0, count = countList(list);
    while(index < count && search != med) {
        index++;
        med = med->next;
    }
    if (index >= count) return -3;
    return index;
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

    ListItem *item = getPointerByIndex(list, index);
    if (item == NULL) return NULL;

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
    delete(removeItem(list, index));
    return 1;
}

int clearList(List *list) {
    if (list == NULL || list->head == NULL) return 0;
    delete(list);
    return 1;
}
int insertItem(List *list, ListItem *item, int index) {
    ListItem *pointer = getPointerByIndex(list, index);
    if (pointer == NULL) return 0;

    if (pointer == list->head) {
        list->head = item;

        pointer->prev = item;
        item->next = pointer;
        item->prev = NULL;
        return 1;
    }

    // if (pointer == list->tail) {
        
    // }

    item->prev = pointer->prev;
    item->next = pointer;

    pointer->prev->next = item;
    pointer->prev = item;

    return 1;
}