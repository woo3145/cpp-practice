#include <assert.h>
#include <iostream>

template <typename T>
class Vector {
    private:
        T* m_pData; // 벡터의 시작주소값
        int m_iLimit; // 벡터의 최대값
        int m_iSize; // 벡터의 현재 원소의 수

    public:
        T* data() { return m_pData; }
        int size() { return m_iSize; } // 벡터의 원소 수
        int capacity() { return m_iLimit; } // 벡터의 최대크기
        bool empty() { return m_iSize == 0; }; // 벡터가 비어있는지 확인
        void resize(int _iSize); // 벡터의 최대 크기 재할당
        T front(); // 벡터의 첫번째 원소
        T back(); // 벡터의 마지막 원소

        void push_back(const T& _data);
        void pop_back();

        T operator [](int _idx) {
            if(0 > _idx || m_iSize <= _idx) {
                std::cout << "Vector::operator[] 현재 벡터를 벗어난 인덱스 접근" << std::endl;
                assert(nullptr);
            }
            return m_pData[_idx];
        }
        T at(int _idx) { // 벡터의 n번째 값 참조
            if(0 > _idx || m_iSize <= _idx) {
                std::cout << "Vector::at 현재 벡터를 벗어난 인덱스 접근" << std::endl;
                assert(nullptr);
            }
            return m_pData[_idx];
         } 
            
        
        class iterator;
        iterator begin(); // 벡터의 첫번째 원소를 가리키는 이터레이터
        iterator end(); // 벡터의 마지막 다음 원소를 가리키는 이터레이터
        iterator erase(iterator& _iter); // 받아온 이터레이터가 가르키는 값을 제거
        
    public:
        Vector ()
            : m_pData(nullptr)
            , m_iSize(0)
            , m_iLimit(0) {};
        ~Vector () {
            delete[] m_pData;
        };

        class iterator {
            private:
                Vector* m_pVector; // 벡터를 참조 (리사이즈 되어 실제 벡터의 데이터주소가 변경되었는지 확인하기 위함)
                T* m_pData; // 현재 이터레이터가 가르키는 벡터의 위치
                int m_iIdx; // 이터레이터가 가르키는 인덱스
                bool m_bValid; // 사용가능한 이터레이터 인지 확인
                // erase를 하면 넘겨준 이터레이터는 삭제될 부분을 가리키는 것임으로 사용을 못하도록 해야함 
                // Vector와 같은 가변배열은 배열특성상 값이 제거되면 인덱스가 다음 데이터를 가리키지만
                // 다른 자료구조에서는 아니기때문에 표준에 맞춰 m_Valid를 구현
            public:
                T operator * () {
                    if(!m_bValid) {
                        std::cout << "Vector::iterator::operator* 유효하지 않은 이터레이터" << std::endl;
                        assert(nullptr);
                    }
                    if(m_pVector->m_pData != m_pData || m_iIdx == -1){
                        std::cout << "Vector::iterator::operator* 벡터의 주솟값이 변경되거나 마지막 다음 인덱스에서 호출됨" << std::endl;
                        assert(nullptr);
                    }
                    return m_pData[m_iIdx];
                };
                iterator& operator ++ (){ // 전위 연산자
                    if(!m_bValid) {
                        std::cout << "Vector::iterator::operator++ 유효하지 않은 이터레이터" << std::endl;
                        assert(nullptr);
                    }
                    if(m_pVector->m_pData != m_pData || m_iIdx == -1){
                        std::cout << "Vector::iterator::operator++ 벡터의 주솟값이 변경되거나 마지막 다음 인덱스에서 호출됨" << std::endl;
                        assert(nullptr);
                    }
                    // 현재 인덱스가 마지막 원소라면 인덱스에 -1을 넣어준다(마지막원소의 다음을 가리킴)
                    if(m_iIdx == m_pVector->size() - 1){
                        m_iIdx = -1;
                    } else {
                        ++m_iIdx;
                    }
                    return *this;
                };
                // 후위 연산자는 객체를 반환할 때 이전상태를 가진 값을 반환해야 함으로 전위 연산자와 달리 참조값이 아닌 복사본을 반환해야만 한다. 
                //  ++ 위와 같은 이유로(++(++int)는 가능하지만 (int++)++ 는 불가능)
                // 따라서 복사본 생성 => 반환용 객체생성(레지스터와 같은 임시저장공간에) => 함수가 끝날 때 스택메모리가 제거되면서 객체삭제
                // 와 같은 불필요한 비용이 발생하기 때문에 후위 연산자는 굳이 필요하지 않으면 전위 연산자로 사용한다.
                iterator operator ++ (int) { // 후위 연산자
                    iterator copyIter = *this; // 컴파일러가 복사 생성자로 변환 => iterator copyIter(*this);
                    ++(*this); // 현재 이터레이터 객체를 가져와서 ++전위 연산자 실행
                    return copyIter; // 위에서 복사한 객체를 반환
                }; 
                iterator& operator -- (){ // 전위 연산자
                    if(m_bValid)
                    if(m_pVector->m_pData != m_pData || m_iIdx == 0){
                        if(!m_bValid) {
                            std::cout << "Vector::iterator::operator-- 유효하지 않은 이터레이터" << std::endl;
                            assert(nullptr);
                        }
                        std::cout << "Vector::iterator::operator-- 벡터의 주솟값이 변경되거나 첫번째 인덱스에서 호출됨" << std::endl;
                        assert(nullptr);
                    }
                    if(m_iIdx == -1){
                        m_iIdx = m_pVector->size() - 1;
                    }else {
                        --m_iIdx;
                    }
                    return *this;
                };
                iterator operator -- (int){ // 후위 연산자
                    iterator copyIter = *this;
                    --(*this);
                    return copyIter;
                }; 
                bool operator == (const iterator& _otherIterator){ // 이터레이터 비교
                    if(m_pData == _otherIterator.m_pData && m_iIdx == _otherIterator.m_iIdx){
                        return true;
                    }
                    return false;
                }; 
                bool operator != (const iterator& _otherIterator) {
                    // 이 연산자의 호출객체는 iterator 클래스 임으로 this는 이터레이터 객체의 주소값를 가리킴
                    return !(*this == _otherIterator);
                }
            public:
                iterator()
                    :m_pVector(nullptr)
                    ,m_pData (nullptr)
                    ,m_iIdx(-1)
                    ,m_bValid(true) {};
                iterator(Vector* _pVector, T* m_pData ,int _idx)
                    :m_pVector(_pVector)
                    ,m_pData (m_pData)
                    ,m_iIdx(_idx)
                    ,m_bValid(true) {};
                ~iterator(){};

                friend class Vector;
        };
};


template <typename T>
void Vector<T>::resize(int _iLimit) {
    if(m_iSize >= _iLimit) {
        std::cout << "현재 원소의 수보다 같거나 작은 값으로 리사이징 됨" << std::endl;
        assert(nullptr);
    }
    T* new_pData = new T[_iLimit];

    for(int i = 0; i < m_iSize; ++i) {
        new_pData[i] = m_pData[i];
    }
    
    delete[] m_pData;
    m_pData = new_pData;
    m_iLimit = _iLimit;
}

template <typename T>
T Vector<T>::front() {
    if(empty()) {
        std::cout << "Vector::front 배열이 비어있음" << std::endl;
        assert(nullptr);
    }
    return m_pData[0];
}
template <typename T>
T Vector<T>::back() {
    if(empty()) {
        std::cout << "Vector::back 배열이 비어있음" << std::endl;
        assert(nullptr);
    }
    return m_pData[m_iSize - 1];
}

template <typename T>
void Vector<T>::push_back (const T& _data) {
    if(capacity() <= size()){
        resize(1 <= size() ? size() * 2 : 1);
    }
    m_pData[size()] = _data;
    ++m_iSize;
}

template <typename T>
void Vector<T>::pop_back () {
    if(empty()){
        std::cout << "Vector::pop_back 배열이 비어있음" << std::endl;
        assert(nullptr);
    }
    --m_iSize;
}


template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    if(size() == 0) {
        return iterator(this, m_pData, -1);
    }else {
        return iterator(this, m_pData, 0);
    }
}
template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(this, m_pData, -1);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(Vector<T>::iterator& _iter) {
    if(m_pData != _iter.m_pData || end() == _iter) {
        std::cout << "Vector::erase 벡터의 주솟값이 변경되거나 받아온 이터레이터가 마지막 다음 원소를 가르킴" << std::endl;
        assert(nullptr);
    }
    // 삭제할 원소의 다음 인덱스들을 한칸씩 땡겨온다.
    for(int i = _iter.m_iIdx; i < size() - 1; ++i) {
        m_pData[i] = m_pData[i + 1];
    }
    --m_iSize;
    _iter.m_bValid = false;
    return iterator(this, m_pData, _iter.m_iIdx);
}