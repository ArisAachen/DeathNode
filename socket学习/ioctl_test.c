//
// Created by aris on 2021/9/25.
//


/*
 * ioctl(int fd,int request,...)
 * 网络请求分为6类
 * 1. 套接字操作
 * 2. 文件操作
 * 3. 接口操作
 * 4. ARP高速缓存操作
 * 5. 路由表操作
 * 6. 流系统
 * */


#include <math.h>
#include <arpa/inet.h>
#include "genernal_define.h"
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>



// ifconfig
void get_ifconfig_test() {

    // buf length

#define BUF_LEN sizeof(struct ifreq) * 10
    char buf[BUF_LEN];

    struct ifconf ifi = {
            .ifc_len = BUF_LEN,
            .ifc_buf = buf,
    };

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
        bad_exit("socket");

    if (ioctl(fd, SIOCGIFCONF, &ifi) == -1)
        bad_exit("get ifconfig");

    for (struct ifreq *req = (struct ifreq *) ifi.ifc_req; req;) {
        char if_name[128];
        strncpy(if_name, req->ifr_name, sizeof(req->ifr_name));
        printf("if name is %s \n", if_name);

        int ex_len = sizeof(req->ifr_name) + sizeof(struct sockaddr);
        req = req + ex_len;
    }

}

// ifreq
void get_ifreq_test() {

    char if_name[IFNAMSIZ] = "eno1";
    struct ifreq req;

    memset(&req, 0, sizeof(struct ifreq));
    req.ifr_addr.sa_family = AF_INET;
    strncpy(req.ifr_name, if_name, IFNAMSIZ);

    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
        bad_exit("socket");

    if (ioctl(fd, SIOCGIFADDR, &req) == -1)
        bad_exit("ifaddr");

    if (req.ifr_addr.sa_family == AF_INET) {
        char buf[INET_ADDRSTRLEN];
        struct sockaddr_in *ipv4_addr = (struct sockaddr_in *) &req.ifr_addr;
        const char *addr = inet_ntop(AF_INET, &ipv4_addr->sin_addr, buf, INET_ADDRSTRLEN);
        if (addr == NULL)
            bad_exit("inet");
        printf("addr is %s \n", addr);
    } else {
        bad_exit("unknown protocol");
    }

    if (ioctl(fd, SIOCGIFFLAGS, &req) == -1)
        bad_exit("flags");

    if (req.ifr_flags & IFF_BROADCAST) {
        printf("BROADCAST ");
    }

    if(req.ifr_flags & IFF_MULTICAST) {
        printf("MULTICAST \n");
    }

}

void arp_test() {
    struct arpreq req;
    struct sockaddr_in* addr;

    strncpy(req.arp_dev,"eno1",IFNAMSIZ);
    addr = (struct sockaddr_in*)&req.arp_pa;

    addr->sin_family = AF_INET;
    if(inet_pton(AF_INET,"10.20.43.117",&addr->sin_addr) == -1)
        bad_exit("inet");

    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd == -1)
        bad_exit("socket");
    if(ioctl(fd,SIOCGARP,&req) == -1)
        bad_exit("ioctl");

    printf("family is %d \n",req.arp_ha.sa_family);
    char *ptr = &req.arp_ha.sa_data[0];
    printf("hwadr is %x:%x:%x:%x:%x:%x \n",*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5));
}

int main() {
    arp_test();

    return 1;
}