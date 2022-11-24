#include <locale.h>
#include <stdio.h>
#include "IoStream/Iostream.h"



int main() {
    setlocale(LC_ALL, "ko_KR");

    MyStd::cout << L"안녕하세요.";

    char str[10];
    wchar_t wstr[10];

    MyStd::cin >> str;
    MyStd::cin >> wstr;
    
    MyStd::cout << str << MyStd::endl;
    MyStd::cout << wstr << MyStd::endl;


    return 0;
}