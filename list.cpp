#include "list.h"
#include "SubjList.h"

using namespace std;

List::List() {
    this->head = NULL;
    this->tail = NULL;
}

List::~List() {
    this->clear();
}

void List::setHead(ListItem *item) {
    this->head = item;
}

int List::addItem(ListItem *item) {
    if (item == NULL) return -2;

    item->setList(this);
    if (this->getHead() == NULL) {
        this->setHead(item);
        this->setTail(item);
        item->setPrev();
    } else {
        item->setPrev(this->getTail());
        this->getTail()->setNext(item);

        this->setTail(item);
    }
    item->setNext();
    return 1;
}

void List::print() {
    if (this->getHead() == NULL) {
        cout << "List empty." << endl; 
        cout << "Press any key for contien" << endl;
        return;
    }
    BaseCD *med = (BaseCD *) this->getHead();
    int i = 0;
    do {
        cout << i << ".";
        if (med->getPrev() != NULL)
            cout << "\t\t\t" << ((BaseCD *) med->getPrev())->getTitle() << "\t\t\t";
        else 
            cout << "\t\t\t" << "NULL" << "\t\t\t";   

        if (med != NULL)
            cout << med->getTitle() << "\t\t\t";
        else 
            cout << "NULL" << "\t\t\t";
        
        if (med->getNext() != NULL)
            cout << ((BaseCD *) med->getNext())->getTitle() << endl;
        else 
            cout << "NULL" << endl; 

        med = (BaseCD *) med->getNext();
        i++;
    } while (med != NULL);
}

int List::count() {

    int count = 0;
    ListItem *med = this->getHead();
    while (med != NULL) {
        count++;
        med = med->getNext();
    }
    return count;
}

int List::getIndexByPointer(ListItem *search) {
    if (search == NULL) return -2;
    ListItem *med = this->getHead();
    int count = this->count();
    for(int index = 0; med; index++) {
        if (med == search) return index;
        med = med->getNext();
    }
    return -3;
}

ListItem* List::getPointerByIndex(int index) {
    if (index < 0 || index > count()) return NULL;
    int i = 0;
    ListItem *med = this->getHead();
    while (i < index && med != NULL) {
        i++;
        med = med->getNext();
    }
    return med;
}

ListItem* List::removeItem(int index) {
    if (index < 0 || index > count()) return NULL;

    BaseCD *item = (BaseCD *)getPointerByIndex(index);
    if (item == NULL) return NULL;

    if (count() == 1) {
        this->setHead();
        this->setTail();
        return (ListItem *)item;
    }

    if (item == this->getHead()) {
        this->setHead(item->getNext());
        item->getNext()->setPrev();
        return (ListItem *)item;
    }
    if (item == this->getTail()) {
        this->setTail(item->getPrev());
        item->getPrev()->setNext();
        return (ListItem *)item;
    }

    item->getPrev()->setNext(item->getNext());
    item->getNext()->setPrev(item->getPrev());
    return (ListItem *)item;
}

int List::deleteItem(int index) {
    delete removeItem(index);
    return 1;
}

int List::clear() {
    if (this->getHead() == NULL) return 0;
    while (this->getHead()) {
        deleteItem(count()-1);
    }



    /*f (list == NULL || list->getHead() == NULL) return 0;

    BaseCD *med = (BaseCD *)list->getTail();
    while (med) {
        //todo использовать функцию deleteitem
        BaseCD *item = (BaseCD *)med->getPrev();
        deleteItem(list, count(list) - 1);
        med = item;
    }(/*/
    return 1;
}

int List::insertItem(ListItem *item, int index) {

    if (index >= count()){
        addItem(item);
        return 1;
    }

    ListItem *pointer = getPointerByIndex(index);

    if (pointer == NULL) return 0;

    if (pointer == this->getHead()) {
        this->setHead(item);

        pointer->setPrev(item);
        item->setNext(pointer);
        item->setPrev();
        cout << "Pointer " << item << " was successfully inserted." << endl;
        print();
        return 1;
    }

    item->setPrev(pointer->getPrev());
    item->setNext(pointer);

    pointer->getPrev()->setNext(item);
    pointer->setPrev(item);
    cout << "Pointer " << item << " was successfully inserted." << endl;
    print();
    return 1;
}

ListItem* List::getTail() {
    return this->tail;
}

void List::setTail(ListItem *item) {
    this->tail = item;
}

ListItem::ListItem() {
    this->next = NULL;
    this->prev = NULL;
    this->list = NULL;
}

ListItem::~ListItem() {
    if (this->list == NULL) return;
    this->list->deleteItem(this->list->getIndexByPointer(this));
}

ListItem* List::getHead() {
    return this->head;
}

ListItem* ListItem::getNext() {
    return this->next;
}

void ListItem::setNext(ListItem *item) {
    this->next = item;
}

ListItem* ListItem::getPrev() {
    return this->prev;
}

void ListItem::setPrev(ListItem *item) {
    this->prev = item;
}

void ListItem::setList(List *list) {
    this->list = list;
}