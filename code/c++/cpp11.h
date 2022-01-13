#ifndef __CPP_11_H__
#define __CPP_11_H__


#include <functional>
#include <iostream>

class Function 
{
public:
    Function() = delete;
    Function(int arg0);

private:
    Function(int arg0, bool arg1, std::string arg2);


private:
    int argument_int_;
    bool argument_bool_;
    std::string argument_string_;
};





#endif