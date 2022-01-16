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

CheckType & CheckType::operator=(CheckType & type) 
{
    this->checksum_ = type.checksum_;
    this->message_ = type.message_;
    std::cout << "duplicate equal is called" << std::endl;
    return *this;
}

CheckType & CheckType::operator=(CheckType && type) 
{
    this->checksum_ = type.checksum_;
    this->message_ = type.message_;
    std::cout << "move equal is called" << std::endl;
    return *this;
}

CheckType::~CheckType() 
{
    std::cout << "release is called" << std::endl;
}

std::ostream & operator << (std::ostream & out, CheckType & typ)
{
    return out << "check sum is " << typ.checksum_ << " message is " << typ.message_; 
}


template <typename Type>
void switch_test(Type && arg0, Type && arg1) 
{
    // check type
    if (std::is_same<Type, CheckType &&>::value) {
        std::cout << "type is not check type" << std::endl;
        return;
    }
    // switch
    Type && tmp = std::forward<CheckType>(arg0);
    arg0 = std::forward<CheckType>(arg1);
    arg1 = tmp;
}

void switch_run() 
{
    CheckType param_first;
    param_first.checksum_ = 1; 
    param_first.message_ = "first";

    CheckType param_second;
    param_second.checksum_ = 2;
    param_second.message_ = "second";


    switch_test(std::move(param_first), std::move(param_second));   

    std::cout << "first is " << param_first << ", second is " << param_second << std::endl;

}

void output_test()
{
    std::cout << "output test begin" << std::endl;
    output(1 ,false ,CheckType{});
    std::cout << "output test end" << std::endl;
}


#include <optional>
void optional_test()
{



}