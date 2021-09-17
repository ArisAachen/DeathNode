//
// Created by aris on 2021/8/30.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>
#include <sys/socket.h>

void fast_return(void) __attribute__((noreturn));

void fast_return(void) {
    printf("error happens, err: %s \n", strerror(errno));
    exit(-1);
}

//
int main(int argc, char **argv) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // define server address
    struct sockaddr_in server_add;
    memset(&server_add, 0, sizeof(struct sockaddr_in));
    server_add.sin_family = AF_INET;
    if (inet_pton(AF_INET, argv[1], server_add.sin_addr) == -1) {
        fast_return();
    }

    // try to connect
    if (connect(fd, (struct sockaddr *) server_add, sizeof(struct sockaddr_in)) == 1) {
        fast_return();
    }

    char *buf;
    buf = malloc(512);

    // begin to read
    while (1) {
        if (read(fd, buf, sizeof(buf)) == -1) {
            if (errno == EINTR) {


                printf("signal break, continue to read \n");
                continue;
            }
            free(buf);
            fast_return();
        }
        if (fputs(buf, stdout) == -1) {
            free(buf);
            fast_return();
        }
    }
}