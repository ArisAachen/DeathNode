``` shell
ls /sys/kernel/debug/tracing/events/syscalls
```

Head First eBPF:  
https://www.ebpf.top/  

ARTHURCHIAO'S BLOG:  
https://arthurchiao.art/articles-zh  

kpath:  
https://www.ebpf.top/post/kpatch_ipvs_timer/  

tcp splice:  
https://blog.csdn.net/u011130578/article/details/44599835 

Program Types and ELF Sections:  
https://docs.kernel.org/bpf/libbpf/program_types.html



##　踩坑合集

``` c
// 在绑定udp socket时, 使用 recv时, 获取到的skb是去除了以太网头和ip头的
// 此时 __sk_buff 内不包含iphdr 和 ethhdr, 使用 bpf_skb_load_bytes 读取不到数据
// 应该使用 bpf_skb_load_bytes_relative 
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

```


``` c
// sockmap 是如何与 sk_skb/stream_parser 结合起来工作的
// 此处是当调用 bpf_map_update_elem 时, sock根据bpf内注册的 stream_parser, 
// 将回调关联到sk内, 
// 注意, 当使用bpf_map_update_elem时, fd必须是 listen　过的
static long sock_map_update_elem(struct bpf_map *map, void *key,
				 void *value, u64 flags)
{
	if (!sock_map_sk_state_allowed(sk))
		ret = -EOPNOTSUPP;
	else if (map->map_type == BPF_MAP_TYPE_SOCKMAP)
		ret = sock_map_update_common(map, *(u32 *)key, sk, flags);
	else
		ret = sock_hash_update_common(map, key, sk, flags);    
}

```