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


template <typename ...Args>
class Params {
// public:
//     friend std::ostream & operator << (std::ostream & os, Params<Args...> params) {
        
//     }
};

template<typename Head, typename ...Args> 
class Params<Head, Args...> : private Params<Args...> {
public:
    friend std::ostream & operator << (std::ostream & os, Params<Head, Args...> params) {
        return std::cout << params.head << Params<Args...>(params);
    }
private:
    Head head;
};

template <>
class Params<> {
};

int main() {
    out_put(std::cout, "message", " ", 1) << std::endl;
    return 1;
}