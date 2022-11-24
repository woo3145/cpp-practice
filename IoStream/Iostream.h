#include <stdio.h>


class Ostream {
public:
    Ostream& operator << (int _iData) {
        printf("%d", _iData);
        return *this;
    };
    Ostream& operator << (float _fData) {
        printf("%f", _fData);
        return *this;
    };
    Ostream& operator << (const char _cData) {
        printf("%c", _cData);
        return *this;
    };
    Ostream& operator << (const char* _pString) {
        printf("%s", _pString);
        return *this;
    };
    Ostream& operator << (const wchar_t* _pString) {
        printf("%ls", _pString);
        return *this;
    };
    Ostream& operator << (void(*_pFunc)(void)) {
        _pFunc();
        return *this;
    };
};

class Istream {
public:
    Istream& operator >> (int& _iData){
        scanf("%d", &_iData);
        return *this;
    }
    Istream& operator >> (float& _iFlot){
        scanf("%f", &_iFlot);
        return *this;
    }
    Istream& operator >> (char* _pString){
        scanf("%s", _pString);
        return *this;
    }
    Istream& operator >> (wchar_t* _pString){
        scanf("%ls", _pString);
        return *this;
    }
};

namespace MyStd {
    Ostream cout;
    Istream cin;
    void endl() {
        printf("\n");
    };
};
