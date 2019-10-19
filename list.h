#include <iostream>

struct ListItem {
    ListItem *prev = NULL;
    ListItem *next = NULL;
};
struct List {
    ListItem *head = NULL;
    ListItem *tail = NULL;
};
