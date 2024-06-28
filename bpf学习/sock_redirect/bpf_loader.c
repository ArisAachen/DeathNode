#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <bpf/bpf.h>
#include <bpf/libbpf.h>


static inline int poll_read(int fd, unsigned int timeout_sec)
{
	struct timeval timeout = { .tv_sec = timeout_sec };
	fd_set rfds;
	int r;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	r = select(fd + 1, &rfds, NULL, NULL, &timeout);
	if (r == 0)
		errno = ETIME;

	return r == 1 ? 0 : -1;
}

int main() {

    // load bpf file
    struct bpf_object *obj = bpf_object__open_file("bpf_program.bpf.o", NULL);
    if (!obj) {
        printf("bpf_object__open_file failed\n");
        return -1;
    }
    if (bpf_object__load(obj)) {
        printf("bpf_object__load failed\n");
        return -1;
    }
    int map_fd = bpf_object__find_map_fd_by_name(obj, "sock_store");
    if (map_fd < 0) {
        printf("bpf_object__find_map_by_name failed\n");
        return -1;
    }
    // get map fd 
    int redir_map_fd = bpf_object__find_map_fd_by_name(obj, "sock_redir");
    if (redir_map_fd < 0) {
        printf("bpf_object__find_map_by_name failed\n");
        return -1;
    }
    // get program fd
    int prog_fd = bpf_program__fd(bpf_object__find_program_by_name(obj, "bpf_prog_verdict"));
    if (prog_fd < 0) {
        printf("bpf_object__find_program_by_name failed, err: %s\n", strerror(errno));
        return -1;
    }
    // attach
    if (bpf_prog_attach(prog_fd, map_fd, BPF_SK_SKB_STREAM_VERDICT, 0) < 0) {
        fprintf(stderr, "Failed to update sock_map: %s\n", strerror(errno));
        return -1;
    }
    if (bpf_prog_attach(prog_fd, redir_map_fd, BPF_SK_SKB_STREAM_VERDICT, 0) < 0) {
        fprintf(stderr, "Failed to update sock_map: %s\n", strerror(errno));
        return -1;
    }
    // // 
    // prog_fd = bpf_program__fd(bpf_object__find_program_by_name(obj, "bpf_prog_parser"));
    // if (prog_fd < 0) {
    //     printf("bpf_object__find_program_by_name failed\n");
    //     return -1;
    // }
    // if (bpf_prog_attach(prog_fd, map_fd, BPF_SK_SKB_STREAM_PARSER, 0) < 0) {
    //     fprintf(stderr, "Failed to update sock_map: %s\n", strerror(errno));
    //     return -1;
    // }

    int sock_local = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_local < 0) {
        printf("socket failed\n");
        return -1;
    }
    struct sockaddr_in addr_local;
    addr_local.sin_family = AF_INET;
    addr_local.sin_port = htons(5201);
    addr_local.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sock_local, (struct sockaddr *)&addr_local, sizeof(addr_local)) < 0) {
        printf("bind failed\n");
        return -1;
    }
    if (listen(sock_local, 10) < 0) {
        printf("listen failed\n");
        return -1;
    }
    int sock_remote = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_remote < 0) {
        printf("socket failed\n");
        return -1;
    }
    struct sockaddr_in addr_remote;
    addr_remote.sin_family = AF_INET;
    addr_remote.sin_port = htons(5201);
    if (inet_pton(AF_INET, "119.3.40.126", &addr_remote.sin_addr) < 0) {
        printf("inet_pton failed\n");
        return -1;
    }
    if (connect(sock_remote, (struct sockaddr *)&addr_remote, sizeof(addr_remote)) < 0) {
        printf("connect failed\n");
        return -1;
    }

    while (1) {
        int accepted_sock = accept(sock_local, NULL, NULL);
        if (accepted_sock < 0) {
            printf("accept failed\n");
            return -1;
        }
        int key = 0;
        if (bpf_map_update_elem(map_fd, &key, &accepted_sock, BPF_ANY) < 0) {
            printf("bpf_map_update_elem failed, err: %s\n", strerror(errno));
            return -1;
        }
        if (bpf_map_update_elem(redir_map_fd, &key, &sock_remote, BPF_ANY) < 0) {
            printf("bpf_map_update_elem failed, err: %s\n", strerror(errno));
            return -1;
        }

        printf("bpf_map_update_elem success\n");
        sleep(5000);
    }

    close(sock_local);
    close(sock_remote);
    
    return 0;
}