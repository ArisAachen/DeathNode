//
// Created by aris on 2021/9/27.
//

#include "genernal_define.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>

int multi_server_test() {

    int index = if_nametoindex("eno1");
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


    struct ip_mreqn req = {
            .imr_ifindex = index,
            .imr_address = htonl(INADDR_ANY),
            .imr_multiaddr = s_multi_addr,
    };

    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &req, sizeof(struct ip_mreqn)) == -1)
        bad_exit("add member");

#define BUF_SIZE 512
    char *buf = (char *) malloc(BUF_SIZE);

    if (recvfrom(fd,buf,BUF_SIZE,0,NULL,NULL) == -1)
        bad_exit("rcv from");

    printf("rcv message is %s \n",buf);
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

    if (inet_pton(AF_INET, "224.1.2.1", &snd_addr.sin_addr) == -1)
        bad_exit("multi inet");

    char *msg = "only for test";

    if(sendto(fd,msg, sizeof(msg),0,(struct sockaddr*)&snd_addr, sizeof(struct sockaddr)) == -1)
        bad_exit("sendto");

    printf("snd end \n");
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