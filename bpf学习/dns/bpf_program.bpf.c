#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_endian.h>
#include <bpf/bpf_tracing.h>

// convert u32 to addr string
static inline void u32_to_addr(__be32 addr, char *buf, int buf_len) {
    BPF_SNPRINTF(buf, buf_len, "%d.%d.%d.%d", addr & 0xff, (addr >> 8) & 0xff, (addr >> 16) & 0xff, (addr >> 24) & 0xff);
}

SEC("kprobe/__sys_sendto")
int BPF_KPROBE(inet_sendmsg, struct socket *sock, struct msghdr *msg, size_t size) {
    // 定义输出格式
    char fmt[] = "sendto: %s -> %s \n";
    struct sock sk;
    __be32 src, dst;
    char src_bytes[16], dst_bytes[16];
    // 从 sk 结构中读取源地址和目标地址
    if (bpf_probe_read_kernel(&src, sizeof(src), &sock->sk->__sk_common.skc_rcv_saddr) != 0)
        return 0;
    if (bpf_probe_read_kernel(&dst, sizeof(dst), &sock->sk->__sk_common.skc_daddr) != 0)
        return 0;

    // get src addr 
    u32_to_addr(src, src_bytes, 16);
    // get dst addr
    u32_to_addr(dst, dst_bytes, 16);
    
    bpf_trace_printk(fmt, sizeof(fmt), src_bytes, dst_bytes);
    return 0;
}

char _license[] SEC("license") = "GPL";