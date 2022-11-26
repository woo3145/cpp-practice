#include <iostream>

template <typename T>
struct Node {
    T value;
    Node<T>* pNext;
    Node<T>* pPrev;

    Node(const T& _value, Node<T>* _pPrev, Node<T>* _pNext)
        : value(_value)
        , pPrev(_pPrev)
        , pNext(_pNext) {
    }
};

template <typename T>
class LinkedList {

private:
    Node<T>* m_pHeadNode;
    Node<T>* m_pTailNode;
    int m_iSize;

public:
    void push_back(const T& _data);
    void push_front(const T& _data);
    void size() { return m_iSize };

    void print();

public:
    LinkedList();
    ~LinkedList();
};

template <typename T>
void LinkedList<T>::push_back(const T& _data) {
    Node<T>* pNewNode = new Node<T>(_data, nullptr, nullptr);
    if(m_iSize == 0){
        m_pHeadNode = pNewNode;
        m_pTailNode = pNewNode;
    }else {
        m_pTailNode->pNext = pNewNode;
        pNewNode->pPrev = m_pTailNode;

        m_pTailNode = pNewNode;
    }
    m_iSize += 1;
}

template <typename T>
void LinkedList<T>::push_front(const T& _data) {
    Node<T>* pNewNode = new Node<T>(_data, nullptr, m_pHeadNode);
    if(m_iSize == 0) {
        m_pHeadNode = pNewNode;
        m_pTailNode = pNewNode;
    } else{
        m_pHeadNode->pPrev = pNewNode;
        m_pHeadNode = pNewNode;

    }
    m_iSize += 1;
}

template <typename T>
void LinkedList<T>::print() {
    Node<T>* curNode = m_pHeadNode;
    while(curNode != nullptr){
        std::cout << curNode->value << std::endl;
        curNode = curNode->pNext;
    }
}


template <typename T>
LinkedList<T>::LinkedList()
    : m_iSize(0)
    , m_pHeadNode(nullptr)
    , m_pTailNode(nullptr) {    
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* curNode = m_pHeadNode;
    while(curNode != nullptr){
        Node<T>* nextNode = curNode->pNext;
        delete curNode;
        curNode = nextNode;
    }
    m_iSize = 0;
    m_pHeadNode = nullptr;
    m_pTailNode = nullptr;
}