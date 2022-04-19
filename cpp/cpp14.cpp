#include <cstdarg>
#include <iostream>
#include <ostream>
#include <type_traits>


template<typename T> 
constexpr T get_value() {
    return T(3.141596);
}


// 变量模板
template<typename T>
constexpr T value = 3.1415;

// lambda模板
auto lambda = [](auto head, auto second) { return head + second; };

// share lock
#include <shared_mutex>
#include <mutex>
class WRLock {
    void set_value(int value) {
        std::unique_lock<std::shared_mutex> lock(mutex);
        value_ = value;
    } 

    int get_value() {
        std::shared_lock<std::shared_mutex> lock(mutex);
        return value_;
    }

private:
    std::shared_mutex mutex;
    int value_ {0};
};


int main() {
    std::cout << "int value is " << get_value<int>() << std::endl;
    std::cout << "double value is " << get_value<double>() << std::endl;

    std::cout << "variant template int is " << value<int> << std::endl;

    std::cout << "lambda value is " << lambda(5, 4.1) << std::endl;

    // digital end;
    std::cout <<"digital is " << 10'000 << std::endl; 

    // out_put(std::cout, "message", 1);

    return 1;
}