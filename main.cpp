#include <iostream>
#include <list>
#include <vector>
#include "Array/Vector.h"
#include "List/LinkedList.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

int main() {

    LinkedList<int> myList;
    LinkedList<int>::iterator myIter;
    for(int i = 1; i <= 10; ++i) {
        myList.push_back(i);
    }
    myIter = myList.begin();
    for(; myIter != myList.end();){
        if(*myIter % 2 == 0){
            myIter = myList.erase(myIter);
        }else {
            ++myIter;
        }
    }

    for(myIter = myList.begin(); myIter != myList.end(); ++myIter){
        cout << *myIter << endl;
    }
    return 0;
}