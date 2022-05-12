#include <exception>
#include <iostream>

// fold expressions
template<typename... Args>
void print_args(Args... args) {
    (std::cout << ... << args) << std::endl;
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

int main() {
    print_args(1, 2);
    any_test();
    optional_test();
}