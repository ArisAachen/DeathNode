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


    int err = socketpair(AF_LOCAL,SOCK_STREAM,0,pair_sock);
    if (err == -1)
        bad_exit("socket_pair");

    // tmp file
    int tmp_fd = open("/tmp/file",O_CREAT|O_RDWR,0777);
    if (tmp_fd == -1)
        bad_exit("open file");

    // msg
    cmsg_len = CMSG_SPACE(sizeof(int));
    char control[cmsg_len];
    msg.msg_control = control;
    msg.msg_controllen = cmsg_len;

    // cmsg
    cmg = CMSG_FIRSTHDR(&msg);
    cmg->cmsg_len = CMSG_LEN(sizeof(int));
    cmg->cmsg_type = SOL_SOCKET;
    cmg->cmsg_level = SCM_RIGHTS;
    *(int *) CMSG_DATA(cmg) = tmp_fd;

    switch (fork()) {
        case 0:


        case -1:

        default:
    }

}