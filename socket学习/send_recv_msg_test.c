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

    if (inet_pton(AF_INET, "10.20.43.54", &in.sin_addr) == -1)
        print_err("ntop");

#define COUNT_VEC 5
    struct iovec vec[COUNT_VEC];
    memset(&vec, 0, sizeof(struct iovec) * COUNT_VEC);
    char *text = "this is a test msg";
    vec[0].iov_base = text;
    vec[0].iov_len = sizeof(text);

    struct msghdr msg = {
            .msg_name = (void *) &in,
            .msg_namelen = INET_ADDRSTRLEN,
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

    int allow = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &allow, sizeof(int)) == -1)
        print_err("reuse port");

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(1080),
    };

    if (bind(fd, (struct sockaddr *) &in, sizeof(struct sockaddr)) == -1)
        print_err("bind");

    printf("bind end \n");

    struct sockaddr_in in_1;
    struct cmsghdr get_head;
    struct msghdr msg = {
            .msg_name = &in_1,
            .msg_control = (void *)&get_head,
            .msg_controllen = CMSG_SPACE(sizeof(struct cmsghdr)),
    };

    if (recvmsg(fd, &msg, 0) == -1)
        print_err("rcv msg");

    printf("rcv end \n");
    for (struct cmsghdr *title = CMSG_FIRSTHDR(&msg); title; title = CMSG_NXTHDR(&msg, title)) {
        printf("level is %d, type is %d \n", title->cmsg_level, title->cmsg_type);
        if (title->cmsg_level == SOL_SOCKET && title->cmsg_type == SO_RCVTIMEO) {
            struct timeval *val = (struct timeval *) CMSG_DATA(title);
            printf("time val tcv time val is %ld \n", val->tv_sec);
        }
    }

}


int main() {

    switch (fork()) {
        case 0:
            sleep(5);
            udp_send_msg_test();
            break;
        case -1:

        default:
            udp_rcv_msg_test();
            break;
    }

    return 1;
}