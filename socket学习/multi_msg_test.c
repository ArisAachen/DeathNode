//
// Created by aris on 2021/8/22.
//

#include <unistd.h>
#include <netdb.h>

#include <sys/socket.h>


void multi_send_test() {
    int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    const char * url = "http://baidu.com";

    struct addrinfo info = {
            .ai_flags =
    };


}

int main() {

}