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
    T* data() {return m_pData; };
    int size() { return m_iSize; };
    int capacity() { return m_iLimit; };

    void print();
    void print_size();

    T& operator[] (int idx);
    class iterator;
    iterator begin();
    iterator end();

public:
    DynamicArray();
    ~DynamicArray();

    class iterator {
        private: 
            DynamicArray* m_pDynamicArray;
            T* m_pData;
            int m_iIdx;

        public:
            T& operator * () {
                if(m_pDynamicArray->m_pData != m_pData || -1 == m_iIdx){
                    assert(nullptr);
                }
                return m_pData[m_iIdx];
            }
            iterator& operator ++ () {
                if(m_pDynamicArray->m_pData != m_pData || -1 == m_iIdx){
                    assert(nullptr);
                }
                if(m_pDynamicArray->size() -1 == m_iIdx){
                    m_iIdx = -1;
                }else {
                    m_iIdx += 1;
                }
                
                return *this;
            }
            iterator operator ++ (int) {
                iterator copy_iter = *this;
                ++(*this);
                return copy_iter;
            }

            iterator& operator -- () {
                if(m_pDynamicArray->m_pData != m_pData || 0 == m_iIdx){
                    assert(nullptr);
                }
                if(m_iIdx == -1 && 0 < m_pDynamicArray->size()){
                    m_iIdx = m_pDynamicArray->size() - 1;
                }else {
                    m_iIdx -= 1;
                }
                return *this;
            }

            iterator operator -- (int) {
                iterator copy_iter = *this; // === iterator copy_iter(*this) 컴파일러가 복사 생성자로 변환
                --(*this);
                return copy_iter;
            }

            bool operator ==(const iterator& other_iterator){
                if(m_pData == other_iterator.m_pData && m_iIdx == other_iterator.m_iIdx){
                    return true;
                }
                return false;
            }
            bool operator !=(const iterator& other_iterator){
                return !(*this == other_iterator);
            }

            
        public:
        iterator()
            : m_pDynamicArray(nullptr)
            , m_pData(nullptr)
            , m_iIdx(-1){
        };
        iterator(DynamicArray* _pDynamicArray, T* _pData, int _iIdx)
            : m_pDynamicArray(_pDynamicArray)
            , m_pData(_pData)
            , m_iIdx(_iIdx){
        };
        ~iterator(){};
    };
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

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::begin() {
    if(m_iSize == 0) {
        return iterator(this, m_pData, -1);
    }else {
        return iterator(this, m_pData, 0);
    }
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::end() {
    return iterator(this, m_pData, -1);
}