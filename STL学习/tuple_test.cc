
#include <functional>
#include <tuple>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <limits>
#include <ratio>
#include <chrono>
#include <thread>


class Noncopyable {
public:
    Noncopyable (Noncopyable& );


};

template<typename T, T val>
struct const_type {
    static const T value = val;
    typedef T value_type;
    typedef const_type<T, val> type;
    constexpr operator value_type() {
        return value;
    }
};

typedef const_type<bool, true> true_type;
typedef const_type<bool, false> false_type;


void tuple_elemt() {
    using TupleTest = std::pair<int, std::string>;
    std::cout << "tuple test size is " << std::tuple_size<TupleTest>::value << std::endl; 

    // 以下代码不可行, 因为拷贝构造函数必须为 const 参数
    // std::pair<Noncopyable, std::string> test;

    int i = 0;
    const std::string message = "message";
    std::pair<std::reference_wrapper<int>, std::reference_wrapper<const std::string>> pair_ref (std::ref(i), std::ref(message));
    pair_ref.first++;
    std::cout << "pair ref value is " << i << std::endl;

    auto tuple_tie = std::make_tuple(1, "message", i);
    std::string tuple_message;
    std::tie(i, tuple_message, std::ignore) = tuple_tie;
    i++;
    tuple_message = "change message";
    std::cout << "tuple tie is " << std::get<0>(tuple_tie) << " " << std::get<1>(tuple_tie) << std::endl;

    auto tuple_cat = std::tuple_cat(pair_ref, tuple_tie);

}


void numeric_test() {
    auto lim = std::numeric_limits<int>::min();


}

void type_test() {
    std::cout << "true type is bool type " << std::is_integral<true_type::type>::value << std::endl;

    int a = 0;
    std::add_lvalue_reference<int>::type b = a;
    a++;
    std::cout << "add const value is " << b << std::endl;
}


void radio_test() {
    typedef std::ratio<5, 3> five_third;
    typedef std::ratio<1, 5> one_fifth;
}

void chrono_test() {
    typedef std::ratio<1, 1000> mill;
    std::chrono::duration<int, mill> mill_sec(1000);
    if (mill_sec == std::chrono::seconds(1)) {
        std::cout << "the same" << std::endl;
    } else {
        std::cout << "diff" << std::endl;
    }

    auto last_cur = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    auto dif = std::chrono::system_clock::now() - last_cur;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(dif);
    std::cout << "time pass " << seconds.count() << std::endl;
}

int main() {
    tuple_elemt();
    type_test();
    chrono_test();
    return 0;
}