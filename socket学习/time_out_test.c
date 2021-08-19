//
// Created by aris on 2021/8/19.
//
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <sys/un.h>

#include <netinet/in.h>

void bad_return(void) __attribute__((noreturn));

void bad_return(void) {
    exit(-1);
}

void signal_func(int signal, siginfo_t *info, void *context) {
    printf("accept signal %d \n", signal);
}

void alarm_time_out(int fd) {
    sigset_t set;
    sigfillset(&set);

    struct sigaction action = {
            .sa_flags = SA_SIGINFO,
            .sa_mask = set,
            .sa_sigaction = signal_func,
    };

    if (sigaction(SIGALRM, &action, NULL) == -1) {
        printf("action failed, err: %s", strerror(errno));
        bad_return();
    }

    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("action failed, err: %s", strerror(errno));
        bad_return();
    }

    struct sockaddr_un ay_path;
    memset(&ay_path, 0, sizeof(struct sockaddr_un));
    ay_path.sun_family = AF_LOCAL;
    strncpy(&ay_path.sun_path[1], "ay_socket", sizeof(ay_path.sun_path) - 2);

    alarm(5);

    if (connect(fd, (struct sockaddr *) &ay_path, sizeof(struct sockaddr)) == -1) {
        printf("connect failed, err: %s \n", strerror(errno));
        bad_return();
    }
}


void select_time_out() {
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un ay_path;
    memset(&ay_path, 0, sizeof(struct sockaddr_un));
    ay_path.sun_family = AF_LOCAL;
    strncpy(&ay_path.sun_path[1], "ay_socket", sizeof(ay_path.sun_path) - 2);
    if (connect(fd, (struct sockaddr *) &ay_path, sizeof(struct sockaddr)) == -1) {
        printf("connect failed, err: %s \n", strerror(errno));
        bad_return();
    }

    int flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);

    fd_set set;
    FD_ZERO(&set);
    FD_SET(fd, set);

    struct timespec spec = {
            .tv_sec = 5,
            .tv_nsec = 0,
    };
    while (select(fd + 1, &set, NULL, NULL, spec) == -1) {
        if (errno == EINTR) {
            continue;
        }
        printf("connect failed, err: %s \n", strerror(errno));
        bad_return();
    }
}

void opt_time_out(int fd) {
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &5, sizeof(int ));
}


int main() {


    return 1;
}