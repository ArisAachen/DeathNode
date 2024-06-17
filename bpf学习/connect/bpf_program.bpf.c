// clang -g -O2 -target bpf -D__TARGET_ARCH_x86 -c bpf_program.bpf.c -o bpf_program.bpf.o
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <bpf/bpf_core_read.h>

struct bpf_sock_info {
    // unsigned long long unused;
    struct sock *sk;
    // struct sockaddr *uaddr;
    // int addr_len;
};

// convert u32 to addr string
static inline void u32_to_addr(__be32 addr, char *buf, int buf_len) {
    BPF_SNPRINTF(buf, buf_len, "%d.%d.%d.%d", addr & 0xff, (addr >> 8) & 0xff, (addr >> 16) & 0xff, (addr >> 24) & 0xff);
}

SEC("kprobe/tcp_connect")
int bpf_prog(struct bpf_sock_info *ctx) {
    // 定义输出格式
    char fmt[] = "tcp_connect: %s -> %s \n";
    struct sock *sk;
    __be32 src, dst;
    char src_bytes[16], dst_bytes[16];

    // 从 pt_regs 结构中获取第一个参数，即 struct sock *sk
    sk = ctx->sk;
    if (!sk)
        return 0;
    // 从 sk 结构中读取源地址和目标地址
    if (bpf_probe_read_kernel(&src, sizeof(src), &sk->__sk_common.skc_rcv_saddr) != 0)
        return 0;
    if (bpf_probe_read_kernel(&dst, sizeof(dst), &sk->__sk_common.skc_daddr) != 0)
        return 0;

    // get src addr 
    u32_to_addr(src, src_bytes, 16);
    // get dst addr
    u32_to_addr(dst, dst_bytes, 16);
    
    bpf_trace_printk(fmt, sizeof(fmt), src_bytes, dst_bytes);

    return 0;
}

// SEC("kprobe/tcp_connect")
// int bpf_prog(struct pt_regs *ctx) {
//     // 定义输出格式
//     char fmt[] = "tcp_connect: %x -> %x \n";
//     struct sock *sk;
//     __be32 src, dst;
//     unsigned char src_bytes[4], dst_bytes[4];

//     // 从 pt_regs 结构中获取第一个参数，即 struct sock *sk
//     sk = (struct sock *)PT_REGS_PARM1(ctx);

//     if (!sk)
//         return 0;

//     // 从 sk 结构中读取源地址和目标地址
//     if (bpf_probe_read_kernel(&src, sizeof(src), &sk->__sk_common.skc_rcv_saddr) != 0)
//         return 0;
//     if (bpf_probe_read_kernel(&dst, sizeof(dst), &sk->__sk_common.skc_daddr) != 0)
//         return 0;

//     bpf_trace_printk(fmt, sizeof(fmt), src, dst);

//     return 0;
// }

char _license[] SEC("license") = "GPL";