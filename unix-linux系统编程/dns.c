#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void hostbyname_test() {
    struct hostent *ent = gethostbyname("baidu.com");
    if (ent == NULL) {
        printf("get host by name failed, err: %s \n", strerror(errno));
        return;
    }
    printf("official name: %s \n", ent->h_name);
    for (char** buf = ent->h_aliases; *buf != NULL; buf++) {
        printf("alias name is %s \n", *buf);
    }
    printf("name type is %d \n", ent->h_addrtype);
    for (char** buf = ent->h_addr_list; *buf != NULL; buf++) {
        char msg[INET_ADDRSTRLEN];
        inet_ntop(ent->h_addrtype, *buf, msg, INET_ADDRSTRLEN);
        printf("addr is : %s \n", msg);
    }
}

void hostbyaddr_test() {
    struct sockaddr_in addr;
    if (inet_pton(AF_INET, "220.181.38.251", &addr.sin_addr) == -1) {
        printf("convert addr failed, err: %s \n", strerror(errno));
        return;
    }
    struct hostent *ent = gethostbyaddr(&addr.sin_addr, INET_ADDRSTRLEN, AF_INET);
    if (ent == NULL) {
        printf("get host by name failed, err: %s \n", strerror(errno));
        return;
    }
    printf("official name: %s \n", ent->h_name);
    for (char** buf = ent->h_aliases; *buf != NULL; buf++) {
        printf("alias name is %s \n", *buf);
    }
    printf("name type is %d \n", ent->h_addrtype);
    for (char** buf = ent->h_addr_list; *buf != NULL; buf++) {
        char msg[INET_ADDRSTRLEN];
        inet_ntop(ent->h_addrtype, *buf, msg, INET_ADDRSTRLEN);
        printf("addr is : %s \n", msg);
    }
}

void addrinfo_test() {
    struct addrinfo info, *result;
    memset(&info, 0, sizeof(info));
    info.ai_flags = AI_CANONNAME;
    info.ai_family = AF_UNSPEC;
    int err = getaddrinfo("baidu.com", NULL, &info, &result);
    if (err != 0) {
        printf("get addr info failed, err: %s", gai_strerror(err));
        return;
    }
    for (struct addrinfo *pre = result; pre != NULL; pre = pre->ai_next) {
        printf("addr name is: %s \n", pre->ai_canonname);
        char buf[INET6_ADDRSTRLEN];
        if (strcmp(inet_ntop(pre->ai_family, pre->ai_addr, buf, INET6_ADDRSTRLEN), "") == 0) {
            printf("convert failed, err: %s \n", strerror(errno));
            continue;
        }
        printf("addr is : %s \n", buf);
        printf("addr type is: %d \n", pre->ai_socktype);
        printf("add protocol is: %d \n", pre->ai_protocol);
    }
    freeaddrinfo(result);
}

void nameinfo_test() {
    // getnameinfo(const struct sockaddr *, socklen_t, char *, socklen_t, char *, socklen_t, int)
}

int main() {
    printf(">>>>>> by name\n");
    hostbyname_test();
    printf(">>>>>> by addr\n");
    hostbyaddr_test();
    printf(">>>>>> addr info \n");
    addrinfo_test();
    return 1;
}