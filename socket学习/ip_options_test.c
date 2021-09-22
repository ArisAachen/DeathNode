//
// Created by aris on 2021/9/21.
//

#include <wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <arpa/inet.h>
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

void send_rst() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct linger num = {
            .l_onoff = 1,
            .l_linger = 0,
    };

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_port = htons(80),
    };

    int err = inet_pton(AF_INET, "127.0.0.1", &in.sin_addr);

    connect(fd, (struct sockaddr *) &in, sizeof(struct sockaddr));
    close(fd);
}


void reuse_test() {

    int fd_1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int fd_2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int fd_3 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int allow = 1;
    if (setsockopt(fd_1, SOL_SOCKET, SO_REUSEADDR, &allow, sizeof(int)) == -1) {
        printf("first reuse failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    if (setsockopt(fd_2, SOL_SOCKET, SO_REUSEADDR, &allow, sizeof(int)) == -1) {
        printf("second reuse failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    if (setsockopt(fd_3, SOL_SOCKET, SO_REUSEADDR, &allow, sizeof(int)) == -1) {
        printf("third reuse failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    struct sockaddr_in in_1 = {
            .sin_family = AF_INET,
            .sin_port = htons(1080),
    };
    int err = inet_pton(AF_INET, "192.168.1.208", &in_1.sin_addr);
    if (err == -1) {
        printf("first addr failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    struct sockaddr_in in_2 = {
            .sin_family = AF_INET,
            .sin_port = htons(1080),
    };
    err = inet_pton(AF_INET, "192.168.1.205", &in_2.sin_addr);
    if (err == -1) {
        printf("second addr failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    struct sockaddr_in in_3 = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(1080),
    };

    // error
    if (bind(fd_1, (struct sockaddr *) &in_1, sizeof(struct sockaddr)) == -1) {
        printf("first bind failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    // error
    if (bind(fd_2, (struct sockaddr *) &in_2, sizeof(struct sockaddr)) == -1) {
        printf("second bind failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    // error
    if (bind(fd_3, (struct sockaddr *) &in_3, sizeof(struct sockaddr)) == -1) {
        printf("third bind failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    printf("bind all success \n");
}

void reuse_port_test() {
    int fd_1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int fd_2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int allow = 1;
    if (setsockopt(fd_1, SOL_SOCKET, SO_REUSEPORT, &allow, sizeof(int)) == -1) {
        printf("first reuse failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    if (setsockopt(fd_2, SOL_SOCKET, SO_REUSEPORT, &allow, sizeof(int)) == -1) {
        printf("second reuse failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    struct sockaddr_in in_1 = {
            .sin_family = AF_INET,
            .sin_port = htons(1080),
    };
    int err = inet_pton(AF_INET, "192.168.1.208", &in_1.sin_addr);
    if (err == -1) {
        printf("first addr failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    // error
    if (bind(fd_1, (struct sockaddr *) &in_1, sizeof(struct sockaddr)) == -1) {
        printf("first bind failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    // error
    if (bind(fd_2, (struct sockaddr *) &in_1, sizeof(struct sockaddr)) == -1) {
        printf("second bind failed, err: %s \n", strerror(errno));
        exit(-1);
    }
}

int main() {
    reuse_port_test();
    return 1;
}