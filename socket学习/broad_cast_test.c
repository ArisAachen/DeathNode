//
// Created by aris on 2021/9/26.
//


/*
 * 多播在ipv4是可选的，在ipv6是必选的
 * ipv6不支持广播
 * 广播和多播可用于ip或者udp  不可用于tcp : arp dhcp
 *
 * */

#include "genernal_define.h"
#include <arpa/inet.h>


void br_client_test() {
    struct sockaddr addr;
    struct sockaddr_in *in = (struct sockaddr_in *) &addr;
    in->sin_family = AF_INET;
    in->sin_port = htons(12345);
    if (inet_pton(AF_INET, "192.168.1.255", &in->sin_addr) == -1)
        bad_exit("inet");

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");

    int on = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(int)) == -1)
        bad_exit("set sock opt");

    char *msg = "broadcast msg";
    if (sendto(fd, msg, sizeof(msg), 0, &addr, sizeof(struct sockaddr)) == -1)
        bad_exit("sendto");

    printf("broadcast client end \n");
}


void br_server_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");

    struct sockaddr_in in = {
            .sin_family =AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(12345),
    };

    if (bind(fd, (struct sockaddr *) &in, sizeof(struct sockaddr)) == -1)
        bad_exit("bind");

#define BUF_SIZE 512
    char *buf = (char *) malloc(BUF_SIZE);
    if (recvfrom(fd, buf, BUF_SIZE, 0, NULL, NULL) == -1)
        bad_exit("recvfrom");

    printf("rcv end, msg: %s \n", buf);
    free(buf);
}

int main() {

    switch (fork()) {
        case 0:
            sleep(4);
            br_client_test();
            break;
        case -1:
            bad_exit("fork");

        default:
            br_server_test();
            break;
    }
    return 1;
}