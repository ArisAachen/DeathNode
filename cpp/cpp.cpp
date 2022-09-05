#include <iostream>

void call(int& value) {
    std::cout << "none left" << std::endl;
}

void call(const int& value) {
    std::cout << "const" << std::endl;
}

void call(int&& value) {
    std::cout << "none right" << std::endl;
}

int main() {
    call(5);
    int value = 6;
    call(value);
    const int cvalue = 7;
    call(cvalue);
    int&& rvalue = 7;
}