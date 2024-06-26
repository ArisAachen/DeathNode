#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <bpf/libbpf.h>
#include <bpf/bpf.h>

#define BPF_PROG_FILE "/sys/fs/bpf/bpf_prog"
#define SOCK_MAP_FILE "/sys/fs/bpf/sock_map"
#define SERVER_PORT 10000

int main() {
    int sock_map_fd, prog_fd, sock_fd;
    struct bpf_object *obj;
    struct sockaddr_in server_addr;

    // 加载 BPF 对象文件
    obj = bpf_object__open_file("bpf_program.bpf.o", NULL);
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "Failed to open BPF object file\n");
        return 1;
    }

    // 加载 BPF 程序
    if (bpf_object__load(obj)) {
        fprintf(stderr, "Failed to load BPF object\n");
        return 1;
    }

    // 获取 BPF 程序文件描述符
    prog_fd = bpf_program__fd(bpf_object__find_program_by_name(obj, "bpf_prog_verdict"));
    if (prog_fd < 0) {
        fprintf(stderr, "Failed to get BPF program FD\n");
        return 1;
    }

    sock_map_fd = bpf_object__find_map_fd_by_name(obj, "sock_redir");
    if (sock_map_fd < 0) {
        fprintf(stderr, "Failed to get sock_map FD\n");
        return 1;
    }

    // 创建 TCP socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        fprintf(stderr, "Failed to create socket: %s\n", strerror(errno));
        return 1;
    }

    // 绑定 socket 到指定端口
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Failed to bind socket: %s\n", strerror(errno));
        return 1;
    }

    __u64 sock_fd64 = sock_fd;

    // 将 socket 添加到 sock_map
    __u32 key = 0;
    if (bpf_map_update_elem(sock_map_fd, &key, &sock_fd64, BPF_ANY) < 0) {
        fprintf(stderr, "Failed to update sock_map: %s\n", strerror(errno));
        return 1;
    }

    // 将 BPF 程序附加到 sock_map 中的 socket 上
    if (bpf_prog_attach(prog_fd, sock_map_fd, BPF_SK_SKB_STREAM_VERDICT, 0) < 0) {
        fprintf(stderr, "Failed to attach BPF program: %s\n", strerror(errno));
        return 1;
    }

    printf("BPF program successfully loaded and attached\n");

    // 保持程序运行以处理流量
    while (1) {
        sleep(10);
    }

    // 清理资源
    close(sock_fd);
    close(sock_map_fd);
    bpf_object__close(obj);

    return 0;
}