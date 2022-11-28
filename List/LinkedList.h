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
    int size() { return m_iSize; };

    void print();

public:
    class iterator;
    iterator begin();
    iterator end();

public:
    LinkedList();
    ~LinkedList();

    class iterator {
        private:
            LinkedList* m_pLinkedList; 
            Node<T>* m_pNode; // nullptr 이면 end iterator
            bool m_bValid;

        public:
            T& operator* () {
                return m_pNode->value;
            }
            bool operator== (const iterator& _otherIter) {
                if(m_pLinkedList == _otherIter.m_pLinkedList && m_pNode == _otherIter.m_pNode){
                    return true;
                }
                return false;
            }
            bool operator!= (const iterator& _otherIter){
                return !(*this == _otherIter);
            }
            iterator& operator++ () {
                if(!m_bValid) {
                    std::cout << "LinkedList::iterator::operator++ 유효하지 않은 이터레이터" << std::endl;
                    assert(nullptr);
                }
                if(nullptr == m_pNode) {
                    std::cout << "LinkedList::iterator::operator++ end iterator에서 호출됨" << std::endl;
                    assert(nullptr);
                }
                m_pNode = m_pNode->pNext;
                return *this;
            }
            iterator operator++ (int) {
                iterator copyIter(*this);
                ++(*this);
                return copyIter;
            }
            iterator& operator-- () {
                if(!m_bValid) {
                    std::cout << "LinkedList::iterator::operator-- 유효하지 않은 이터레이터" << std::endl;
                    assert(nullptr);
                }
                if(m_pLinkedList->m_pHeadNode == m_pNode) {
                    std::cout << "LinkedList::iterator::operator-- begin iterator에서 호출됨" << std::endl;
                    assert(nullptr);
                }
                m_pNode = m_pNode->pPrev;
                
                return *this;
                
            }
            iterator operator-- (int) {
                iterator copyIter(*this);
                --(*this);
                return copyIter;
            }

        public:
            iterator()
            : m_pLinkedList(nullptr)
            , m_pNode(nullptr)
            , m_bValid(false){}
            iterator(LinkedList<T>* _pLinkedList, Node<T>* _pNode)
            : m_pLinkedList(_pLinkedList)
            , m_pNode(_pNode)
            , m_bValid(false){
                if (nullptr != _pLinkedList && nullptr != _pNode){
                    m_bValid = true;
                }
            }
            ~iterator(){}
        friend LinkedList;

    };
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

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    return iterator(this, m_pHeadNode);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return iterator(this, nullptr);
}