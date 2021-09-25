//
// Created by aris on 2021/9/25.
//


#include <poll.h>
#include <arpa/inet.h>

#include "genernal_define.h"


void poll_connect_client() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd == -1)
        bad_exit("client socket");

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        bad_exit("client get flags");

    flags |= O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) == -1)
        bad_exit("client set flags");

    struct sockaddr_storage storage;
    struct sockaddr_in *in = (struct sockaddr_in *) &storage;
    in->sin_family = AF_INET;
    in->sin_port = htonl(12345);
    if (inet_pton(AF_INET, "192.168.1.205", &in->sin_addr) == -1)
        bad_exit("client in_t_p");

    int err = connect(fd, (struct sockaddr *) in, sizeof(struct sockaddr_in));
    if (err == -1) {
        if (errno != EINPROGRESS)
            bad_exit("client connect");
        printf("socket is in progress \n");
    }

#define MAX_POLL 5
    struct pollfd fd_arr[MAX_POLL];
    fd_arr[0].fd = fd;
    fd_arr[0].events = POLLIN | POLLOUT | POLLHUP | POLLERR;

#define MS_TO_SC 1000
    err = poll(fd_arr, 1, 2 * MS_TO_SC);
    if (err == -1)
        bad_exit("poll");

    if (fd_arr[0].revents | POLLERR) {
        int socket_err;
        socklen_t len;
        if (getsockopt(fd_arr[0].fd, SOL_SOCKET, SO_ERROR, &socket_err, &len) == -1)
            bad_exit("get sock opt");
        printf("socket error is %s \n", strerror(socket_err));
    } else {
        printf("no error happens \n");
    }
    printf("poll end %d \n", err);

}

int main() {
    poll_connect_client();
}