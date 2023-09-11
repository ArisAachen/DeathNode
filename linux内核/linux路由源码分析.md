## 说明 
文档主要用于分析linux内核中的路由策略

## 配置操作
### 提交patch
``` shell
perl-authen-sasl 
perl-io-socket-ssl 
```

### 禁止gcc优化
``` shell
# 使用 gcc -Og 优化调试, 会导致编译失败
find . -name Makefile -print0 | xargs -0 sed -i 's/-O2/-Og/g'
```

``` json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
      {
        "name": "(gdb) linux",
        "type": "cppdbg",
        "request": "launch",
        "program": "${workspaceRoot}/vmlinux",
        "miDebuggerServerAddress": "localhost:1234",
        "args": [],
        "stopAtEntry": true,
        "cwd": "${workspaceFolder}",
        "environment": [],
        "externalConsole": false,
        "MIMode": "gdb"
      }
    ]
}
```

### host 配置
``` shell
sudo ip tuntap add dev tap0 mode tap user `whoami`
sudo ip link add link enp3s0 name eth0 type macvlan mode bridge
sudo brctl addbr br0
sudo brctl addif br0 eth0
sudo brctl addif br0 tap0
sudo ip link set br0 up
sudo ip link set  tap0 up
sudo ip addr add dev br0 192.168.10.1/24
sudo ip addr add dev tap0 192.168.10.100/24
sudo systemctl start nginx.service
qemu-system-x86_64 -kernel ~/Desktop/OpenSource/linux/arch/x86_64/boot/bzImage -initrd ~/Desktop/OpenSource/busybox/_install/rootfs.img -append "nokaslr console=ttyS0" -netdev tap,id=net0,ifname=tap0,script=no,downscript=no -device e1000,netdev=net0 -s -S -nographic
```

### kvm配置
``` shell
ip link set dev eth0 up
ip addr add dev eth0 192.168.10.10/24
ip route add default via 192.168.10.1
```

### 获取配置
``` shell
~ # ip route show table local
local 192.168.10.10 dev eth0 scope host  src 192.168.10.10
broadcast 192.168.10.255 dev eth0 scope link  src 192.168.10.10

~ # ip route show table main
192.168.10.0/24 dev eth0 scope link  src 192.168.10.10
```



## 创建默认路由
1. 注册通知模块 
``` c
// 
void __init ip_fib_init(void) {
    // 注册通知, 本质上是将自己感兴趣的函数注册到 inetaddr_chain， 
    // 此函数一般是在添加和删除 ip 地址的地方被调用, 举个例子 __inet_insert_ifa 
    register_inetaddr_notifier(&fib_inetaddr_notifier);
}

// fib_inetaddr_notifier 中包含实际被调用的 callback fib_inetaddr_event,
// 此处仅分析 添加的过程, __inet_insert_ifa 调用 callback 的 NETDEV_UP 事件
// 源码部分为 blocking_notifier_call_chain(&inetaddr_chain, NETDEV_UP, ifa); 
static int fib_inetaddr_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	switch (event) {
    // 此处是添加时间
	case NETDEV_UP:
		fib_add_ifaddr(ifa);
#ifdef CONFIG_IP_ROUTE_MULTIPATH
		fib_sync_up(dev, RTNH_F_DEAD);
#endif
		atomic_inc(&net->ipv4.dev_addr_genid);
		rt_cache_flush(dev_net(dev));
		break;
    }
}
```

2. 处理添加默认路由
``` c 
// 
void fib_add_ifaddr(struct in_ifaddr *ifa)
{
    // 此处处理新增默认路由, 指定为 local, 指定 local 是为了方便后续 main 表的递归创建 
    fib_magic(RTM_NEWROUTE, RTN_LOCAL, addr, 32, prim, 0);
}

// 
static void fib_magic(int cmd, int type, __be32 dst, int dst_len,
		      struct in_ifaddr *ifa, u32 rt_priority)
{
    // 此处获取设备所属的命名空间，所有网络ip 域名等都是通过命名空间隔离的
    // 这也是 docker 这类网络隔离的基础 
    struct net *net = dev_net(ifa->ifa_dev->dev);

    // TODO 暂时绕过, 只要知道 一开始获取到 0
    u32 tb_id = l3mdev_fib_table(ifa->ifa_dev->dev);

    // 这个结构体, 保存了路由器配置信息, 用于后续创建路由表信息
	struct fib_config cfg = {
		.fc_protocol = RTPROT_KERNEL,  // kernel bgp ospe dhcp
		.fc_type = type,
		.fc_dst = dst,
		.fc_dst_len = dst_len,
		.fc_priority = rt_priority,
		.fc_prefsrc = ifa->ifa_local,
		.fc_oif = ifa->ifa_dev->dev->ifindex,
		.fc_nlflags = NLM_F_CREATE | NLM_F_APPEND,
		.fc_nlinfo = {
			.nl_net = net,
		},
	};

    // 此处判断是否为空, 根据上面那个代码可以知道, 一开始就是空的, 
    // 这里一开始传的 local, 就派上用场了, 首先获取到 local 表, 也就是 255 表 
	if (!tb_id)
		tb_id = (type == RTN_UNICAST) ? RT_TABLE_MAIN : RT_TABLE_LOCAL;
    
    // 此处开始创建新的路由表, 里面根据是local 循环创建了 main 表 
    tb = fib_new_table(net, tb_id);
    // 更新id
	cfg.fc_table = tb->tb_id;
    
	// 如果是本地就使用 scope host
	if (type != RTN_LOCAL)
		cfg.fc_scope = RT_SCOPE_LINK;
	else
		cfg.fc_scope = RT_SCOPE_HOST;

    // 此处创建route
	if (cmd == RTM_NEWROUTE)
		fib_table_insert(net, tb, &cfg, NULL);
	else
		fib_table_delete(net, tb, &cfg, NULL);
}

// 创建路由表
struct fib_table *fib_new_table(struct net *net, u32 id)
{
    // 这里判断了一下表是否存在, 一开始当然是空的 
	tb = fib_get_table(net, id);
	if (tb)
		return tb;
    
    // 此处根据是不是 local 表, 递归创建 main
    // TODO 为什么此处要判断是否存在 fib_has_custom_rules 
	if (id == RT_TABLE_LOCAL && !net->ipv4.fib_has_custom_rules)
		alias = fib_new_table(net, RT_TABLE_MAIN);    

    // 此处创建 trie 树, 本质上内核路由是一颗 lc-trie 树
    tb = fib_trie_table(id, alias);

	switch (id) {
    // 保存了 main 和 default 表
	case RT_TABLE_MAIN:
		rcu_assign_pointer(net->ipv4.fib_main, tb);
		break;
	case RT_TABLE_DEFAULT:
		rcu_assign_pointer(net->ipv4.fib_default, tb);
		break;
	default:
		break;
	}

    // 此处把路由表添加到全局路由, 可以看到实际是挂在 fib_table_hash 下的一个 hashtable
	h = id & (FIB_TABLE_HASHSZ - 1);
	hlist_add_head_rcu(&tb->tb_hlist, &net->ipv4.fib_table_hash[h]);
}

// 初始化trie, 将trie挂载fib_table的data, tb_data指向data
struct fib_table *fib_trie_table(u32 id, struct fib_table *alias)
{
    // 这里主要用于分配 fib_table 的内存
    struct fib_table *tb;
    tb = kzalloc(sz, GFP_KERNEL);

    // 此处初始化一些成员变量
	tb->tb_id = id;
	tb->tb_num_default = 0;
    // TODO 这里似乎 local 挂载了 main
	tb->tb_data = (alias ? alias->__data : tb->__data);

    // 这里挂载了 trie, 实际的路由信息存在 trie 内 
	t = (struct trie *) tb->tb_data;
	t->kv[0].pos = KEYLENGTH;
	t->kv[0].slen = KEYLENGTH;    
}

/* Caller must hold RTNL. */
int fib_table_insert(struct net *net, struct fib_table *tb,
		     struct fib_config *cfg, struct netlink_ext_ack *extack)
{
	// 指向了 trie
	struct trie *t = (struct trie *)tb->tb_data;

	// 网络转化为主机字节序
	// 0xa0aa8c0 转化为 0xc0a80a0a, 也就是 192.168.10.10
	u32 key;
	int err;
	key = ntohl(cfg->fc_dst);

	// 此处创建fib_info, 主要包含下一跳的地址信息
	fi = fib_create_info(cfg, extack);

	// 此处寻找再fib_table中 是否已经存在响应的节点， 
	l = fib_find_node(t, &tp, key);

	// 这里是处理一些node存在的情况
	// TODO 此处当存在时, 如何处理
	if (fa && fa->fa_dscp == dscp &&
	    fa->fa_info->fib_priority == fi->fib_priority) {}

	// 分配新的fib_alias
	new_fa = kmem_cache_alloc(fn_alias_kmem, GFP_KERNEL);	
	// 保存下一跳的信息
	new_fa->fa_info = fi;
	new_fa->fa_dscp = dscp;
	new_fa->fa_type = cfg->fc_type;
	new_fa->fa_state = 0;
	new_fa->fa_slen = slen;
	new_fa->tb_id = tb->tb_id;
	new_fa->fa_default = -1;
	new_fa->offload = 0;
	new_fa->trap = 0;
	new_fa->offload_failed = 0;
	
	err = fib_insert_alias(t, tp, l, new_fa, fa, key);
}

// 将 fib_alias 插入 trie
static int fib_insert_alias(struct trie *t, struct key_vector *tp,
			    struct key_vector *l, struct fib_alias *new,
			    struct fib_alias *fa, t_key key)
{
	// 这里判断key_vector原先存在这个 
	// 如果不存在, 则新建一个node
	if (!l)
		return fib_insert_node(t, tp, new, key);
	// 旧的存在
	// TODO
	if (fa) {
		hlist_add_before_rcu(&new->fa_list, &fa->fa_list);
	}
}

// 将 fib_alias 挂载在 key_vector 下
static int fib_insert_node(struct trie *t, struct key_vector *tp,
			   struct fib_alias *new, t_key key)
{
	// 此处创建了一个key_vector
	l = leaf_new(key, new);
	// 此处计算一下应该把leaf挂载哪个key_vector
	n = get_child(tp, get_index(key, tp));

	// 如果找到key_vector, 可能要替换
	// 这里找到自己可能要挂载的父节点
	// 例如, 如果后缀如果是32位, 当前如果是24, 则一定会找到32这个节点, 
	// 在初始化的时候, 这个可能是个leaf
	if (n) {
		struct key_vector *tn;
		// 这里key^n->key, 是获取当前key和父节点的key的差距
		// 举个例子 192.168.10.10/32 和 192.168.10.10/24, 前缀应该都是一样的, 区别就在后缀
		// 0000 与 1010, 异或后得到了 1010, 而获取最高位的1, 所以得到了3, 那么实际上, 在前缀24位应该是相同的
		// 此时应该保存的是 key=192.168.121.0, 相同前缀是24, 而当前保存的是pos=3, 意思是一样的
		// TODO: 理解为什么不使用 (key, _fls(key ^ n->key) + 1, 0)
		// DONE: 这里是为了刚好存储, 以后应该要把192.168.121.100/32 和 192.168.121.100/24, 存储在一个节点下
		tn = tnode_new(key, __fls(key ^ n->key), 1);
		if (!tn)
			goto notnode;

		// 先把tn的parent挂成tp, 后续是把leaf存在tn下
		NODE_INIT_PARENT(tn, tp);

		put_child(tn, get_index(key, tn) ^ 1, n);

		/* start adding routes into the node */
		put_child_root(tp, key, tn);
		node_set_parent(n, tn);

		/* parent now has a NULL spot where the leaf can go */
		tp = tn;
	}

	/**
	1. 这里解释以下的操作, 首先需要找到cidr上能包含new_leaf的tp节点, 例如192.168.121.0/21 可以包含 192.168.121.0/24
	谁的前缀更短, 后缀更长, 谁就可以包含谁
	2. 找到以后, 从new_leaf这个key_vector根据container_of反查到tnode, 然后将步骤1找到的父节点挂在tnode->parent下
	*/
	// 一旦准备将alias放入这个链里面后, 所有的后缀长度都要更新
	node_push_suffix(tp, new->fa_slen);
	// TODO 应该是将 leaf这个key_vector挂载tp下
	NODE_INIT_PARENT(l, tp);
	// 挂载子节点
	put_child_root(tp, key, l);
	// 平衡节点
	trie_rebalance(t, tp);
}

// slen是后缀长度, 192.168.121.0/24, 则slen长度是 32 - 24 = 8
// 例当前的 key_vector, slen 是 0, 后缀是32, 而new leaf是8, 肯定是不能插在这里的, 
// 得继续向上查找知道找到包含或者等于其后缀的点, 例如192.168.121.0/21, 此时slen是32 - 21 = 11
// 其实可以用plen比较更直观, parent.plen >= new_leaf.plen
// 此处可以提交 patch, 需要先检查 tn 是否为非空
static void node_push_suffix(struct key_vector *tn, unsigned char slen)
{
	while (tn->slen < slen) {
		tn->slen = slen;
		tn = node_parent(tn);
	}
}

// 分配tnode节点
static struct key_vector *tnode_new(t_key key, int pos, int bits)
{
	// 这里说明一下, slen包含了相同前缀的消息,
	// pos和bits, 包含放置index和个数的信息
	// 那么其实就是在 slen转化为前缀后, 和 pos 之间是最大可存放的数量
	// 例如 192.168.121.0/24中, 后续挂在这个节点下的, 当前具有相同的key前缀, 
	// 在这个例子上slen是8, 前缀是24, 假设pos是3, 位置是从pos3开始, 到slen8, 
	// 此时总共存了 8-3+1=4, 那么bit可取值就是 0-2
	unsigned int shift = pos + bits;
	// 分配tnode
	tnode = tnode_alloc(bits);
	// TODO 这里分配的原理
	if (bits == KEYLENGTH)
		tnode->full_children = 1;
	else
		tnode->empty_children = 1ul << bits;
	// 还是一样, 这里tnode指向了key_vector
	tn = tnode->kv;
	// 这里的key, 先向右移动(pos + bits), 左移pos, 是为了保持前缀一致, 再左移bits, 
	// 是为了保存bits位, 所以要保持放进去的, 也要保存前缀一致, 
	// 再右移原来位, 是为了把不一致的全部变成0
	// 这里存pos和slen一样为了保存不一致的后缀个数
	tn->key = (shift < KEYLENGTH) ? (key >> shift) << shift : 0;
	tn->pos = pos;
	tn->bits = bits;
	// TODO: 此处为什么slen不是shift, 
	// 这里的key如果是去除4位, 得到的应该是192.168.121.0/24, 所以slen应该是4才对
	tn->slen = pos;	
}

// 这里n其实是在tnode生成后, tnode->kv, 这里反过来取得tnode, 然后把他的父节点设置为p
#define NODE_INIT_PARENT(n, p) RCU_INIT_POINTER(tn_info(n)->parent, p)

// 重新平衡
static void trie_rebalance(struct trie *t, struct key_vector *tn)
{
	// IS_TRIE判断一般是挂载主节点, 也就是fib_table下的key_vector
	// 节点已经到了IS_TRIE, 不再继续需要平衡了
	while (!IS_TRIE(tn))
		tn = resize(t, tn);
}

#define MAX_WORK 10
// 这里一般是fib_table的trie
static struct key_vector *resize(struct trie *t, struct key_vector *tn)
{
	// 根据node, 从tnode反查parent key_vector
	struct key_vector *tp = node_parent(tn);

	unsigned long cindex = get_index(tn->key, tp);

	// 这里计算是否需要翻倍
	// 判断的逻辑是 100 * (not_double + 2*double) / (child*2)
	// 是否大于 high, 也就是其inflate_threshold, 当为leaf时, 为50, 否则为30
	// TODO: not_double = child - empty - full, 这里为什么not_double不为0
	while (should_inflate(tp, tn) && max_work) {
		// 
		tp = inflate(t, tn);
	}
}


static struct key_vector *inflate(struct trie *t,
				  struct key_vector *oldtnode)
{
	// 这一步做的就是, 创建一个新的key_vector, 
	// 将原有的oldnote的子节点挂上去, 但是多留了一位置, 从pos-1来看, 应该是开头的位置留空了
	tn = tnode_new(oldtnode->key, oldtnode->pos - 1, oldtnode->bits + 1);
}

// 将child节点推送进父节点
static inline void put_child_root(struct key_vector *tp, t_key key,
				  struct key_vector *n)
{
	// 这里判断是不是trie, 根据宏定义的展开
	// 一般来说, 如果是fib_trie_table这个函数生成的trie下挂的key_vector就是一个ISTRIE
	// 如果是leaf_new生成的, 那就是ISLEAF了
	// 可以看到如果是TRIE那就直接挂了
	if (IS_TRIE(tp))
		rcu_assign_pointer(tp->tnode[0], n);
	else
	    // TODO 扩展分配
		put_child(tp, get_index(key, tp), n);	
}

// 创建leaf
static struct key_vector *leaf_new(t_key key, struct fib_alias *fa)
{
	// 分配一个tnode
	kv = kmem_cache_alloc(trie_leaf_kmem, GFP_KERNEL);

	// 创建一个tnode, 然后把key_vector挂载tnode下
	// TODO: 为什么挂载在tnode下, key_vector下的 leaf和tnode只是结构体而已?
	// DONE: 后续挂载 empty_child_dec, 根据 key_vector 反差 tnode, 
	// 这里也是 IS_TRIE 判断的基础, 如果是挂载主节点 pos和len设置是 4*8 
	// 一般是考虑将 子节点 挂载 TRIE 下
	struct tnode *kv;
	l = kv->kv;
	l->key = key;
	l->pos = 0;
	l->bits = 0;
	l->slen = fa->fa_slen;

	/* link leaf to fib alias */
	INIT_HLIST_HEAD(&l->leaf);
	// 将 fa 挂载leaf下
	hlist_add_head(&fa->fa_list, &l->leaf);
}

// 
static inline void empty_child_dec(struct key_vector *n)
{
	if (!tn_info(n)->empty_children)
		tn_info(n)->full_children--;

	tn_info(n)->empty_children--;
}

// 创建 fib_info
struct fib_info *fib_create_info(struct fib_config *cfg,
				 struct netlink_ext_ack *extack)
{
	// 此处检查scope
	// TODO 此处为什么不是检查相等
	if (fib_props[cfg->fc_type].scope > cfg->fc_scope) {
		NL_SET_ERR_MSG(extack, "Invalid scope");
		goto err_inval;
	}

	// 此处检查 fc nh id, 下一跳的id
	if (cfg->fc_nh_id) {
	}

	// 此处处理当路由数量超过限制时的处理方式
	// TODO 处理错误情况
	if (READ_ONCE(fib_info_cnt) >= fib_info_hash_size) {}

	// 此处时分配 fib_info, 主要是
	fi = kzalloc(struct_size(fi, fib_nh, nhs), GFP_KERNEL);

	// 保存一些配置信息
	// TODO 区分 nh 和 fib_nhs 的区别
	fi->fib_net = net;
	fi->fib_protocol = cfg->fc_protocol;
	fi->fib_scope = cfg->fc_scope;
	fi->fib_flags = cfg->fc_flags;
	fi->fib_priority = cfg->fc_priority;
	fi->fib_prefsrc = cfg->fc_prefsrc;
	fi->fib_type = cfg->fc_type;
	fi->fib_tb_id = cfg->fc_table;
	// 保存下一跳的地址信息, 新创建的时候, 此处应该是空的
	fi->fib_nhs = nhs;

	// 刚创建的时候应该是空的, 
	// TODO 非空的时候的处理方式
	if (nh) {
	} else {
		// 此处其实就遍历 fib_nh 这个数组
		change_nexthops(fi) {
			// 让这个数组内的 nh 都以这个为父 fib_info
			// TODO 此处为什么要这么设置, 具体的数据结构为何
			nexthop_nh->nh_parent = fi;
		} endfor_nexthops(fi)

		if (cfg->fc_mp)
			err = fib_get_nhs(fi, cfg->fc_mp, cfg->fc_mp_len, cfg,
					  extack);
		else
			// 初始化下一跳
			err = fib_nh_init(net, fi->fib_nh, cfg, 1, extack);
	}
}

/* rcu_read_lock needs to be hold by caller from readside */
static struct key_vector *fib_find_node(struct trie *t,
					struct key_vector **tp, u32 key)
{
	struct key_vector *pn, *n = t->kv;
	unsigned long index = 0;

	do {
		pn = n;
		// 获取index, 首次的index为0, 后续的index为上次根据key 亦或运算得到的
		n = get_child_rcu(n, index);

		if (!n)
			break;
		// e
		index = get_cindex(key, n);
		if (index >= (1ul << n->bits)) {
			n = NULL;
			break;
		}

	// 一直查找 知道找到leaf为止, 但是返回的是leaf挂载的node
	// 对于添加操作, 没有找到leaf也没有关系, 因为此处可作为父节点 插入点
	} while (IS_TNODE(n));

	*tp = pn;

	return n;
}
```


## 路由选择
1. 系统调用
``` c
int __sys_connect(int fd, struct sockaddr __user *uservaddr, int addrlen) {}
int inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
			int addr_len, int flags) {}
int __inet_stream_connect(struct socket *sock, struct sockaddr *uaddr,
			  int addr_len, int flags, int is_sendmsg) {}
int tcp_v4_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len) {}
static inline struct rtable *ip_route_connect(struct flowi4 *fl4, __be32 dst,
					      __be32 src, int oif, u8 protocol,
					      __be16 sport, __be16 dport,
					      const struct sock *sk) {}
static inline struct rtable *__ip_route_output_key(struct net *net,
						   struct flowi4 *flp) {}
struct rtable *ip_route_output_key_hash(struct net *net, struct flowi4 *fl4,
					const struct sk_buff *skb) {}
struct rtable *ip_route_output_key_hash_rcu(struct net *net, struct flowi4 *fl4,
					    struct fib_result *res,
					    const struct sk_buff *skb) {}
```

2. 路由表查找
``` c
static inline int fib_lookup(struct net *net, struct flowi4 *flp,
			     struct fib_result *res, unsigned int flags)
{
	// TODO 
	if (net->ipv4.fib_has_custom_rules)
		return __fib_lookup(net, flp, res, flags);

	// 先在main表里面查找
	// 一般没有指明路由表的, 都会被默认添加进main
	tb = rcu_dereference_rtnl(net->ipv4.fib_main);
	if (tb)
		err = fib_table_lookup(tb, flp, res, flags);
}

/* should be called with rcu_read_lock */
int fib_table_lookup(struct fib_table *tb, const struct flowi4 *flp,
		     struct fib_result *res, int fib_flags)
{
	cindex = 0;
	// 首先获取第一个子节点
	n = get_child_rcu(pn, cindex);


	for (;;) {
		// 这里去找最长的路径匹配, 
		index = get_cindex(key, n);
		// 这里检查一下, 如果获取index超过包含的个数, 那么这个节点肯定不存在
		if (index >= (1ul << n->bits))
			break;
		// 如果说找到了, 并且是个leaf, 则说明这个leaf一定存了fib_info信息
		// 那就是个合法的路由
		if (IS_LEAF(n))
			goto found;
		// 后续就是找到了, 但是是个node, 得接着往下找
		if (n->slen > n->pos) {
			pn = n;
			cindex = index;
		}

		// 这里继续获取下一个
		n = get_child_rcu(n, index);
		if (unlikely(!n))
			goto backtrace;
	}

	// 能找到这里, 说明最长前缀匹配没找到合适的leaf
	for (;;) {
		struct key_vector __rcu **cptr = n->tnode;

		
	}
}
```




# 插入路由信息 















## 笔记
1. 将 main作为 alias 挂载 local 下, 然后将两者都存在全局的 hashtable fib_table_hash 中, 
但是实际上 fib_new_table 返回 fib_magic 的却是 local

## 参考文档
https://www.acwing.com/blog/content/23314/  
https://blog.csdn.net/arm7star/article/details/125950936   
https://www.infvie.com/ops-notes/linux-policy-routing.html  