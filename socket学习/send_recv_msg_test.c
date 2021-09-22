//
// Created by aris on 2021/9/22.
//

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include <netinet/in.h>
#include <sys/socket.h>


static void print_err(char *msg) {
    printf("%s failed, err: %s \n", msg, strerror(errno));
    exit(-1);
}


void udp_send_msg_test() {
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (fd == -1)
        print_err("socket");

#ifdef IP_RECVDSTADDR
    int active = 1;
    if(setsockopt(fd,IPPROTO_IP,IP_RECVDSTADDR,&active,sizeof(int)) == -1)
        print_err("set sockopt");
#elif


}