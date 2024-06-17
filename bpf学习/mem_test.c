#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int call_malloc() {
    sleep(30);
    char* mem = malloc(1024);
    sleep(10);
    return 0;
}


int main() {
    call_malloc();
}



