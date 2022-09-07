#ifndef CALL 
#define CALL

#include <stdio.h>

void call_delay() {
    printf("call delay \n");
}

void call_func() {
    printf("call \n");
    call_delay();
}



#endif