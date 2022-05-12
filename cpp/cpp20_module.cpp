#include <string>
export module helloworld;
import <iostream>;
import <string>


export auto hello() {
    std::cout << "hello" << std::endl;
    return std::string("hello world");
}