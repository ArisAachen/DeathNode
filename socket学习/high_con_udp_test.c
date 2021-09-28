//
// Created by aris on 2021/9/28.
//

#include "genernal_define.h"

#include <arpa/inet.h>

void udp_client_test() {

    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");

    int allow = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &allow, sizeof(int)) == -1)
        bad_exit("reuse");

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_port = htons(12345),
    };

    if (inet_pton(AF_INET, "10.20.43.195", &in.sin_addr) == -1)
        bad_exit("inet");

    char *test = (char *) malloc(BUFSIZ);
    strncpy(test, "test msg", sizeof("test msg"));

    while (1) {
        if (sendto(fd, test, sizeof(test), 0, (struct sockaddr *) &in, sizeof(struct sockaddr)) == -1)
            bad_exit("sendto");

        printf("client snd end \n");

        if (recvfrom(fd, test, BUFSIZ, 0, NULL, NULL) == -1)
            bad_exit("client rcv end \n");

        printf("client rcv end, msg is %s \n", test);
    }
}