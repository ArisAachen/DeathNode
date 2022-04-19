#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>


template<typename... Args>
struct Params {};

template<typename Head, typename... Args> 
struct Params<Head, Args...> : public Params<Args...> {

    Params(Head head, Args... args) : Params<Args...>(args...) {
        head_ = head;
    }

    friend std::ostream & operator << (std::ostream & os, Params<Head, Args...> params) {
        os << "member contains " << params.head_ << std::endl << Params<Args...>(params);
        return os;
    }

    Head head_;
};

template<>
struct Params<> {
    friend std::ostream & operator << (std::ostream & os, Params<> params) {
        return os;
    }
};


template<int ...Seq>
struct IndexSeq {
};

template<int Num, int ...Seq>
struct MakeSeq : MakeSeq<Num - 1, Num - 1 , Seq...> {};

template<int ...Seq>
struct MakeSeq<0, Seq...> {
    using typ = IndexSeq<Seq...>;
};

template<typename Func, typename... Args> 
void invoke(Func func, Args... args) {
    func(args...);
}

template<typename Func, int... Seq, typename... Args>
void invoke_helper(Func func, IndexSeq<Seq...>, std::tuple<Args...> elems) {
    invoke(func, std::get<Seq>(elems)...);
}

template<typename Func, typename... Args>
void delay_call(Func func, Args... args) {
    std::tuple<typename std::decay<Args>::type...> elems {args...};
    invoke_helper(func, typename MakeSeq<sizeof...(Args)>::typ(), elems);
}

void test_print(int index, std::string message, double fnum) {
    std::cout << index << message << fnum << std::endl;
}

int main() {
    Params<int, int, std::string> result(1, 2, "message");

    delay_call(test_print, 1, "message", 1.0);

    return 1;
}