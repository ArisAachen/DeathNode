#include "vmlinux.h"
#include <bpf/bpf_endian.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_core_read.h>

#define IP_PROTO_OFF offsetof(struct iphdr, protocol)
#define IP_DEST_OFF offsetof(struct iphdr, daddr)
#define IP_SRC_OFF offsetof(struct iphdr, saddr)

#define ETH_HLEN 14  // Ethernet header length
#define CHUNK_SIZE 128  // 每次打印的片段大小

SEC("socket")
int addr_dump(struct __sk_buff *skb) {
    struct udphdr udp;
    if (bpf_skb_load_bytes(skb, 0, &udp, sizeof(struct udphdr)) < 0) {
        char fmt[] = "eth_hdr: load failed\n";
        bpf_trace_printk(fmt, sizeof(fmt));
        return 0;
    }
    char udp_fmt[] = "msg: %d %d \n";
    bpf_trace_printk(udp_fmt, sizeof(udp_fmt), bpf_ntohl(udp.source), bpf_ntohl(udp.dest));

    struct iphdr ip;
    if (bpf_skb_load_bytes_relative(skb, 0, &ip, sizeof(struct iphdr), BPF_HDR_START_NET) < 0) {
        char fmt[] = "ip_hdr: load failed\n";
        bpf_trace_printk(fmt, sizeof(fmt));
        return 0;
    }
    char ip_fmt[] = "ip: %x %x \n";
    bpf_trace_printk(ip_fmt, sizeof(ip_fmt), ip.saddr, ip.daddr);

    return skb->len;
}
char _license[] SEC("license") = "GPL";
