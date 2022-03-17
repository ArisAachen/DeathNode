
#include "function.h"
#include <functional>


int func (const std::string & message) 
{
    std::cout << message << std::endl;
    return 1;
}

int func_int (int index) 
{
    return 1;
}

void Func::operator()(const std::string & message)
{
    std::cout << __func__ << std::endl;
}

Func::operator std::string()
{
    std::cout << "convert func is called" << std::endl;
    return "message";
}


void func_test () 
{
    std::cout << __func__ << std::endl;
    func_ptr ptr = func;
    const std::string message ("message");
    ptr(message);


    Func func_arg;
    Func func_caller;
    func_caller(func_arg);

    // functional 必须使用 swap
    std::function<int(const std::string &)> caller = func;
    caller("caller");

    std::function<int(const std::string &)> bind_caller = std::bind(func, "member");
    bind_caller("member");

    
    std::function<int(int)> bind_caller_2 = std::bind(func_int, 1);

#include <tuple>
    auto auto_tuple = std::make_tuple(1, false, "auto tuple");


}