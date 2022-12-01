#include <iostream>
enum class NODE_TYPE {
    PARENT,
    L_CHILD,
    R_CHILD,
    END
};

template <typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;
};

template <typename T1, typename T2>
Pair<T1, T2> make_pair(const T1& _first, const T2& _second){
    return Pair<T1, T2>{_first, _second};
};

template <typename T1, typename T2>
struct BSTNode {
    Pair<T1, T2> pair;

    BSTNode<T1, T2>* arrNode[(int)NODE_TYPE::END];

    public:
        bool isRoot() {
            return arrNode[(int)NODE_TYPE::PARENT] == nullptr;
        }
        bool isLChild() {
            return arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::L_CHILD] == this;
        }
        bool isRChild() {
            return arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::R_CHILD] == this;
        }
        bool isLeaf() {
            return arrNode[(int)NODE_TYPE::L_CHILD] == nullptr && arrNode[(int)NODE_TYPE::R_CHILD] == nullptr;
        }
        bool isFull() {
            return arrNode[(int)NODE_TYPE::L_CHILD] && arrNode[(int)NODE_TYPE::R_CHILD];
        }

    public:
        BSTNode()
        : pair(nullptr)
        , arrNode{nullptr, nullptr, nullptr} {}
        BSTNode(const Pair<T1, T2>& _pair, BSTNode* _pParent, BSTNode* _pLChild, BSTNode* _pRChild)
        : pair(_pair)
        , arrNode{_pParent, _pLChild, _pRChild}{
        }
};

template <typename T1, typename T2>
class BST {
    private:
        BSTNode<T1, T2>* m_pRootNode;
        int m_iCount;
    public:
        bool insert(const Pair<T1, T2>& _pair);
        BSTNode<T1, T2>* GetInOrderSuccessor(BSTNode<T1, T2>* _pNode);
        BSTNode<T1, T2>* GetInOrderPredecessor(BSTNode<T1, T2>* _pNode);


        class iterator;
        iterator begin();
        iterator end();
        iterator find(const T1& _key);
        iterator erase(const iterator& _iter);
    private:
        BSTNode<T1, T2>* DeleteNode(BSTNode<T1, T2>* _pNode);

    public:
        BST()
        : m_pRootNode(nullptr)
        , m_iCount(0){};
        ~BST(){};
    public:
        class iterator {
            private:
                BST<T1, T2>* m_pBST;
                BSTNode<T1, T2>* m_pNode;
                bool m_bValid;
            public:
                iterator() 
                : m_pBST(nullptr)
                , m_pNode(nullptr)
                , m_bValid(false) {};
                iterator(BST<T1, T2>* _pBST, BSTNode<T1, T2>* _pNode) 
                : m_pBST(_pBST)
                , m_pNode(_pNode)
                , m_bValid(false){
                    if(nullptr != _pBST && nullptr != _pNode){
                        m_bValid = true;
                    }
                };
                ~iterator(){};
            public:
                const Pair<T1, T2>& operator * () {
                    if(!m_bValid) {
                        std::cout << "BST::iterator::operator* 유효하지 않은 이터레이터" << std::endl;
                        assert(nullptr);
                    }
                    if(nullptr == m_pNode){
                        std::cout << "BST::iterator::operator* end 이터레이터에서 호출됨" << std::endl;
                        assert(nullptr);
                    }
                    return m_pNode->pair;
                }
                const Pair<T1, T2>* operator -> () {
                    if(!m_bValid) {
                        std::cout << "BST::iterator::operator* 유효하지 않은 이터레이터" << std::endl;
                        assert(nullptr);
                    }
                    if(nullptr == m_pNode){
                        std::cout << "BST::iterator::operator* end 이터레이터에서 호출됨" << std::endl;
                        assert(nullptr);
                    }
                    return &m_pNode->pair;
                }
                bool operator == (const iterator& _otherIter) {
                    if(m_pBST == _otherIter.m_pBST && m_pNode == _otherIter.m_pNode){
                        return true;
                    }
                    return false;
                }
                bool operator != (const iterator& _otherIter) {
                    return !(*this == _otherIter);
                }
                iterator& operator ++ () {
                    m_pNode = m_pBST->GetInOrderSuccessor(m_pNode);
                    return *this;
                }
                iterator& operator -- () {
                    m_pNode = m_pBST->GetInOrderPredecessor(m_pNode);
                    return *this;
                }
            friend class BST<T1, T2>;
        };
};

template <typename T1, typename T2>
bool BST<T1, T2>::insert(const Pair<T1,T2>& _pair){
    BSTNode<T1, T2>* pNewNode = new BSTNode<T1, T2>(_pair, nullptr, nullptr, nullptr);

    if(m_pRootNode == nullptr) {
        m_pRootNode = pNewNode;
    }else {
        BSTNode<T1, T2>* pNode = m_pRootNode;

        NODE_TYPE node_type = NODE_TYPE::END;

        while(true){

            if(pNode->pair.first < pNewNode->pair.first){
                node_type = NODE_TYPE::R_CHILD;
            }else if(pNode->pair.first > pNewNode->pair.first) {
                node_type = NODE_TYPE::L_CHILD;
            }else {
                return false;; // 중복되는 키값
            }
            
            if(nullptr == pNode->arrNode[(int)node_type]){
                pNode ->arrNode[(int)node_type] = pNewNode;
                pNewNode->arrNode[(int)NODE_TYPE::PARENT] = pNode;
                break;
            }else {
                pNode = pNode->arrNode[(int)node_type];
            }
        }
        
    }
    m_iCount += 1;
    return true;
}

template <typename T1, typename T2>
typename BST<T1, T2>::iterator BST<T1, T2>::begin () {
    BSTNode<T1, T2>* pNode = m_pRootNode;
    while(pNode->arrNode[(int)NODE_TYPE::L_CHILD]) {
        pNode = pNode->arrNode[(int)NODE_TYPE::L_CHILD];
    }
    return iterator(this, pNode);
}

template <typename T1, typename T2>
typename BST<T1, T2>::iterator BST<T1, T2>::end () {
    return iterator(this, nullptr);
}

template <typename T1, typename T2>
typename BST<T1, T2>::iterator BST<T1, T2>::find (const T1& _key) {
    BSTNode<T1, T2>* pNode = m_pRootNode;
    NODE_TYPE node_type = NODE_TYPE::END;

    while(true){
        if(_key < pNode->pair.first){
            node_type = NODE_TYPE::L_CHILD;
        }else if(_key > pNode->pair.first) {
            node_type = NODE_TYPE::R_CHILD;
        }else {
            break;
        }

        if(nullptr == pNode->arrNode[(int)node_type]){
            pNode = nullptr;
            break;
        }else {
            pNode = pNode->arrNode[(int)node_type];
        }
    }
    return iterator(this, pNode);
}

// 중위 후속자
template <typename T1, typename T2>
BSTNode<T1, T2>* BST<T1, T2>::GetInOrderSuccessor(BSTNode<T1, T2>* _pNode){
    // 1. if 오른쪽 자식이 있으면 오른쪽 자식으로 가서 왼쪽 자식이 없을때까지 내려감 (왼쪽자식이 없으면 자신이 후속자)
    // 2. else 부모로부터 왼쪽자식일 때 까지 올라감 (왼쪽자식이면 부모가 후속자)

    BSTNode<T1, T2>* pSuccessor = nullptr;
    if(_pNode->arrNode[(int)NODE_TYPE::R_CHILD] != nullptr){
        pSuccessor = _pNode->arrNode[(int)NODE_TYPE::R_CHILD];

        while(pSuccessor->arrNode[(int)NODE_TYPE::L_CHILD] != nullptr){
            pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::L_CHILD];
        }
    }else {
        pSuccessor = _pNode;
        while(true){
            if(pSuccessor->isRoot()){
                pSuccessor =  nullptr;
                break;
            }
            if(pSuccessor->isLChild()){
                pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
                break;
            }
            pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
        }
    }
    return pSuccessor;
}

// 중위 선행자
template <typename T1, typename T2>
BSTNode<T1, T2>* BST<T1, T2>::GetInOrderPredecessor(BSTNode<T1, T2>* _pNode){
    // 1. if 왼쪽 자식이 있으면 왼쪽 자식으로 가서 오른쪽 자식이 없을때까지 내려감 (오른쪽자식이 없으면 자신이 선행자)
    // 2. else 부모로부터 오른쪽자식일 때 까지 올라감 (오른쪽자식이면 부모가 선행자)
    BSTNode<T1, T2>* pSuccessor = nullptr;
    if(_pNode->arrNode[(int)NODE_TYPE::L_CHILD] != nullptr){
        pSuccessor = _pNode->arrNode[(int)NODE_TYPE::L_CHILD];

        while(pSuccessor->arrNode[(int)NODE_TYPE::R_CHILD] != nullptr){
            pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::R_CHILD];
        }
    }else {
        pSuccessor = _pNode;
        while(true){
            if(pSuccessor->isRoot()){
                pSuccessor =  nullptr;
                break;
            }
            if(pSuccessor->isRChild()){
                pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
                break;
            }
            pSuccessor = pSuccessor->arrNode[(int)NODE_TYPE::PARENT];
        }
    }
    return pSuccessor;
}



template <typename T1, typename T2>
typename BST<T1, T2>::iterator BST<T1, T2>::erase(const BST<T1, T2>::iterator& _iter){
    if(!_iter.m_bValid || this != _iter.m_pBST) {
        std::cout << "BST::iterator::erase 유효하지 않은 이터레이터" << std::endl;
        assert(nullptr);
    }
    BSTNode<T1, T2>* pSuccessor = this->DeleteNode(_iter.m_pNode);
    

    return iterator(this, pSuccessor);
}

template <typename T1, typename T2>
BSTNode<T1, T2>* BST<T1, T2>::DeleteNode(BSTNode<T1, T2>* _pNode){
    BSTNode<T1, T2>* pSuccessor = GetInOrderSuccessor(_pNode);

    // 자식이 0개인 경우
    if(_pNode->isLeaf()){

        // 자식이 0개인데 루트노드
        if(_pNode->isRoot()){
            m_pRootNode = nullptr;
        }else {
            // 부모노드에서 해당 자식노드를 가르키는 포인터를 nullptr로 변경
            if(_pNode->isLChild()){
                _pNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::L_CHILD] = nullptr;
            }else {
                _pNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::R_CHILD] = nullptr;
            }
        }
        delete _pNode;
        --m_iCount;
    
    // 자식이 2개인 경우 (삭제할 자리에 중위후속자를 복사)
    }else if(_pNode->isFull()){
        // 삭제할 노드가 루트여도 값만 복사해 오기 때문에 연결 된 노드는 변화가 없음으로 예외처리 필요없음

        _pNode->pair = pSuccessor->pair; // 후속자의 값을 복사

        DeleteNode(pSuccessor); // 후속자가 가르키는 포인터 제거

        pSuccessor = _pNode; // 반환 할 후속자는 삭제할 노드가 가르키던 포인터가 됨(해당 포인터 자리에 삭제할 노드의 중위후속자 값이 복사되어있음)

    // 자식이 1개인 경우 (삭제할 노드의 부모와 삭제할 노드의 자식을 연결)
    }else {
        NODE_TYPE child_type = NODE_TYPE::L_CHILD;
        if(_pNode->arrNode[(int)NODE_TYPE::R_CHILD]){
            child_type = NODE_TYPE::R_CHILD;
        }
        
        if(_pNode->isRoot()){
            m_pRootNode = _pNode->arrNode[(int)child_type];
            _pNode->arrNode[(int)child_type]->arrNode[(int)NODE_TYPE::PARENT] = nullptr;
        }else {
            // 부모노드의 자식연결
            if(_pNode->isLChild()){
                _pNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::L_CHILD] = _pNode->arrNode[(int)child_type];
            }else {
                _pNode->arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::R_CHILD] = _pNode->arrNode[(int)child_type];
            }
            // 자식노드의 부모연결
            _pNode->arrNode[(int)child_type]->arrNode[(int)NODE_TYPE::PARENT] = _pNode->arrNode[(int)NODE_TYPE::PARENT];
        }
        delete _pNode;
        --m_iCount;
    }

    return pSuccessor;
}