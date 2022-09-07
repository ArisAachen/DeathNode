
#include "thread.h"

#include <functional>
#include <iostream>
#include <cstring>
#include <string>
#include <tuple>
#include <type_traits>

void test_get_line() {
    const int size = 20;
    char msg[size];
    memset(&msg, 0, sizeof(msg));

    while (strcmp(msg, "end") != 0)
    {
        std::cout << R"(please input message, use "end" to finish)" << std::endl;
        std::cin.getline(msg, size);
        std::cout << "input message is " << msg << std::endl;
    }

    std::cout << "get line end" << std::endl;

}


void test_struct() {
    struct test {
        std::string msg;
    } one, two;


    struct {
        std::string msg;
    } three;


}

void test_ano_union () {
    std::cout << "test_ano_union" << std::endl;
    // struct test {
    //     union 
    //     {
    //         std::string message;
    //         int id;
    //     };
        
    // } only ;

    // only.message = "test";

}

void size(char* buf) {
    std::cout << "func size is " << sizeof(buf) << std::endl;
}

int main() {
    char buf[] = "abc";
    size(buf);
    std::cout << "main char size is " << strlen(buf) << std::endl;
    int* arr = new int(12);
    std::cout << "main int size is " << sizeof(arr) << std::endl;
    
    Thread th("test", test_ano_union);

    return 1;
}