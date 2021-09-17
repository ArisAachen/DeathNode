//
// Created by aris on 2021/9/17.
//

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include <stropts.h>


void bad_return(void) __attribute__((noreturn));

void bad_return() {
    exit(-1);
}


struct command_head {
    t_scalar_t command;
    t_scalar_t length;
    t_scalar_t offset;
    t_uscalar_t id;
};

struct {
    struct command_head head;
    char addr[128];
} bind_req;

void test_bind() {
    // open dev to get one socket
    int fd = open("/dev/tcp", O_RDWR | O_EXCL | O_CLOEXEC, S_IRUSR | S_IWUSR | S_IXUSR);
    if (fd == -1) {
        printf("open tcp failed, err: %s", strerror(errno));
        bad_return();
    }


}


int main() {

}
