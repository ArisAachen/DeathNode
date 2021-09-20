//
// Created by aris on 2021/9/19.
//

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netinet/in.h>

void print_ntoa() {
    struct sockaddr_in ipv4_addr = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_LOOPBACK),
            .sin_port = ntohs(43),
    };
    char *buf;
    buf = inet_ntoa(ipv4_addr.sin_addr);
    if (!strcmp(buf, "")) {
        printf("convert network to address failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    printf("convert network to address, address: %s \n", buf);
}


void print_aton() {
    struct sockaddr_in get_addr;
    char *address = "127.0.0.1";
    int err = inet_aton(address, &get_addr.sin_addr);
    if (err == -1) {
        printf("convert address to network failed, err: %s", strerror(errno));
        exit(-1);
    }
    printf("convert address to netwoprk success \n");
}

void print_ntop() {
    struct sockaddr_in ipv4_addr = {
            .sin_family =AF_INET,
            .sin_port = htons(443),
            .sin_addr = htonl(INADDR_ANY),
    };

    char *address;
    const char *buf_ipv4 = inet_ntop(AF_INET, &ipv4_addr.sin_addr, address, INET_ADDRSTRLEN);
    if (!strcmp(address, "")) {
        printf("convert network to address failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    printf("convert ipv4 network to address, address: %s \n", address);

    struct sockaddr_in6 ipv6_addr = {
            .sin6_family =AF_INET6,
            .sin6_port = htons(443),
            .sin6_addr = IN6ADDR_ANY_INIT,
    };
    const char *buf_ipv6 = inet_ntop(AF_INET6, &ipv6_addr.sin6_addr, address, INET6_ADDRSTRLEN);
    if (!strcmp(address, "")) {
        printf("convert network to address failed, err: %s \n", strerror(errno));
        exit(-1);
    }
    printf("convert ipv6 network to address, address: %s \n", address);
}


void print_pton() {
    char *address = "127.0.0.1";
    struct sockaddr_in ipv4_addr;
    if (inet_pton(AF_INET, address, &ipv4_addr.sin_addr) == -1) {
        printf("convert address to network failed, err: %s", strerror(errno));
        exit(-1);
    }
    printf("convert address to netwoprk success \n");
}


int main() {
    print_ntoa();
    print_aton();
    print_ntop();
    print_pton();
    return 1;
}

