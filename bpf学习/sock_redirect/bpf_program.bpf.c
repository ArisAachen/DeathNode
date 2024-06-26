#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/tcp.h>

struct {
    __uint(type, BPF_MAP_TYPE_SOCKMAP);
    __uint(max_entries, 10);
    __type(key, __u32);
    __type(value, __u64);
} sock_redir SEC(".maps");

// 解析程序，用于解析数据包
SEC("sk_skb/stream_parser")
int bpf_prog_parser(struct __sk_buff *skb) {
    // 简单地返回数据包长度作为解析结果
    return skb->len;
}

// 判决程序，用于决定数据包处理方式
SEC("sk_skb/stream_verdict")
int bpf_prog_verdict(struct __sk_buff *skb) {
    __u32 lport = skb->local_port; // 获取本地端口
    __u32 idx = 0;

    // 如果本地端口是 10000，则重定向数据包
    if (lport == 10000) {
        return bpf_sk_redirect_map(skb, &sock_redir, idx, 0);
    }
    // 否则，数据包通过
    return SK_PASS;
}

char LICENSE[] SEC("license") = "GPL";