//
// Created by aris on 2021/9/22.
//

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/uio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>


static void print_err(char *msg) {
    printf("%s failed, err: %s \n", msg, strerror(errno));
    exit(-1);
}


void udp_send_msg_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        print_err("socket");

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_port = htons(1080),
    };

    if (inet_pton(AF_INET, "192.168.1.205", &in.sin_addr) == -1)
        print_err("ntop");

#define COUNT_VEC 5
    struct iovec vec[COUNT_VEC];
    memset(&vec, 0, sizeof(struct iovec) * COUNT_VEC);
    char *text = "this is a test msg";
    vec[0].iov_base = text;
    vec[0].iov_len = sizeof(text);

    struct msghdr msg = {
            .msg_control = &in,
            .msg_controllen = INET_ADDRSTRLEN,
            .msg_iov = vec,
            .msg_iovlen = 1,
            .msg_flags = 0,
    };

    if (sendmsg(fd, &msg, 0) == -1)
        print_err("send msg");

}


void udp_rcv_msg_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        print_err("socket");

    struct timeval val = {
            .tv_sec = 10,
    };
    if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &val, sizeof(struct timeval)) == -1)
        print_err("set sock opt");

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(1080),
    };

    if (bind(fd, (struct sockaddr *) &in, sizeof(struct sockaddr)) == -1)
        print_err("bind");

    struct iovec vec[COUNT_VEC];
    struct msghdr msg = {
            .msg_iov = vec,
            .msg_iovlen = COUNT_VEC,
    };

    if (recvmsg(fd, &msg, 0) == -1)
        print_err("rcv msg");


    for (struct cmsghdr *title = CMSG_FIRSTHDR(&msg); title; title = CMSG_NXTHDR(&msg, title))
        printf("level is %d, type is %d \n", title->cmsg_level, title->cmsg_type);
}


int main() {

    switch (fork()) {
        case 0:
            sleep(2);
            udp_send_msg_test();
        case -1:

        default:
            udp_rcv_msg_test();
    }

    return 1;
}