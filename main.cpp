#include <iostream>
#include <list>
#include "Array/Vector.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::list;

int main() {

    Vector<int> myVector;

    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);

    Vector<int>::iterator myIter = myVector.begin();
    myIter = myVector.erase(myIter);
    for(; myIter != myVector.end(); ++myIter){
        cout << *myIter << endl;
    }
    cout << myVector.data() << endl;

    return 0;
}