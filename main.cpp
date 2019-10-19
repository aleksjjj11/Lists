#include "subj.h"

int main() 
{
    setlocale(LC_CTYPE, "rus");
    int result = 0;
    List *listLoc = new List;
    do 
        result = menu(listLoc); 
    while (true);
    return 0;
}