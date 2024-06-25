#include <linux/bpf.h>
#include <linux/ptrace.h>
#include <linux/version.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>

SEC("krpobe/sendto")
int bpf_prog(struct pt_regs *ctx) {
    char fmt[] = "sendto\n";
    bpf_trace_printk(fmt, sizeof(fmt));
    return 0;
}