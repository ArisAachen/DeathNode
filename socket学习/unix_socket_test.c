//
// Created by aris on 2021/9/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/un.h>
#include <sys/socket.h>

void unix_client_test() {
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un un = {
            .sun_family = AF_LOCAL,
    };
    char *path = "/tmp/unix.socket";
    strncpy(un.sun_path, path, sizeof(un.sun_path) - 1);
    if (connect(fd, (struct sockaddr *) &un, sizeof(struct sockaddr)) == -1) {
        printf("connect failed \n");
        exit(-1);
    }

    char *text = "this is a msg";
    if (send(fd, text, sizeof(text), 0) == -1) {
        printf("send failed \n");
        exit(-1);
    }

    char *buf = (char *) malloc(512);
    if (recv(fd, buf, 512, 0) == -1) {
        printf("recv failed \n");
        exit(-1);
    }

    printf("client rcv msg iis %s \n", buf);
}

void unix_server_test() {
    int fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct sockaddr_un un = {
            .sun_family = AF_LOCAL,
    };
    char *path = "/tmp/unix.socket";
    strncpy(un.sun_path, path, sizeof(un.sun_path) - 1);
    unlink(path);
    if (bind(fd, (struct sockaddr *) &un, sizeof(struct sockaddr)) == -1) {
        printf("bind failed,err :%s \n", strerror(errno));
        exit(-1);
    }


    if (listen(fd, SOMAXCONN) == -1) {
        printf("listen failed,err :%s \n", strerror(errno));
        exit(-1);
    }

    printf("listen success \n");

    int client = accept(fd, NULL, NULL);

    char *buf = (char *) malloc(512);
    if (recv(client, buf, 512, 0) == -1)
        exit(-1);

    printf("sever rcv msg iis %s \n", buf);

    if (send(client, buf, 512, 0) == -1)
        exit(-1);

    printf("server send success \n");

    close(client);
}


void socket_pair_test() {
    int pair_fd[2];
    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, pair_fd) == -1)
        exit(-1);

    union {
        struct cmsghdr cmg;
        char control_msg[CMSG_SPACE(sizeof(int))];
    } union_cmg;

    struct msghdr msg;
    &union_cmg.cmg = CMSG_FIRSTHDR(&msg);
    union_cmg.cmg.cmsg_type = SOL_SOCKET;
    union_cmg.cmg.cmsg_level = SCM_RIGHTS;
    &union_cmg.control_msg = CMSG_DATA(&union_cmg.cmg);


    switch (fork()) {
        case 0:
            sleep(2);
            send(pair_fd[0], buf, 128, 0);
            break;
        case -1:


        default:
            recv(pair_fd[1], buf, 512, 0);
    }

}


int main() {
    switch (fork()) {
        case 0:
            sleep(3);
            unix_client_test();
            break;
        case -1:
            break;
        default:
            unix_server_test();
            break;
    }


    return 1;
}