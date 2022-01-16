#ifndef __TEMPLATE_CPP_11_TEST__
#define __TEMPLATE_CPP_11_TEST__

// 模板表达式参数
// template <typename Type, int n>
// 指出了 Type是一种类型, n是一种int类型的参数

#include <iostream>
#include <string>

constexpr int const_message_len() {
    return 512;
}

struct SimplePod {
    int typ;
};

struct CheckType {
    int checksum_ {1};
    std::string message_ {"check sum type"};

    CheckType();
    CheckType(const CheckType &);
    CheckType(CheckType &&);

    CheckType& operator=(CheckType &);
    CheckType& operator=(CheckType &&);

    ~CheckType();
};

std::ostream & operator << (std::ostream & out, CheckType & typ);

template <typename Type, Type v>
struct base_constant {
    static const Type value = v;
    using value_type = Type;
    using base_type = base_constant<Type, v>;
    operator value_type () {return v;}
};




#include <type_traits>
template <typename Type>
void switch_test(Type && arg0, Type && arg1);



template <typename Type, typename... Types>
void output(Type head, Types... args) 
{
    std::cout << head << std::endl;
    output(args...);
}

template <typename Type>
void output(Type arg)
{
    std::cout << arg << std::endl;
}



void switch_run();
void output_test();
void optional_test();


#endif