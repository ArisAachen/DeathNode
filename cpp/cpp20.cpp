#include <string>
#include <iostream>
#include <string_view>

constexpr std::string_view const_message() {
    return "message";
}

auto larger_int(int & first, int & second) -> int& {
    if (first > second) {
        return first;
    } 
    return second;
}

int main() {
    int first = 1;
    int larger;
    {
        int second = 2;
        larger = larger_int(first, second);
    }
    std::cout << "larger num is " << larger << std::endl;

    return 1;
}