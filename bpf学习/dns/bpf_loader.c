#include <unistd.h>
#include <sys/socket.h>
#include <bpf/libbpf.h>

int test_send() {
    send(0, NULL, 0, 0);
}

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
    struct bpf_program *program =  bpf_object__find_program_by_name(obj, "print_dns_request");
    if (!program) {
        fprintf(stderr, "Error finding BPF program in object file\n");
        return 1;
    }
    if (bpf_program__attach(program) < 0) {
        fprintf(stderr, "Error attaching to kprobe\n");
        return 1;
    }
    printf("BPF program loaded and attached successfully\n");
    sleep(150000);
    return 0;
}