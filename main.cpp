#include <iostream>
#include <vector>
#include <list>
#include "Array/DynamicArray.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

int main() {


    DynamicArray<int> dArr;

    dArr.push_back(10);
    dArr.push_back(20);
    dArr.push_back(30);
    DynamicArray<int>::iterator myIter = dArr.begin();

    for(; myIter != dArr.end(); myIter++){
        cout << *myIter << endl;
    }
    dArr.clear();
    for(int i = 0; i < 11; ++i){
        dArr.push_back(i);
    }

    myIter = dArr.begin();
    for(; myIter != dArr.end();){
        if(*myIter % 2 == 0){
            myIter = dArr.erase(myIter);
        }else {
            ++myIter;
        }
    }
    dArr.print();
    return 0;
}