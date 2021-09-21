//
// Created by aris on 2021/9/21.
//

#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/socket.h>

static void handler(int sig) {

}

void sig_io_test() {

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGIO);

    struct sigaction action = {
            .sa_flags = SA_RESTART,
            .sa_mask = set,
            .sa_handler = handler,
    };

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int flags;
    flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK | O_ASYNC;
    if (fcntl(fd, F_SETFL, &flags) == -1) {

    }

    if (fcntl(fd, F_SETOWN, getpid()) == -1) {

    }


}