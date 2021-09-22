//
// Created by aris on 2021/9/21.
//


#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>


void print_err(char *msg) {
    printf("%s failed, err: %s \n", msg, strerror(errno));
    exit(-1);
}


void sctp_single_client_test() {
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (fd == -1) {
        print_err("create socket");
    }

    struct timeval val = {
            .tv_sec = 5,
    };

    if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(struct timeval)) == -1) {
        print_err("set timeout");
    }

    struct sockaddr_in ipv4 = {
            .sin_family = AF_INET,
            .sin_port = htons(1080),
    };

    if (inet_pton(AF_INET, "192.168.1.206", &ipv4.sin_addr) == -1) {
        print_err("convert address");
    }

    if (connect(fd, (struct sockaddr *) &ipv4, sizeof(struct sockaddr)) == -1) {
        print_err("connect");
    }

    while (1) {
        char *msg = "this is a test msg \n";
        if (write(fd, msg, sizeof(msg)) == -1) {
            if (errno == EINTR)
                continue;
            print_err("write");
        }
        char *buf = (char *) malloc(512);
        if (read(fd, buf, 512) == -1) {
            free(buf);
            if (errno == EINTR)
                continue;
            print_err("read");
        }
        printf("client rcv msg is %s \n", buf);
        free(buf);
        sleep(2);
    }
}

void sctp_single_server_test() {

    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (fd == -1) {
        print_err("create socket");
    }

    struct timeval val = {
            .tv_sec = 5,
    };

    if (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &val, sizeof(struct timeval)) == -1) {
        print_err("set timeout");
    }

    struct sockaddr_in ipv4 = {
            .sin_family = AF_INET,
            .sin_port = htons(1080),
    };

    if (inet_pton(AF_INET, "192.168.1.206", &ipv4.sin_addr) == -1) {
        print_err("convert address");
    }

    if (bind(fd, (struct sockaddr *) &ipv4, sizeof(struct sockaddr)) == -1) {
        print_err("bind");
    }

    if (listen(fd, SOMAXCONN) == -1) {
        print_err("listen");
    }


    int ac_fd = accept(fd, NULL, NULL);
    if (ac_fd == -1) {
        print_err("accept");
    }

    char *buf = (char *) malloc(512);
    while (1) {
        if (read(ac_fd, buf, 512) == -1) {
            if (errno == EINTR)
                continue;
            print_err("write");
        }
        printf("server rcv msg is %s \n", buf);

        if (write(ac_fd, buf, 512) == -1) {
            if (errno == EINTR)
                continue;
            print_err("read");
        }
    }
}





int main() {

    switch (fork()) {
        case 0:
            sleep(2);
            sctp_single_client_test();
        default:
            sctp_single_server_test();
    }
    return 1;
}