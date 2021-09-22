//
// Created by aris on 2021/9/22.
//

/*         SCTP一对多的服务程序
 *  1. 当客户端关闭关联时,服务端也自动关闭
 *  2. 在第三路和第四路夹带数据的方法是 使用一对多的方式  采用sendto sendmsg sctp_sendmsg
 *  3. 不使用send write发生 除非 sctp_peeloff
 *  4. 关联事件会被发出 除非禁用SCTP_EVENTS
 * */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/sctp.h>

static void print_err(char *msg) __attribute__((noreturn));

static void print_err(char *msg) {
    printf("%s failed, err: %s \n", msg, strerror(errno));
    exit(-1);
}


static void print_addr(struct sockaddr *addr) {
    if (addr == NULL)
        return;
    const char *address;
    char buf[128];
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *in = (struct sockaddr_in *) addr;
        address = inet_ntop(addr->sa_family, &in->sin_addr, buf,
                            INET_ADDRSTRLEN);
    } else if (addr->sa_family == AF_INET6) {
        struct sockaddr_in6 *in = (struct sockaddr_in6 *) addr;
        address = inet_ntop(addr->sa_family, &in->sin6_addr, buf,
                            INET6_ADDRSTRLEN);
    }

    if (address == NULL) {
        print_err("inet_ntop");
    }
    printf("addr is %s \n", address);
}


void sctp_multi_client() {
    int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (client_fd == -1)
        print_err("socket");

    struct timeval val = {
            .tv_sec = 5,
    };

    if (setsockopt(client_fd, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(struct timeval)) == -1)
        print_err("set_sock_opt");

    const char *host_name = "aris";
    struct addrinfo req = {
            .ai_family = AF_UNSPEC,
            .ai_flags = AI_CANONNAME | AI_ADDRCONFIG | AI_V4MAPPED | AI_ALL,
            .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    int err = getaddrinfo(host_name, "socks", &req, &res);
    if (err != 0)
        printf("%s \n", gai_strerror(err));

    if (res == NULL) {
        print_err("get addr info");
    }

#define MAX_SOCK 5
    int count = 0;
    struct sockaddr addr_arr[MAX_SOCK];
    while (res) {
        addr_arr[count] = *(res->ai_addr);
        print_addr(res->ai_addr);
        res = res->ai_next;
        count++;
        if (count >= MAX_SOCK)
            break;
    }

    freeaddrinfo(res);

    if (sctp_connectx(client_fd, addr_arr, count, NULL) == -1)
        print_err("sctp_connect");
}

void sctp_multi_server_test() {
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (server_fd == -1)
        print_err("socket");

    const char *host_name = "aris";
    struct addrinfo req = {
            .ai_family = AF_UNSPEC,
            .ai_flags = AI_CANONNAME | AI_ADDRCONFIG | AI_V4MAPPED | AI_ALL,
            .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    int err = getaddrinfo(host_name, "socks", &req, &res);
    if (err != 0)
        printf("%s \n", gai_strerror(err));

    if (res == NULL) {
        print_err("get addr info");
    }

#define MAX_SOCK 5
    int count = 0;
    struct sockaddr addr_arr[MAX_SOCK];
    while (res) {
        addr_arr[count] = *(res->ai_addr);
        print_addr(res->ai_addr);
        res = res->ai_next;
        count++;
        if (count >= MAX_SOCK)
            break;
    }

    freeaddrinfo(res);

    if (sctp_bindx(server_fd, addr_arr, count, SCTP_BINDX_ADD_ADDR) == -1)
        print_err("sctp_bindx");

    if (listen(server_fd, SOMAXCONN) == -1)
        print_err("listen");

    while (1) {
        int client = accept(server_fd, NULL, NULL);
    }
}


void sctp_multi_options_client_test() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (fd == -1)
        print_err("socket");

    struct sctp_event_subscribe sub = {
            .sctp_data_io_event = 1,
            .sctp_association_event = 1,
            .sctp_send_failure_event = 1,
    };

    if (setsockopt(fd, SOL_SCTP, SCTP_EVENTS, &sub, sizeof(sub)) == -1)
        print_err("set sock opt");

    struct sctp_sndrcvinfo info = {
            .sinfo_timetolive = 1,
    };

    int close_time = 10;
    if (setsockopt(fd, SOL_SCTP, SCTP_AUTOCLOSE, &close_time, sizeof(int)) == -1)
        print_err("auto close");

}

void sctp_server_test() {
    int fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
    if (fd == -1)
        print_err("socket");

    struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_addr = htonl(INADDR_ANY),
            .sin_port = htons(8080),
    };

    if (bind(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr)) == -1)
        print_err("bind");

    if (listen(fd, SOMAXCONN) == -1)
        print_err("listen");

#define BUF_SIZE
    char *buf = (char *) malloc(BUF_SIZE);
    while (1) {
        socklen_t len;
        int flags;
        struct sockaddr addr;
        struct sctp_sndrcvinfo info;
        if (sctp_recvmsg(fd, buf, BUF_SIZ, addr, &len, &info, &flags) == -1)
            print_err("rcv msg");

        if (flags & MSG_NOTIFICATION) {
            printf("rcv kernel msg \n");

            union sctp_notification *notify = (union sctp_notification *) buf;

        }
        printf("rcv msg %s \n", buf);
    }
}


int main() {
    switch (fork()) {
        case 0:
            sleep(2);
            sctp_multi_client();
        case -1:

        default:
            sctp_multi_server_test();
    }
}