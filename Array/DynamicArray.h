#include <iostream>
#include <assert.h>

template <typename T>
class DynamicArray {
private:
    T* m_pData;
    int m_iSize;
    int m_iLimit;

public:
    void resize(int _iLimit);
    void push_back(const T& _iData);
    void print();
    void print_size();

    T& operator[] (int idx);

public:
    DynamicArray();
    ~DynamicArray();
};


template <typename T>
DynamicArray<T>::DynamicArray() 
    : m_pData(nullptr)
    , m_iSize(0)
    , m_iLimit(2) {
    m_pData = new T[2];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] m_pData;
}

template <typename T>
void DynamicArray<T>::resize(int _iLimit) {
    if(_iLimit <= m_iSize){
        assert(nullptr);
    }
    T* pNew = new T[_iLimit];

    for(int i = 0; i < m_iSize; ++i) {
        pNew[i] = m_pData[i];
    }

    delete[] m_pData;

    m_pData = pNew;
    m_iLimit = _iLimit;
}

template <typename T>
void DynamicArray<T>::push_back(const T& _iData) {
    if(m_iLimit <= m_iSize) {
        resize(m_iLimit * 2);
    }

    m_pData[m_iSize] = _iData;
    m_iSize += 1;
}

template <typename T>
void DynamicArray<T>::print() {
    std::cout << "Values : [";
    for(int i = 0; i < m_iSize; ++i){
        std::cout << m_pData[i];
        if(i != m_iSize - 1){
            std::cout << ", ";
        }
    };
    std::cout << "]"<< "\n";
}

template <typename T>
void DynamicArray<T>::print_size() {
    std::cout << "Size : " << m_iSize << "\n";
    std::cout << "Limit : " << m_iLimit << "\n";
}

template <typename T>
T& DynamicArray<T>::operator[] (int idx) {
    if(m_iLimit <= idx) {
        assert(nullptr);
    }
    return m_pData[idx];
}