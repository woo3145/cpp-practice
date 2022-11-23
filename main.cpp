#include <stdio.h>
#include "Array/DynamicArray.h"


int main() {
    DynamicArray<int> dArr = {};
    dArr.push_back(10);
    dArr.push_back(20);
    dArr.push_back(30);
    dArr.printSize();
    dArr.print();
    
    DynamicArray<float> fArr = {};
    fArr.push_back(3.3f);
    fArr.push_back(20.4f);
    fArr.push_back(30.11455f);
    fArr.printSize();
    fArr.print();

    return 0;
}