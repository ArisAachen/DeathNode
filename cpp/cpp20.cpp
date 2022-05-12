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

#include <string>
// Designated Initializer
struct Designated {
    std::string name = "member";
    int age = 12;
};
void Designated_Initializer() {
    Designated member {
        .name = "ok",
        .age = 12,
    };
}

// pack-expansions in lambda init-captures
void lambda_test() {
        // [=, this]{
        //     std::cout << typeid(this).name() << this->val << std::endl;
        // }();    //从 C++20, 传引用捕获 this
}

// 3-way comparison operator <=> and operator==() = default
#include <compare>
#include <iostream>
void three_test() {
    // clang 当前不支持  g++ 支持
    // double foo = -0.0;
    // double bar = 0.0;
 
    // auto res = foo <=> bar;
 
    // if (res < 0)
    //     std::cout << "-0 is less than 0";
    // else if (res > 0)
    //     std::cout << "-0 is greater than 0";
    // else // (res == 0)
    //     std::cout << "-0 and 0 are equal";
}

// init-statements and initializers in range-for
#include <vector>
void for_range_test() {
    std::vector<int> vec = {1, 2, 3};
    for (int size = vec.size(); auto elem : vec) {
        std::cout << size << elem << std::endl;
    }
}

// modules

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