//
// Created by aris on 2021/8/16.
//
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

void tun_test() {
    // open file
    const char *dev_path = "/dev/net/tun";
    int tun_fd = open(dev_path, O_CREAT | O_EXCL | O_RDWR, S_IWUSR | S_IRUSR);
    if (tun_fd == -1) {
        printf("open tun device failed, err: %s", strerror(errno));
    }

    const char *dev = "tun1";
    struct ifreq req;

    // copy if name
    if (!strncpy(req.ifr_ifrn.ifrn_name, dev, IFNAMSIZ)) {
        printf("copy failed, err : %s", strerror(errno));
        return;
    }

    // set tun flags
    req.ifr_ifru.ifru_flags = IFF_TUN;


}

int main() {

}