#include <cstdio>
#include <exception>
#include <iostream>
#include <string>

// fold expressions
template<typename... Args>
void print_args(Args... args) {
    std::cout << (... << args) << std::endl;
}

template<typename... Args> 
void printfs(std::string& msg, Args... args) {
    std::printf(msg, args...);
}

#include <any>
void any_test() {
    std::any value = "message";
    std::cout << value.type().name() << std::endl;
    try {
        int num = std::any_cast<int>(value);
    } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
}

#include <optional>
void optional_test() {
    std::optional<int> value(std::nullopt);
    if (value) {
        std::cout << "has value" << std::endl;
    } else {
        std::cout << "has no value" << std::endl;
    }
}

#include <variant> 
void variant_test() {
    std::variant<int, double> value;
    value = 1;
    std::visit([](double num) {
        std::cout << "value is " << num << std::endl;
    }, value);
}



int main() {
    print_args(1, 2);
    any_test();
    optional_test();
}