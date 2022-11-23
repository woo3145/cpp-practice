#include <stdio.h>
#include "List/LinkedList.h"


int main() {
    LinkedList<int> list;

    list.push_front(4444);
    list.push_back(10);
    list.push_back(21);
    list.push_back(440);

    list.push_front(999);
    list.push_front(20);

    list.print();
    

    return 0;
}