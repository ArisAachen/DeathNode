//
// Created by aris on 2021/9/24.
//

#include <fcntl.h>
#include "genernal_define.h"

void snd_fd_test() {
    int pair_sock[2];
    struct msghdr msg;
    struct cmsghdr *cmg;
    int cmsg_len;
    struct iovec vec[1];


    int err = socketpair(AF_LOCAL, SOCK_STREAM, 0, pair_sock);
    if (err == -1)
        bad_exit("socket_pair");

    // tmp file
    int tmp_fd = open("/tmp/file", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (tmp_fd == -1)
        bad_exit("open file");

    printf("open fd is %d \n", tmp_fd);

    // msg
    cmsg_len = CMSG_SPACE(sizeof(int));
    char control[cmsg_len];
    msg.msg_control = control;
    msg.msg_controllen = cmsg_len;

    // vec
#define BUF_SIZE 512
    char buf[BUFSIZ];
    vec->iov_base = buf;
    vec->iov_len = BUF_SIZE;
    msg.msg_iov = vec;
    msg.msg_iovlen = 1;

    // cmsg
    cmg = CMSG_FIRSTHDR(&msg);
    cmg->cmsg_len = CMSG_LEN(sizeof(int));
    cmg->cmsg_type = SOL_SOCKET;
    cmg->cmsg_level = SCM_RIGHTS;
    *(int *) CMSG_DATA(cmg) = tmp_fd;

    // text msg
    char *text = "write text msg";

    switch (fork()) {
        case 0:
            sleep(2);
            if (sendmsg(pair_sock[0], &msg, 0) == -1)
                bad_exit("send msg");
            printf("snd msg success \n");
            break;
        case -1:
            bad_exit("fork");
        default:
            if (recvmsg(pair_sock[1], &msg, 0) == -1)
                bad_exit("rcv msg");
            printf("rcv msg success \n");
            for (cmg = CMSG_FIRSTHDR(&msg); cmg; cmg = CMSG_NXTHDR(&msg, cmg)) {
                printf("type is %d, level is %d\n", cmg->cmsg_type, cmg->cmsg_level);
                if (cmg->cmsg_type == SOL_SOCKET && cmg->cmsg_level == SCM_RIGHTS) {
                    tmp_fd = *(int *) CMSG_DATA(cmg);
                    printf("rcv fd is %d \n", tmp_fd);

                    if (write(tmp_fd, text, sizeof(text)) == -1)
                        printf("write text");
                }
            }
            break;
    }

}

int main() {
    snd_fd_test();
    return 1;
}