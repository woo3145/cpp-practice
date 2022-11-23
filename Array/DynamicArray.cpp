#include "DynamicArray.h"
#include <assert.h>
#include <stdio.h>


DynamicArray::DynamicArray() 
    : m_pInt(nullptr)
    , m_iSize(0)
    , m_iLimit(2) {
    m_pInt = new int[2];
}

DynamicArray::~DynamicArray() {
    delete[] m_pInt;
}

void DynamicArray::resize(int _iLimit) {
    if(_iLimit <= m_iSize){
        assert(nullptr);
    }
    int* pNew = new int[_iLimit];

    for(int i = 0; i < m_iSize; ++i) {
        pNew[i] = m_pInt[i];
    }

    delete[] m_pInt;

    m_pInt = pNew;
    m_iLimit = _iLimit;
}

void DynamicArray::push_back(int _iData) {
    if(m_iLimit <= m_iSize) {
        resize(m_iLimit * 2);
    }

    m_pInt[m_iSize] = _iData;
    m_iSize += 1;
}

void DynamicArray::print() {
    for(int i = 0; i < m_iSize; ++i){
        printf("%d\n", m_pInt[i]);
    };
}

void DynamicArray::printSize() {
    printf("size : %d\nlimit : %d\n", m_iSize, m_iLimit);
}

int& DynamicArray::operator[] (int idx) {
    if(m_iLimit <= idx) {
        assert(nullptr);
    }
    return m_pInt[idx];
}