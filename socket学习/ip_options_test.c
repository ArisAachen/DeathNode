//
// Created by aris on 2021/9/21.
//

#include <wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <sys/socket.h>

static void sig_handler(int sig) {
    printf("sig is %d \n", sig);

    if (sig == SIGCHLD) {
        while (waitpid(-1, NULL, WNOHANG) > 0)
            continue;
    }
}

void tcp_options_test() {
    sigset_t sigset;
    sigfillset(&sigset);
    struct sigaction action = {
            .sa_mask = sigset,
            .sa_flags = 0,
            .sa_handler = sig_handler,
    };

    if (sigaction(SIGCHLD, &action, NULL) == -1) {
        printf("sig failed \n");
        exit(-1);
    }

    int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd == -1) {
        printf("create socket failed \n");
        exit(-1);
    }

    // for purpose
    int flags = fcntl(sock_fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(sock_fd, F_SETFL, &flags);

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(8080),
    };

    if (bind(sock_fd, (struct sockaddr *) &in, sizeof(struct sockaddr_in)) == -1) {
        printf("bind socket failed \n");
        exit(-1);
    }

    if (listen(sock_fd, SOMAXCONN) == -1) {
        printf("listen socket failed \n");
        exit(-1);
    }

    int type;
    socklen_t length;
    if (getsockopt(sock_fd, SOL_SOCKET, SO_TYPE, &type, &length) == -1) {
        printf("type socket failed \n");
        exit(-1);
    }
    printf("type is %d %s \n", type, type == SOCK_STREAM ? "stream" : "udp");

    int alive;
    if (getsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE, &alive, &length) == -1) {
        printf("alive socket failed \n");
        exit(-1);
    }
    printf("alive time is %d \n", alive);

}


int main() {
    tcp_options_test();
    return 1;
}