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

struct CheckType {
    int checksum_ {1};
    std::string message_ {"check sum type"};

    CheckType();
    CheckType(const CheckType &);
    CheckType(CheckType &&);

    CheckType& operator=(CheckType &);
    CheckType&& operator=(CheckType &&);

    ~CheckType();
};


template <typename Type, Type v>
struct base_constant {
    static const Type value = v;
    using value_type = Type;
    using base_type = base_constant<Type, v>;
    value_type operator() {return v;}
};




#include <type_traits>
template <typename Type>
void switch_test(Type && arg0, Type && arg1);





#endif