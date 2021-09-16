//
// Created by aris on 2021/9/1.
//

#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <poll.h>

char *sock_top(struct sockaddr *address, socklen_t socklen) {
    // is ipv4
    static char buf[128];
    char port_char[8];

    if (address->sa_family == AF_INET) {
        struct sockaddr_in *in = (struct sockaddr_in *) address;
        if (inet_ntop(AF_INET, in->sin_addr, buf) == -1) {
            printf("convert to ipv4 failed, err: %s", strerror(errno));
            return "";
        }
        snprintf(port_char, sizeof(port_char), ":%d", ntohs(in->sin_port));
        strcat(buf,port_char);
    } else if (address->sa_family == AF_INET6) {
        struct sockaddr_in6 *in6 = (struct sockaddr_in6 *) address;
        if (inet_ntop(AF_INET, in6->sin_addr, buf) == -1) {
            printf("convert to ipv4 failed, err: %s", strerror(errno));
            return "";
        }
    }
    return buf;
}