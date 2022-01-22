//
// Created by aris on 2021/9/24.
//

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ucontext.h>


void ucontext_call() {
    printf("call func \n");
}

int main() {
#define BUF_SIZE 1024
    char buf[BUFSIZ];
    ucontext_t cur_ctx;
    ucontext_t tar_ctx;


    getcontext(&cur_ctx);
    tar_ctx.uc_link = &cur_ctx;
    tar_ctx.uc_stack.ss_sp = buf;
    tar_ctx.uc_stack.ss_size = BUFSIZ;
    makecontext(&tar_ctx, ucontext_call, 0);

    getcontext(&tar_ctx);
    setcontext(&tar_ctx);

    // ucontext_t cur_ctx;
    // ucontext_t tar_ctx;

    // getcontext(&tar_ctx);


    // char buf[1024];
    // tar_ctx.uc_link = &cur_ctx;
    // tar_ctx.uc_stack.ss_sp = buf;
    // tar_ctx.uc_stack.ss_size = sizeof(buf);
    // makecontext(&tar_ctx,ucontext_call,0);

    // // execute twice
    // getcontext(&cur_ctx);
    // setcontext(&tar_ctx);

    printf("end \n");

    return 1;
}