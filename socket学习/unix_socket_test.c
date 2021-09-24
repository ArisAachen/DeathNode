//
// Created by aris on 2021/9/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

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


    struct cmsghdr *cmsg;

    int fd = open("/tmp/test.file", O_RDWR | O_CREAT, 0777);
    if (fd == -1) {
        printf("open file failed, err: %s \n", strerror(errno));
        exit(-1);
    }

    printf("open fd success, %d \n", fd);

    struct msghdr msg;
    char rcv_msg[512];
    struct iovec vec[2];

    char *control_len[CMSG_SPACE(sizeof(int))];



    int get_fd;
    switch (fork()) {
        case 0:
            close(pair_fd[1]);
            sleep(2);
            cmsg = CMSG_FIRSTHDR(&msg);
            if (cmsg == NULL) {
                printf("cannot get cmsg \n");
                exit(-1);
            }
            vec[0].iov_base = (void *) rcv_msg;
            vec[0].iov_len = 512;
            msg.msg_control = control_len;
            msg.msg_controllen = sizeof(control_len);
            msg.msg_iov = vec;
            msg.msg_iovlen = 1;
            cmsg->cmsg_type = SOL_SOCKET;
            cmsg->cmsg_level = SCM_RIGHTS;
            cmsg->cmsg_len = CMSG_LEN(sizeof(int));
            *(int *) CMSG_DATA(cmsg) = fd;

            if (sendmsg(pair_fd[0], &msg, 0) == -1) {
                printf("snd failed, err: %s \n", strerror(errno));
                exit(-1);
            }
            printf("snd success \n");
            break;
        case -1:
            printf("fork failed \n");
            break;
        default:
            // parent close fd
            close(fd);
            close(pair_fd[0]);
            vec[0].iov_base = (void *) rcv_msg;
            vec[0].iov_len = 512;
            msg.msg_control = control_len;
            msg.msg_controllen = sizeof(control_len);
            msg.msg_iov = vec;
            msg.msg_iovlen = 1;
            if (recvmsg(pair_fd[1], &msg, 0) == -1) {
                printf("rcv msg failed, err: %s \n", strerror(errno));
                exit(-1);
            }
            printf("rcv success \n");
            for (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
                printf("rcv cmsg \n");
                if (cmsg->cmsg_type == SOL_SOCKET && cmsg->cmsg_level == SCM_RIGHTS) {
                    get_fd = *(int *) CMSG_DATA(cmsg);
                    printf("get fd is %d \n", get_fd);
                }
            }

    }

}


int main() {

    socket_pair_test();


    return 1;
}