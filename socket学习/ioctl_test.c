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

#include "genernal_define.h"
#include <net/if.h>
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

int main() {
    get_ifconfig_test();

    return 1;
}