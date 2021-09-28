//
// Created by aris on 2021/9/27.
//


#include "genernal_define.h"
#include <arpa/inet.h>

void udp_client_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_port = htons(12345),
    };

    if (inet_pton(AF_INET, "192.168.1.205", &in.sin_addr) == -1)
        bad_exit("client inet");

    char *msg = "this is test msg";

    if (sendto(fd, msg, sizeof(msg), 0, (struct sockaddr *) &in, sizeof(struct sockaddr)) == -1)
        bad_exit("sendto");

    printf("snd end \n");
}


void udp_server_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        bad_exit("socket");

    struct sockaddr_in in = {
            .sin_family = AF_INET,
            .sin_port = htons(12345),
            .sin_addr = htonl(INADDR_ANY),
    };

    int opt = 1;
    if (setsockopt(fd, SOL_IP, IP_PKTINFO, &opt, sizeof(int)) == -1)
        bad_exit("pkt");

    if (bind(fd, (struct sockaddr *) &in, sizeof(struct sockaddr)) == -1)
        bad_exit("bind");

    char buf[BUFSIZ];
    struct msghdr hdr;
    struct iovec vec[1];
    char control[1000];

    vec[0].iov_base = buf;
    vec[0].iov_len = BUFSIZ;

    hdr.msg_name = &in;
    hdr.msg_namelen = sizeof(in);
    hdr.msg_control = control;
    hdr.msg_controllen = 1000;
    hdr.msg_iov = vec;
    hdr.msg_iovlen = 1;

    memset(&in, 0, sizeof(struct sockaddr_in));

    if (recvmsg(fd, &hdr, 0) == -1)
        bad_exit("rcv msg");

    for (struct cmsghdr *cmg = CMSG_FIRSTHDR(&hdr); cmg; cmg = CMSG_NXTHDR(&hdr, cmg)) {
        if (cmg->cmsg_type == IP_PKTINFO && cmg->cmsg_level == SOL_IP) {
            struct in_pktinfo *info = (struct in_pktinfo *) CMSG_DATA(cmg);
            if (info == NULL)
                bad_exit("info null");

            char address[128];
            if (inet_ntop(AF_INET, &info->ipi_addr, address, INET_ADDRSTRLEN) == NULL)
                bad_exit("rcv address");
            printf("rcv address is %s, index is %d \n", address,info->ipi_ifindex);
        } else {
            printf("type is %d, level is %d \n", cmg->cmsg_type, cmg->cmsg_level);
        }
    }

    char address[128];
    struct in_addr *inAddr = hdr.msg_name;
    if (inet_ntop(AF_INET, inAddr, address, INET_ADDRSTRLEN) == NULL)
        bad_exit("rcv address");

    printf("src address is %s flags is %d \n", address, hdr.msg_flags);

    printf("rcv msg is %s \n", buf);

    printf("rcv end \n");
}


int main() {

    switch (fork()) {
        case 0:
            sleep(5);
            udp_client_test();
            break;
        case -1:
            bad_exit("fork");
            break;
        default:
            udp_server_test();
    }


}