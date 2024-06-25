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
    struct bpf_program *program =  bpf_object__find_program_by_name(obj, "add");
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