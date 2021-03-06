``` c
int fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)

其中AF_INET指定的是协议族, 内核中每个族都注册了net_families[ip/ipv6],
当调用socket函数时, 在公共的函数__sock_create创建了未初始化的socket*对象,
接着寻找每个协议族相对应的create函数, 例如 AF_INET 注册了 inet_family_ops->create,
在协议族的create函数中, 初始化socket*对象, 绑定SOCK_STREAM等类型, 
创建SOCK*对象, 根据 sock_type 与 protocol初始化sock*对象

其中SOCK_STREAM是套接字类型, 内核每个协议类型都注册了inetsw[SOCK_STREAM/SOCK_DGRAM],
其中IPPROTO_TCP是传输协议, 每个套接字类型包含多种传输协议, 
{
    .type = SOCK_DGRAM, 
    .protocol= IPPROTO_UDP,
    .prot = &udp_prot,  // 提供给 sock 使用, 主要用于流数据传输
    .ops = &inet_dgram_ops,  // 提供给 socket, 上层socket函数库使用
},
{
    .type = SOCK_DGRAM, 
    .protocol= IPPROTO_ICMP,
    .prot = &ping_prot,
    .ops = &inet_sockraw_ops,
},
创建sock*对象用于协议数据交互, 在初始化sock*对象时, 根据协议类型找到对应的 SOCK_STREAM/SOCK_DGRAM,
同一个套接字类型中, 可能存在多个传输协议, 也在此函数中找到对应的传输类型, 
此时保存 prot 到 sock对象的 sk_prot 

// 定义系统调用
SYSCALL_DEFINE3(socket, int, family, int, type, int, protocol)
{
	return __sys_socket(family, type, protocol);
}

int __sys_socket(int family, int type, int protocol)
{   
    // 创建一个类型的对象,主要用于与用户进程交互
	struct socket *sock;    
	retval = sock_create(family, type, protocol, &sock);    
    // 在当前文件系统， 分配一个新的文件fd 将 sock放进file* 再绑定fd map
	return sock_map_fd(sock, flags & (O_CLOEXEC | O_NONBLOCK));
}

// 创建一个sock对象,抽象用于与协议栈交互,
// 其中将sock对象隐藏在socket对象中
int sock_create(int family, int type, int protocol, struct socket **res)
{
    // 指定当前的命名空间和协议栈等
	return __sock_create(current->nsproxy->net_ns, family, type, protocol, res, 0);
}

// 创建 sock对象
int __sock_create(struct net *net, int family, int type, int protocol,
			 struct socket **res, int kern)
{
    // socket对象
	struct socket *sock;    
    // 安全创建的hook层
	err = security_socket_create(family, type, protocol, kern);

    // 分配了socket,其中指定了文件类型  uid 和 gid  分配了inode节点
	sock = sock_alloc();    
    // 记录type
	sock->type = type;   
    // 地址协议族集合, 根据family找出当前的协议族
    // 来源于 sock_register   我们以 ipv4 为例  af_inet.c   	(void)sock_register(&inet_family_ops);
	const struct net_proto_family *pf;     
	pf = rcu_dereference(net_families[family]);   

    // 此处是创建了 sock 对象, 以 ipv4为例 inet_family_ops->create
	err = pf->create(net, sock, protocol, kern);     
}

// 创建 sock 对象
static int inet_create(struct net *net, struct socket *sock, int protocol,
		       int kern)
{
    // 标记当前的状态为未连接
	sock->state = SS_UNCONNECTED;
    // 查找套接字类型SOCK_STREAM赋给 answer  来源于 inet_register_protosw(q);   inetsw_array
	list_for_each_entry_rcu(answer, &inetsw[sock->type], list) {}

    // 保存地址族的ops 以 stream 为例, ops 保存的是套接字类型的处理  inet_stream_ops 
	sock->ops = answer->ops;
    // 保存套接字对于 tcp udp处理 用于保存 sock 对象
    answer_prot = answer->prot;
    // GFP_KERNEL指定优先级分配内存  内核优先级
	sk = sk_alloc(net, PF_INET, GFP_KERNEL, answer_prot, kern);    
    // 将 sock 专为 inet_sock
	inet = inet_sk(sk);
    // 初始化 发送接收缓存
	sock_init_data(sock, sk);
    // 设置sock的析构函数
	sk->sk_destruct	   = inet_sock_destruct;    
	sk->sk_protocol	   = protocol;    
}

// 分配 sock 对象
struct sock *sk_alloc(struct net *net, int family, gfp_t priority,
		      struct proto *prot, int kern)
{
    // kmalloc分配内存
	sk = sk_prot_alloc(prot, priority | __GFP_ZERO, family);
	if (sk) { 
        // 保存地址族
		sk->sk_family = family; 
        // 保存 tcp_prot 或者 udp_prot
		sk->sk_prot = sk->sk_prot_creator = prot;     
        // 暂时不知道做啥
		sk->sk_kern_sock = kern;   

        // 引用计数
		sk->sk_net_refcnt = kern ? 0 : 1;                       
        
        // 保存 sock 对象的命名空间
		sock_net_set(sk, net);    

        // 设计提交发送队列的子杰数
		refcount_set(&sk->sk_wmem_alloc, 1); 
        // sock 对象能分配的最大的buff  根据当前的 cgroup 
		mem_cgroup_sk_alloc(sk);                   
    }

}

// 初始化数据 分配缓存区大小
void sock_init_data(struct socket *sock, struct sock *sk)
{
    // 记录缓存区大小
	sk->sk_allocation	=	GFP_KERNEL;
	sk->sk_rcvbuf		=	sysctl_rmem_default;
	sk->sk_sndbuf		=	sysctl_wmem_default;
	sk->sk_state		=	TCP_CLOSE;

    sk_set_socket(sk, sock);    

    // 保存 sock 对象的信息
	if (sock) {
		sk->sk_type	=	sock->type;
		sk->sk_wq	=	sock->wq;
		sock->sk	=	sk;
		sk->sk_uid	=	SOCK_INODE(sock)->i_uid;   
    }     

    // 设置 接收缓存区为空
	sk_rx_queue_clear(sk);    
}

// 记录sock 的 socket, 之前记录过 socket 的 sock
// 记录要发生的字段为空
static inline void sk_set_socket(struct sock *sk, struct socket *sock)
{
	sk_tx_queue_clear(sk);
	sk->sk_socket = sock;
}

```


``` c
// ipv4 地址协议族
static const struct net_proto_family inet_family_ops = {
	.family = PF_INET,
	.create = inet_create,
	.owner	= THIS_MODULE,
};

// 套接字类型 流式
static struct inet_protosw inetsw_array[] =
{
	{
		.type =       SOCK_STREAM,
		.protocol =   IPPROTO_TCP,
		.prot =       &tcp_prot,
		.ops =        &inet_stream_ops,
		.flags =      INET_PROTOSW_PERMANENT |
			      INET_PROTOSW_ICSK,
	},

	{
		.type =       SOCK_DGRAM,
		.protocol =   IPPROTO_UDP,
		.prot =       &udp_prot,
		.ops =        &inet_dgram_ops,
		.flags =      INET_PROTOSW_PERMANENT,
       },

       {
		.type =       SOCK_DGRAM,
		.protocol =   IPPROTO_ICMP,
		.prot =       &ping_prot,
		.ops =        &inet_sockraw_ops,
		.flags =      INET_PROTOSW_REUSE,
       },

       {
	       .type =       SOCK_RAW,
	       .protocol =   IPPROTO_IP,	/* wild card */
	       .prot =       &raw_prot,
	       .ops =        &inet_sockraw_ops,
	       .flags =      INET_PROTOSW_REUSE,
       }
};


```



``` c
int err = connect(fd, sockaddr*, len)

// 发起连接
SYSCALL_DEFINE3(connect, int, fd, struct sockaddr __user *, uservaddr,
		int, addrlen) 
{
	return __sys_connect(fd, uservaddr, addrlen);
}

int __sys_connect(int fd, struct sockaddr __user *uservaddr, int addrlen)
{
    // socket 保存了 inode, 根据inode 寻找到socket
	sock = sockfd_lookup_light(fd, &err, &fput_needed);
	// 复制用户的地址 到内核分配的 地址 sockaddr_storage
	err = move_addr_to_kernel(uservaddr, addrlen, &address);
	// 针对tcp，此处调用的为 inet_stream_ops.connect
	err = sock->ops->connect(sock, (struct sockaddr *)&address, addrlen,
				 sock->file->f_flags);		
}

int inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
			int addr_len, int flags)
{
	lock_sock(sock->sk);
	err = __inet_stream_connect(sock, uaddr, addr_len, flags, 0);
	release_sock(sock->sk); 
}

int __inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
			  int addr_len, int flags, int is_sendmsg)
{
	if (uaddr) { 
	    // 如果指定了AF_UNSPEC, 啧相当于断开, 调用sock*对象的disconnect
		if (uaddr->sa_family == AF_UNSPEC) { 
		    err = sk->sk_prot->disconnect(sk, flags);
		}	
	}
	
	switch (sock->state) { 
	case SS_UNCONNECTED:
	    // 检查底层sock*的state
		if (sk->sk_state != TCP_CLOSE)
			goto out;	
		// 调用 sock* 底层 connect, 此方法已通过.prot = &tcp_prot绑定,
		err = sk->sk_prot->connect(sk, uaddr, addr_len);
		// 记录当前为连接状态
		sock->state = SS_CONNECTING;						
	}

	// 是否为阻塞, 为阻塞则获取超时  否则将超时设为0
	timeo = sock_sndtimeo(sk, flags & O_NONBLOCK);		



}

int tcp_v4_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
    // 模拟继承关系, 将sock*父类对象 转为 inet_sock 子类
	struct inet_sock *inet = inet_sk(sk);
	// 如上 将inet_sock*对象 转化 tcp_sock* 子类
	struct tcp_sock *tp = tcp_sk(sk);
	   
	// 获取本地接口 与 目的地接口
	orig_sport = inet->inet_sport;
	orig_dport = usin->sin_port;	
	
	// 路由表寻址
	struct rtable *rt;
	// nexthop 目的地地址 
	// inet->inet_saddr 本地地址
	// 寻找路由表
	rt = ip_route_connect(fl4, nexthop, inet->inet_saddr,
			      RT_CONN_FLAGS(sk), sk->sk_bound_dev_if,
			      IPPROTO_TCP,
			      orig_sport, orig_dport, sk);
			      
	// tcp 不支持 多播 和 广播		      
	if (rt->rt_flags & (RTCF_MULTICAST | RTCF_BROADCAST)) {}	
	
	// 将端口设置在 tcp 层 inet_sock
    inet->inet_dport = usin->sin_port;	
    // 设置 sock* 对象的地址	
    sk_daddr_set(sk, daddr);
    // tcp 分段
	tp->rx_opt.mss_clamp = TCP_MSS_DEFAULT; 
	// 设置 sock* 对象, 标记 tcp 状态机
	tcp_set_state(sk, TCP_SYN_SENT);
	// 发起tcp连接	
	err = tcp_connect(sk);	

	// 查看是否f失败
	if (err)
		goto failure;		

	return 0;		
}

//  
int tcp_connect(struct sock *sk)
{
    // 转换为 tcp_sock* 子类
	struct tcp_sock *tp = tcp_sk(sk);
	
	// 初始化一堆 tcp 参数
	// 分配 tcp header
	// 初始化窗口大小
	tcp_connect_init(sk);	
	// 分配 skb 内存
	buff = sk_stream_alloc_skb(sk, 0, sk->sk_allocation, true);	
	// 写入 第一个 sync
	tcp_init_nondata_skb(buff, tp->write_seq++, TCPHDR_SYN);	
	// 将数据加到 sock* 对象的 buffer 末尾
	tcp_connect_queue_skb(sk, buff);
	// 设置 ecn 阻塞
	tcp_ecn_send_syn(sk, buff);	
	
	// 发送数据
	err = tp->fastopen_req ? tcp_send_syn_data(sk, buff) :
	      tcp_transmit_skb(sk, buff, 1, sk->sk_allocation);	
}
```

 ![kernel_write](../asset/kernel_write.jpg)

``` c
static int tcp_transmit_skb(struct sock *sk, struct sk_buff *skb, int clone_it,
			    gfp_t gfp_mask)
{
	return __tcp_transmit_skb(sk, skb, clone_it, gfp_mask,
				  tcp_sk(sk)->rcv_nxt);
}

static int __tcp_transmit_skb(struct sock *sk, struct sk_buff *skb,
			      int clone_it, gfp_t gfp_mask, u32 rcv_nxt)
{
	// 此处调用了 
	err = icsk->icsk_af_ops->queue_xmit(sk, skb, &inet->cork.fl);
}




static void tcp_connect_queue_skb(struct sock *sk, struct sk_buff *skb)
{
    // 获取 tcp 控制信息
    // 包括 当前发送的 seq 号 和结束的 seq 号
	struct tcp_skb_cb *tcb = TCP_SKB_CB(skb);
	tcb->end_seq += skb->len;
	
	__skb_header_release(skb);		
	// 放入 sock* 的 buffer 末尾
	tcp_add_write_queue_tail(sk, skb);	
	
	sk_wmem_queued_add(sk, skb->truesize);	
	sk_mem_charge(sk, skb->truesize);	
}

static inline struct rtable *ip_route_connect(struct flowi4 *fl4,
					      __be32 dst, __be32 src, u32 tos,
					      int oif, u8 protocol,
					      __be16 sport, __be16 dport,
					      struct sock *sk)
{
    // 将目标地址 来源地址 端口等信息绑定 flowi4
	ip_route_connect_init(fl4, dst, src, tos, oif, protocol,
			      sport, dport, sk);
			      
	return ip_route_output_flow(net, fl4, sk);			      
}

static struct socket *sockfd_lookup_light(int fd, int *err, int *fput_needed) 
{
	struct fd f = fdget(fd);    
}

struct inet_sock {
	// 必须放在第一个字节, 是因为想要模拟继承的效果 sk是inet_sock的父类
	struct sock		sk;
}

struct rtable 
{
    struct rtable   *rt_next;/*指向下一个rtable表项 */
    unsigned long   rt_dst;/*目的IP地址*/
    unsigned long   rt_gateway;/*网关地址 */
    unsigned short  rt_mss;/*MSS值*/
    struct device   *rt_dev;/*与该路由项绑定的接口*/
}

struct proto tcp_prot = {
	.name			= "TCP",
	.owner			= THIS_MODULE,
	.close			= tcp_close,
	.pre_connect		= tcp_v4_pre_connect,
	.connect		= tcp_v4_connect,
	.disconnect		= tcp_disconnect,
	.accept			= inet_csk_accept,
	.ioctl			= tcp_ioctl,
	.init			= tcp_v4_init_sock,
	.destroy		= tcp_v4_destroy_sock,
	.shutdown		= tcp_shutdown,
	.setsockopt		= tcp_setsockopt,
	.getsockopt		= tcp_getsockopt,
	.keepalive		= tcp_set_keepalive,
	.recvmsg		= tcp_recvmsg,
	.sendmsg		= tcp_sendmsg,
	.sendpage		= tcp_sendpage,
	.backlog_rcv		= tcp_v4_do_rcv,
	.release_cb		= tcp_release_cb,
	.hash			= inet_hash,
	.unhash			= inet_unhash,
	.get_port		= inet_csk_get_port,
	.enter_memory_pressure	= tcp_enter_memory_pressure,
	.leave_memory_pressure	= tcp_leave_memory_pressure,
	.stream_memory_free	= tcp_stream_memory_free,
	.sockets_allocated	= &tcp_sockets_allocated,
	.orphan_count		= &tcp_orphan_count,
	.memory_allocated	= &tcp_memory_allocated,
	.memory_pressure	= &tcp_memory_pressure,
	.sysctl_mem		= sysctl_tcp_mem,
	.sysctl_wmem_offset	= offsetof(struct net, ipv4.sysctl_tcp_wmem),
	.sysctl_rmem_offset	= offsetof(struct net, ipv4.sysctl_tcp_rmem),
	.max_header		= MAX_TCP_HEADER,
	.obj_size		= sizeof(struct tcp_sock),
	.slab_flags		= SLAB_TYPESAFE_BY_RCU,
	.twsk_prot		= &tcp_timewait_sock_ops,
	.rsk_prot		= &tcp_request_sock_ops,
	.h.hashinfo		= &tcp_hashinfo,
	.no_autobind		= true,
#ifdef CONFIG_COMPAT
	.compat_setsockopt	= compat_tcp_setsockopt,
	.compat_getsockopt	= compat_tcp_getsockopt,
#endif
	.diag_destroy		= tcp_abort,
};

static const struct inet_connection_sock_af_ops dccp_ipv4_af_ops = {
	.queue_xmit	   = ip_queue_xmit,
	.send_check	   = dccp_v4_send_check,
	.rebuild_header	   = inet_sk_rebuild_header,
	.conn_request	   = dccp_v4_conn_request,
	.syn_recv_sock	   = dccp_v4_request_recv_sock,
	.net_header_len	   = sizeof(struct iphdr),
	.setsockopt	   = ip_setsockopt,
	.getsockopt	   = ip_getsockopt,
	.addr2sockaddr	   = inet_csk_addr2sockaddr,
	.sockaddr_len	   = sizeof(struct sockaddr_in),
#ifdef CONFIG_COMPAT
	.compat_setsockopt = compat_ip_setsockopt,
	.compat_getsockopt = compat_ip_getsockopt,
#endif
};
```




``` c
list_for_each_entry_rcu

```
