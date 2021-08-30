//
// Created by aris on 2021/8/22.
//

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/un.h>

int main() {
    const char *file_path = "/home/aris/Desktop/un.socket";

    struct sockaddr_un un_add;
    memset(&un_add, 0, sizeof(struct sockaddr_un));
    un_add.sun_family = AF_LOCAL;
    strncpy(un_add.sun_path, file_path, sizeof(un_add.sun_path) - 1);

    int unix_sock = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (bind(unix_sock, (struct sockaddr * ) & un_add, sizeof(struct sockaddr_un)) == -1) {
        printf("bind failed, err: %s \n", strerror(errno));
        return -1;
    }

    printf("bind success \n");

    return 1;
}


i