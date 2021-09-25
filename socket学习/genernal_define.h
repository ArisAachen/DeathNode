//
// Created by aris on 2021/9/24.
//

#ifndef DEATHNODE_GENERNAL_DEFINE_H
#define DEATHNODE_GENERNAL_DEFINE_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <sys/socket.h>

void bad_exit(char *msg) __attribute__((noreturn));

void bad_exit(char *msg) {
    printf("%s failed, err: %s \n",msg, strerror(errno));
    exit(-1);
}




#endif //DEATHNODE_GENERNAL_DEFINE_H
