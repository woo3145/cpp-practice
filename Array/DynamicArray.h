

class DynamicArray {
private:
    int* m_pInt;
    int m_iSize;
    int m_iLimit;

public:
    void resize(int _iLimit);
    void push_back(int _iData);
    void print();
    void printSize();

    int& operator[] (int idx);

public:
    DynamicArray();
    ~DynamicArray();
};