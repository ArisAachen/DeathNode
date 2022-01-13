#include "template_cpp11_test.h"


CheckType::CheckType()
{
    std::cout << "simple is called" << std::endl;
}

CheckType::CheckType(const CheckType & out)
{
    this->checksum_ = out.checksum_;
    this->message_ = out.message_;
    std::cout << "duplicate is called" << std::endl;
}

CheckType::CheckType(CheckType && out)
{
    this->checksum_ = out.checksum_;
    this->message_ = std::move(out.message_);
    std::cout << "move is called" << std::endl;
}

CheckType::~CheckType() 
{
    std::cout << "release is called" << std::endl;
}


template <typename Type>
void switch_test(Type && arg0, Type && arg1) 
{
    // check type
    if (std::is_same<Type, CheckType &&>::value) {
        std::cout << "type is not check type" << std::endl;
        return
    }

    if (std::is_rvalue_reference)

    // 
    Type && tmp = std::forward(arg0);
    arg0 = std::forward(arg1);
    arg1 = tmp;
}