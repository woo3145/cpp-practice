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
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myIter = myList.begin();
    myIter++;
    cout << *myIter << endl;
    myIter--;
    cout << *myIter << endl;
    return 0;
}