//
// Created by aris on 2021/9/21.
//

#include <stdio.h>
#include <poll.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <sys/socket.h>

void poll_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;

#define NUM_FD 5
    struct pollfd poll_fds[NUM_FD];
    poll_fds[0].fd = fd;
    poll_fds[0].events = POLLERR | POLLRDNORM | POLLOUT | POLLHUP;

    for (int index = 1; index < NUM_FD; index++) {
        poll_fds[index].fd = -1;
    }

    while (1) {
        poll(poll_fds, NUM_FD, 5);

        for (int index = 0; index < NUM_FD; index++) {
            if (poll_fds[index].revents & POLLOUT) {
                printf("socket output ready \n");
                break;
            } else if (poll_fds[index].revents & POLLRDNORM) {
                printf("socket input ready \n");
            } else if (poll_fds[index].revents & POLLERR) {
                printf("socket error ready \n");
                return;
            }
        }
    }



}


int main () {

    poll_test();
    return 1;
}