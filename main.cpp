#include <stdio.h>
#include "Array/DynamicArray.h"


int main() {
    DynamicArray dArr = {};
    dArr.push_back(10);
    dArr.push_back(20);
    dArr.push_back(30);

    dArr.printSize();
    dArr.print();

    dArr[1] = 1022;
    dArr.print();

    dArr.resize(100);
    dArr.printSize();
    return 0;
}