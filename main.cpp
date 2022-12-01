#include <iostream>
#include "DataStructure/BST/BST.h"

using std::cout;
using std::cin;
using std::endl;



int main() {
    BST<int, int> bstInt;
    bstInt.insert(make_pair(10,1)); //      10
    bstInt.insert(make_pair(5,0));  //    5    20
    bstInt.insert(make_pair(3,0));  //   3 6  15 25
    bstInt.insert(make_pair(6,0));  //
    bstInt.insert(make_pair(20,0));
    bstInt.insert(make_pair(15,0));
    bstInt.insert(make_pair(25,0));
    BST<int, int>::iterator myIter = bstInt.begin();
    
    bstInt.erase(bstInt.find(5));
    
    for(myIter = bstInt.begin(); myIter != bstInt.end(); ++myIter){
        cout << myIter->first << endl;
    }
} 