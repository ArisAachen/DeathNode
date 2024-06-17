// bpftool btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h
// gcc -o bpf_loader bpf_loader.c -lbpf
#include <unistd.h>
#include <bpf/libbpf.h>

int main() {
    struct bpf_object *obj =  bpf_object__open_file("bpf_program.bpf.o", NULL);
    if (libbpf_get_error(obj)) {
        fprintf(stderr, "Error opening BPF object file\n");
        return 1;
    }
    if (bpf_object__load(obj)) {
        fprintf(stderr, "Error loading BPF object file\n");
        return 1;
    }
    struct bpf_program *program =  bpf_object__find_program_by_name(obj, "bpf_prog");
    if (!program) {
        fprintf(stderr, "Error finding BPF program in object file\n");
        return 1;
    }
    if (bpf_program__attach(program) < 0) {
        fprintf(stderr, "Error attaching to kprobe\n");
        return 1;
    }
    printf("BPF program loaded and attached successfully\n");
    sleep(60);
    return 0;
}


// // bpf_loader.c
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <bpf/libbpf.h>

// int main() {
//     struct bpf_object *obj;
//     int prog_fd;

//     // 加载BPF程序
//     obj = bpf_object__open_file("bpf_program.bpf.o", NULL);
//     if (libbpf_get_error(obj)) {
//         fprintf(stderr, "Error opening BPF object file\n");
//         return 1;
//     }

//     // 加载到内核中
//     if (bpf_object__load(obj)) {
//         fprintf(stderr, "Error loading BPF object file\n");
//         return 1;
//     }

//     // 获取程序文件描述符
//     struct bpf_program *prog = bpf_object__find_program_by_name(obj, "bpf_prog");
//     if (!prog) {
//         fprintf(stderr, "Error finding BPF program in object file\n");
//         return 1;
//     }
//     // 附加到tracepoint
//     if (bpf_program__attach(prog) < 0) {
//         fprintf(stderr, "Error attaching to tracepoint\n");
//         return 1;
//     }
//     printf("BPF program loaded and attached successfully\n");
//     sleep(60);
//     return 0;
// }