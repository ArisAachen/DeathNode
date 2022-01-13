#include "cpp11.h"


Function::Function(int arg0):
Function(arg0, false, "")
{

}

Function::Function(int arg0, bool arg1, std::string arg2):
argument_int_(arg0),
argument_bool_(arg1),
argument_string_(arg2)
{

}