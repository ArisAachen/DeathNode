//
// Created by aris on 2021/9/27.
//

#include "genernal_define.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>

int multi_server_test() {

    int index = if_nametoindex("wlp61s0");
    if (index == -1)
        bad_exit("if index");

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");

    struct sockaddr_in rcv_addr = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(12345),
    };

    if (bind(fd, (struct sockaddr *) &rcv_addr, sizeof(struct sockaddr)) == -1)
        bad_exit("bind");

    struct in_addr s_multi_addr;
    if (inet_pton(AF_INET, "224.1.1.1", &s_multi_addr) == -1)
        bad_exit("multi inet");

#ifdef IP_ADD_MEMBERSHIP_TEST
    struct ip_mreqn req = {
            .imr_ifindex = index,
            .imr_address = htonl(INADDR_ANY),
            .imr_multiaddr = s_multi_addr,
    };

    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &req, sizeof(struct ip_mreqn)) == -1)
        bad_exit("add member");
#else
    struct group_req req = {
            .gr_interface = index,
    };
    rcv_addr.sin_addr = s_multi_addr;
    memcpy(&req.gr_group, &rcv_addr, sizeof(struct sockaddr_in));
    if (setsockopt(fd, IPPROTO_IP, MCAST_JOIN_GROUP, &req, sizeof(struct group_req)) == -1)
        bad_exit("mcast join");
#endif

#define BUF_SIZE 512
    char *buf = (char *) malloc(BUF_SIZE);

    if (recvfrom(fd, buf, BUF_SIZE, 0, NULL, NULL) == -1)
        bad_exit("rcv from");

    printf("rcv message is %s \n", buf);
    free(buf);

    return 1;
}

int multi_client_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");


    struct sockaddr_in snd_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(12345),
    };

    if (inet_pton(AF_INET, "224.0.0.1", &snd_addr.sin_addr) == -1)
        bad_exit("multi inet");

    char *msg = "only for test";

    if (sendto(fd, msg, sizeof(msg), 0, (struct sockaddr *) &snd_addr, sizeof(struct sockaddr)) == -1)
        bad_exit("sendto");

    printf("snd end \n");

    return 1;
}


int main() {
    switch (fork()) {
        case 0:
            sleep(5);
            multi_client_test();
            break;
        case -1:
            bad_exit("fork");

        default:
            multi_server_test();
    }
    return 1;
}