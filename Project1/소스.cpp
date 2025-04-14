#include <iostream>
#include <windows.h>

int main() {
    SetConsoleCP(437);             // 입력 코드 페이지 설정
    SetConsoleOutputCP(437);       // 출력 코드 페이지 설정
    char c = char(219);

    std::cout << c << char(219) << std::endl;  // █ 출력
    return 0;
}