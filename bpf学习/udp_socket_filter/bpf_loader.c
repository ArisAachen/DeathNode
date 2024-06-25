// bpf_loader.c
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <bpf/libbpf.h>

int main() {

    char msg[128] = {0};
    printf("test msg: %x \n", msg);

    struct bpf_object *obj;
    int prog_fd;

    // 加载BPF程序
    obj = bpf_object__open_file("bpf_program.bpf.o", NULL);
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "Error opening BPF object file\n");
        return 1;
    }

    // 加载到内核中
    if (bpf_object__load(obj)) {
        fprintf(stderr, "Error loading BPF object file\n");
        return 1;
    }
    // 获取程序文件描述符
    struct bpf_program *prog = bpf_object__find_program_by_name(obj, "addr_dump");
    if (!prog) {
        fprintf(stderr, "Error finding BPF program in object file\n");
        return 1;
    }
    // 获取fd
    prog_fd = bpf_program__fd(prog);
    if (prog_fd < 0) {
        fprintf(stderr, "Error getting file descriptor for program\n");
        return 1;
    }
    // 创建udp socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }
    // 绑定bpf程序
    if (setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd, sizeof(prog_fd)) < 0) {
        fprintf(stderr, "Error attaching BPF program to socket\n");
        return 1;
    }
    // 监听udp server
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(9999);
    if (bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) {
        fprintf(stderr, "Error binding socket\n");
        return 1;
    }
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    // client_addr.sin_family = AF_INET;
    // inet_pton(AF_INET, "192.168.121.1", &client_addr.sin_addr);
    // client_addr.sin_port = htons(9999);

    // 读取
    char buf[1024];
    socklen_t addr_len;
    while (1) {
        int len = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addr_len);
        if (len < 0) {
            fprintf(stderr, "Error reading from socket\n");
            return 1;
        }
        sleep(3);  
        printf("Received message: %s, len: %d\n", buf, len);
    }

    printf("BPF program loaded and attached successfully\n");
    sleep(60);
    return 0;
}