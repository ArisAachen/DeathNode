#include <iostream>
#include <ostream>

template<typename T>
void out_message(T arg) { 
    std::cout << arg << std::endl; 
}


template<typename Head, typename... Args>
void out_message(Head head, Args... args) {
    std::cout << head << std::endl;
    out_message(args...);
}

template<typename T>
std::ostream & out_put(std::ostream & os, T arg) {
    return os << arg;
}

template<typename Head, typename ...Args>
std::ostream & out_put(std::ostream & os, Head head, Args... args) {
    return out_put(out_put(os, head), args...);
}