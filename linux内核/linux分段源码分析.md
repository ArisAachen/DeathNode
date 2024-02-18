``` c
static int __ip_finish_output(struct net *net, struct sock *sk, struct sk_buff *skb)
{
    // 检查一下是不是需要分片
	// 此处先看看ip层的报文是否超过了mtu, 
	if (skb->len > mtu || IPCB(skb)->frag_max_size)
		return ip_fragment(net, sk, skb, mtu, ip_finish_output2);
}


static int ip_fragment(struct net *net, struct sock *sk, struct sk_buff *skb,
		       unsigned int mtu,
		       int (*output)(struct net *, struct sock *, struct sk_buff *))
{

}
```