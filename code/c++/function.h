#ifndef __FUNC_CPP_11__
#define __FUNC_CPP_11__

#include <string>
#include <iostream>




typedef int (*func_ptr)(const std::string & message);

int func (const std::string & message);
void func_test ();

class Func 
{
public:
    void operator()(const std::string &);
    operator std::string();
private:
};



#endif