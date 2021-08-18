//
// Created by aris on 2021/8/18.
//

#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>

void bad_exit(void) __attribute__((noreturn));

void write_test() {
    // dev patch
    const char *dev_path = "/dev/log";

    // create unix domain socket
    int unix_socket = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (unix_socket == -1) {
        printf("create local socket failed, err: %s \n", strerror(errno));
        return;
    }

    // unix path
    struct sockaddr_un dev_address;
    dev_address.sun_family = AF_LOCAL;
    memset(&dev_address, 0, sizeof(struct sockaddr_un));
    strncpy(dev_address.sun_path, dev_path, sizeof(dev_address.sun_path));

    // data_gram connect
    if (connect(unix_socket, (struct sockaddr *) &dev_address, sizeof(struct sockaddr_un))) {
        printf("connect udp socket failed, err： %s \n", strerror(errno));
        return;
    }
    const char *msg = ">>>>>> this is syslog socket msg";

    // try to write message
    if (write(unix_socket, msg, 512)) {
        printf("write msg failed, err: %s \n", strerror(errno));
    }

    if (sendto(unix_socket, msg, 512, 0, (struct sockaddr *) &dev_address, sizeof(struct sockaddr_un))) {
        printf("sendto msg failed, err: %s \n", strerror(errno));
    }
}

int main() {
    write_test();
    return 1;
}