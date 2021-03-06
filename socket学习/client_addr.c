//
// Created by aris on 2021/9/20.
//

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


static void bad_return(void) __attribute__((noreturn));

static void bad_return() {
    printf("method failed, err: %s \n", strerror(errno));
    exit(-1);
}


void basic_client_test() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd == -1) {
        bad_return();
    }

    struct timeval val = {
            .tv_sec = 10,
    };
    if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(struct timeval)) == -1) {
        bad_return();
    }

    int none_block = 1;
    if (setsockopt(fd, SOL_SOCKET, SOCK_NONBLOCK, &none_block, sizeof(int)) == -1) {
        bad_return();
    }

    const char *host = "aris";
    const struct addrinfo info = {
            .ai_flags = AI_CANONNAME | AI_ALL,
            .ai_socktype = SOCK_STREAM,
    };

    struct addrinfo *result;
    const char *port = "80";
    int err = getaddrinfo(host, "80", &info, &result);
    if (err != -1) {
        bad_return();
    }
    while (result) {
        char *buf;
        const char *addr;
        switch (result->ai_family) {
            case AF_INET:
            case AF_INET6:

                addr = inet_ntop(result->ai_family, result->ai_addr, buf,
                                 result->ai_family == AF_INET ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN);
                if (connect(sock_fd, result->ai_addr, sizeof(struct sockaddr)) == -1) {
                    printf("connect to %s failed, err: %s \n", addr, strerror(errno));
                    continue;
                }
                printf("connect to %s success \n", addr);
                break;
            default:
                printf("unknown socket type \n");
                exit(-1);
        }
        result = result->ai_next;
    }

    if (!result) {
        printf("all address not available \n");
        exit(-1);
    }

    // use select
    int fd_in = fileno(stdin);

    struct fd_set rd_set;
    struct fd_set wr_set;
    struct fd_set err_set;

    while (1) {
        FD_ZERO(&rd_set);
        FD_ZERO(&wr_set);
        FD_ZERO(&err_set);

        FD_SET(fd_in, &rd_set);
        FD_SET(sock_fd, &rd_set);

        FD_SET(fd_in, &err_set);
        FD_SET(sock_fd, &err_set);

        FD_SET(sock_fd, &wr_set);

        struct timespec time = {
                .tv_sec = 10,
        };
        if (select(sock_fd + 1, &rd_set, &wr_set, &err_set, &time) == -1) {
            if (errno == EINTR) {
                printf("normal error, err: %s \n", strerror(errno));
                continue;
            }
            printf("unexpected happens, err: %s \n", strerror(errno));
            exit(-1);
        }
    }


}

int main() {
    basic_client_test();
    return 1;
}