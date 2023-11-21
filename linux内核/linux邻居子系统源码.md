# 前置准备
``` shell
ip link set dev eth0 up
ip addr add dev eth0 192.168.10.10/24
ip route add default via 192.168.10.10
```

# 接收arp帧
``` c
// 此处是注册的poll函数
static int e1000_clean(struct napi_struct *napi, int budget) {

}

bool napi_complete_done(struct napi_struct *n, int work_done)
{

}

static inline void gro_normal_list(struct napi_struct *napi)
{

}

void netif_receive_skb_list_internal(struct list_head *head)
{

}

static void __netif_receive_skb_list_core(struct list_head *head, bool pfmemalloc)
{

}

static inline void __netif_receive_skb_list_ptype(struct list_head *head,
						  struct packet_type *pt_prev,
						  struct net_device *orig_dev)
{

}


static int arp_rcv(struct sk_buff *skb, struct net_device *dev,
		   struct packet_type *pt, struct net_device *orig_dev)
{

}
```


## 被动学习
``` c
// 此处是被动学习 更新arp缓存列表
// 收到了其他终端发送的arp探测请求
static int arp_rcv(struct sk_buff *skb, struct net_device *dev,
		   struct packet_type *pt, struct net_device *orig_dev)
{
	// 此处检查是否为广播的地址 loopback地址, 针对于这些地址, 不需要保存arp缓存
    // 因为在发送l2数据包时, 直接使用arp_direct_ops发送
    // 检查一下目的地址是不是本地, 不是的也不处理
	if (dev->flags & IFF_NOARP ||
	    skb->pkt_type == PACKET_OTHERHOST ||
	    skb->pkt_type == PACKET_LOOPBACK)
		goto consumeskb;

	// 
	if (!pskb_may_pull(skb, arp_hdr_len(dev)))
		goto freeskb;
	
	// 此处获取arp的帧头
	arp = arp_hdr(skb);
	if (arp->ar_hln != dev->addr_len || arp->ar_pln != 4)
		goto freeskb;
	
	// 此处查看检查arp hook, 最后进入 arp_process
	return NF_HOOK(NFPROTO_ARP, NF_ARP_IN,
		       dev_net(dev), NULL, skb, dev, NULL,
		       arp_process);
}


static int arp_process(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	// 获取arp头 
	arp = arp_hdr(skb);
	// 检查一下接受本地的设备类型
	switch (dev_type) {
	case ARPHRD_ETHER:
	case ARPHRD_FDDI:
	case ARPHRD_IEEE802:
		// 这里检查一下是不是有线或者无线，
		// 并且要求三层协议是ip
		// 也就意味着虚拟设备不会处理neigh
		if ((arp->ar_hrd != htons(ARPHRD_ETHER) &&
		     arp->ar_hrd != htons(ARPHRD_IEEE802)) ||
		    arp->ar_pro != htons(ETH_P_IP))
			goto out_free_skb;
		break;		
	}

	// 仅处理arp的request和reply
	if (arp->ar_op != htons(ARPOP_REPLY) &&
	    arp->ar_op != htons(ARPOP_REQUEST))
		goto out_free_skb;

	// 这里来解析来源和目标的 ip 和 hardware
	// 协议报文为 source hareware | source ip | target hardware | target ip 
	arp_ptr = (unsigned char *)(arp + 1);
	sha	= arp_ptr;
	arp_ptr += dev->addr_len;
	memcpy(&sip, arp_ptr, 4);
	switch (dev_type) {
		tha = arp_ptr;
		arp_ptr += dev->addr_len;
	}
	memcpy(&tip, arp_ptr, 4);

	// 组播的 或者 回环的设备就不管了
	if (ipv4_is_multicast(tip) ||
	    (!IN_DEV_ROUTE_LOCALNET(in_dev) && ipv4_is_loopback(tip)))
		goto out_free_skb;

	// 给自己发送的不处理	
	if (sip == tip && IN_DEV_ORCONF(in_dev, DROP_GRATUITOUS_ARP))
		goto out_free_skb;
	
	// TODO: 帧协议中继
	if (dev_type == ARPHRD_DLCI)
		sha = dev->broadcast;	
	
	// TODO: 此处意义不明
	if (arp->ar_op == htons(ARPOP_REQUEST) && skb_metadata_dst(skb))
		reply_dst = (struct dst_entry *)
			    iptunnel_metadata_reply(skb_metadata_dst(skb),
						    GFP_ATOMIC);


	// 将来源地址设为0, 此时是dhcp用于检测地址冲突的封包
	// 当终端获取到ip后, 主动请求arp probe
	if (sip == 0) {
		// 收到别打设备的冲突检测时, 此时必须是request
		// 如果本地的ip确实和请求的ip冲突了, 那么就发起回复, 否则就不管了
		// arp_ignore的含义是, 即时目标的ip是eth1, 当eth0收到请求时, 则会把eth0的mac返回
		if (arp->ar_op == htons(ARPOP_REQUEST) &&
		    inet_addr_type_dev_table(net, dev, tip) == RTN_LOCAL &&
		    !arp_ignore(in_dev, sip, tip))
			arp_send_dst(ARPOP_REPLY, ETH_P_ARP, sip, dev, tip,
				     sha, dev->dev_addr, sha, reply_dst);
		goto out_consume_skb;
	}

	// 这里判断一下是否收到的是arp请求, 并且要找到至少一条规则可以直接到达的
	if (arp->ar_op == htons(ARPOP_REQUEST) &&
	    ip_route_input_noref(skb, tip, sip, 0, dev) == 0) {
		// 获取设备类型
		rt = skb_rtable(skb);
		addr_type = rt->rt_type;
		// 检查一下目的是不是本机
		if (addr_type == RTN_LOCAL) {
			int dont_send;
			// 这里其实就是看一下arp_ignore 和 过滤规则的影响
			// 如果被影响到了, 则不发送响应
			dont_send = arp_ignore(in_dev, sip, tip);
			if (!dont_send && IN_DEV_ARPFILTER(in_dev))
				dont_send = arp_filter(sip, tip, dev);
			// 判断出要发送响应了
			if (!dont_send) {
				// 这里查找和创建邻居
				n = neigh_event_ns(&arp_tbl, sha, &sip, dev);
				if (n) {
					arp_send_dst(ARPOP_REPLY, ETH_P_ARP,
						     sip, dev, tip, sha,
						     dev->dev_addr, sha,
						     reply_dst);
					neigh_release(n);
				}
			}
		// 检查当前的设备是否开启了forward
		// 这里应该是处理arp代理的逻辑
		} else if (IN_DEV_FORWARD(in_dev)) {
			if (addr_type == RTN_UNICAST  &&
			    (arp_fwd_proxy(in_dev, dev, rt) ||
			     arp_fwd_pvlan(in_dev, dev, rt, sip, tip) ||
			     (rt->dst.dev != dev &&
			      pneigh_lookup(&arp_tbl, net, &tip, dev, 0)))) {
				n = neigh_event_ns(&arp_tbl, sha, &sip, dev);
				if (n)
					neigh_release(n);

				if (NEIGH_CB(skb)->flags & LOCALLY_ENQUEUED ||
				    skb->pkt_type == PACKET_HOST ||
				    NEIGH_VAR(in_dev->arp_parms, PROXY_DELAY) == 0) {
					arp_send_dst(ARPOP_REPLY, ETH_P_ARP,
						     sip, dev, tip, sha,
						     dev->dev_addr, sha,
						     reply_dst);
				} else {
					pneigh_enqueue(&arp_tbl,
						       in_dev->arp_parms, skb);
					goto out_free_dst;
				}
				goto out_consume_skb;
			}
		}
	}
}

// 查找和创建邻居缓存, 此处创建的原因是因为收到了相应的事件, 
// 主动创建的是另外的逻辑
struct neighbour *neigh_event_ns(struct neigh_table *tbl,
				 u8 *lladdr, void *saddr,
				 struct net_device *dev)
{
	// 查找一下邻居, 不存在的话根据lladdr判断是否应该创建一个邻居
	struct neighbour *neigh = __neigh_lookup(tbl, saddr, dev,
						 lladdr || !dev->addr_len);
	// 创建成功了, 那么就将lladdr保存起来, 
	// 可以懒到
	if (neigh)
		neigh_update(neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_OVERRIDE, 0);
	return neigh;	
}

static inline struct neighbour *
__neigh_lookup(struct neigh_table *tbl, const void *pkey, struct net_device *dev, int creat)
{
	// 这里查找是否存在arp,
	// 如果不存在, 则根据create标识判断是否应该创建邻居记录 
	struct neighbour *n = neigh_lookup(tbl, pkey, dev);
	if (n || !creat)
		return n;
	// 创建neighbor记录 
	return neigh_create(tbl, pkey, dev);
}

// 创建邻居记录 neighbor
static inline struct neighbour *neigh_create(struct neigh_table *tbl,
					     const void *pkey,
					     struct net_device *dev)
{
	return __neigh_create(tbl, pkey, dev, true);
}

// 创建邻居记录 neighbor
struct neighbour *__neigh_create(struct neigh_table *tbl, const void *pkey,
				 struct net_device *dev, bool want_ref)
{
	return ___neigh_create(tbl, pkey, dev, 0, false, want_ref);
}

// 创建邻居记录 neighbor
static struct neighbour *
___neigh_create(struct neigh_table *tbl, const void *pkey,
		struct net_device *dev, u32 flags,
		bool exempt_from_gc, bool want_ref)
{
	struct neighbour *n1, *rc, *n;
	// 分配neighbor空间
	n = neigh_alloc(tbl, dev, flags, exempt_from_gc);
	memcpy(n->primary_key, pkey, key_len);
	n->dev = dev;
	// 初始化邻居系统, 这里调用的是 arp_constructor
	if (tbl->constructor &&	(error = tbl->constructor(n)) < 0) {

	}
	// TODO: 这里暂时没看出什么作用
	if (dev->netdev_ops->ndo_neigh_construct) {
	}

	// TODO: 这里暂时没看出什么作用
	if (n->parms->neigh_setup &&
	    (error = n->parms->neigh_setup(n)) < 0) {
	}

	// 当创建了这个设备, 那当前的时间就是确认的时间
	n->confirmed = jiffies - (NEIGH_VAR(n->parms, BASE_REACHABLE_TIME) << 1);
	// TODO: 这里需要看需不需要扩展
	if (atomic_read(&tbl->entries) > (1 << nht->hash_shift))
		nht = neigh_hash_grow(tbl, nht->hash_shift + 1);
	// 计算出哈希值, 这里调用 arp_tbl->hash
	hash_val = tbl->hash(n->primary_key, dev, nht->hash_rnd) >> (32 - nht->hash_shift);

	// 根据hash获取首个邻居记录, 如果存在哈希相同的时候, 则把新的加到最后一个, 由next连接起来的链表
	// hash值一样, 不一定说明l3地址一定相同, 这里的组织方式是尽量把l3一样的地址串起来
	for (n1 = rcu_dereference_protected(nht->hash_buckets[hash_val],
					    lockdep_is_held(&tbl->lock));
	     n1 != NULL;
	     n1 = rcu_dereference_protected(n1->next,
			lockdep_is_held(&tbl->lock))) {
		// 这里一直找, 直到找到不同的为止
		if (dev == n1->dev && !memcmp(n1->primary_key, n->primary_key, key_len)) {
			rc = n1;
			goto out_tbl_unlock;
		}
	}
	// 看看是否需要添加到gc链表里面, 正常来说, 手动创建的属于permnant, 此时就不需要gc
	if (!exempt_from_gc)
		list_add_tail(&n->gc_list, &n->tbl->gc_list);
	// 添加到管理的链表, 手动创建的需要被管理
	if (n->flags & NTF_MANAGED)
		list_add_tail(&n->managed_list, &n->tbl->managed_list);
	// 将新的邻居放在哈希的第一个
	rcu_assign_pointer(n->next,
			   rcu_dereference_protected(nht->hash_buckets[hash_val],
						     lockdep_is_held(&tbl->lock)));
	rcu_assign_pointer(nht->hash_buckets[hash_val], n);
}

// 分配 neighbor 内存
static struct neighbour *neigh_alloc(struct neigh_table *tbl,
				     struct net_device *dev,
				     u32 flags, bool exempt_from_gc)
{
do_alloc:
	// 分配neighbor内存
	n = kzalloc(tbl->entry_size + dev->neigh_priv_len, GFP_ATOMIC);
	if (!n)
		goto out_entries;
	// arp_queue在neigh检测到成功前, 先将缓存放在arp_queue
	__skb_queue_head_init(&n->arp_queue);
	rwlock_init(&n->lock);
	seqlock_init(&n->ha_lock);
	n->updated	  = n->used = now;
	// 初始化NUD状态
	n->nud_state	  = NUD_NONE;
	// 丢弃arp包函数
	n->output	  = neigh_blackhole;
	n->flags	  = flags;
	seqlock_init(&n->hh.hh_lock);
	n->parms	  = neigh_parms_clone(&tbl->parms);
	// 设置neigh超时检测
	timer_setup(&n->timer, neigh_timer_handler, 0);
	NEIGH_CACHE_STAT_INC(tbl, allocs);
	n->tbl		  = tbl;
	refcount_set(&n->refcnt, 1);
	n->dead		  = 1;
	INIT_LIST_HEAD(&n->gc_list);
	INIT_LIST_HEAD(&n->managed_list);
}

// 初始化arp到状态
static int arp_constructor(struct neighbour *neigh)
{
	// 主key获取到手目标地址的ip地址
	addr = *(__be32 *)neigh->primary_key;
	// 这里要判断一下是不是回环设备, 如果是回环设备, 则设置一下主key
	if (dev->flags & (IFF_LOOPBACK | IFF_POINTOPOINT))
		memcpy(neigh->primary_key, &inaddr_any, arp_tbl.key_len);
	// 获取neigh记录类型
	neigh->type = inet_addr_type_dev_table(dev_net(dev), dev, addr);
	// 复制neigh的参数
	neigh->parms = neigh_parms_clone(parms);
	// TODO: 什么设备才不存在header_ops
	if (!dev->header_ops) {
		neigh->nud_state = NUD_NOARP;
		neigh->ops = &arp_direct_ops;
		neigh->output = neigh_direct_output;
	} else {
		// 多播直接设置no_arp, 因为不需要arp缓存
		if (neigh->type == RTN_MULTICAST) {
			neigh->nud_state = NUD_NOARP;
			arp_mc_map(addr, neigh->ha, dev, 1);		
		// 这里看一下是不是回环
		} else if (dev->flags & (IFF_NOARP | IFF_LOOPBACK)) {
			// 将缓存添加到device的地址
			neigh->nud_state = NUD_NOARP;
			memcpy(neigh->ha, dev->dev_addr, dev->addr_len);
		// 查看一下是不是广播, 直接设置缓存的地址
		} else if (neigh->type == RTN_BROADCAST ||
			   (dev->flags & IFF_POINTOPOINT)) {
			neigh->nud_state = NUD_NOARP;
			memcpy(neigh->ha, dev->broadcast, dev->addr_len);
		}
		// 如果header包函缓存函数, 设置一下, 后面的connect_output和output
		if (dev->header_ops->cache)
			neigh->ops = &arp_hh_ops;	
		else
			// 设置generic
			neigh->ops = &arp_generic_ops;	
		// 检查状态, 如果是可达的, 则调用connected_output, 
		// 否则就调用output, 
		// 对于direct来说, 两者没有区别
		// 对于generic, 则首先会发起arp查询请求, 并把
		if (neigh->nud_state & NUD_VALID)
			neigh->output = neigh->ops->connected_output;
		else
			neigh->output = neigh->ops->output;
	}
}

// 更新neigh信息
int neigh_update(struct neighbour *neigh, const u8 *lladdr, u8 new,
		 u32 flags, u32 nlmsg_pid)
{
	return __neigh_update(neigh, lladdr, new, flags, nlmsg_pid, NULL);
}

// 更新neigh信息
static int __neigh_update(struct neighbour *neigh, const u8 *lladdr,
			  u8 new, u32 flags, u32 nlmsg_pid,
			  struct netlink_ext_ack *extack)
{
	// 获取设备和原始状态
	dev    = neigh->dev;
	old    = neigh->nud_state;
	err    = -EPERM;
	// 这里如果是事件触发的, 则不更新flags, 如果是用户配置的则进行更新
	neigh_update_flags(neigh, flags, &notify, &gc_update, &managed_update);
	// 这里判断一下, 如果是因为事件触发的更新, 则把permanent移除标记
	if (flags & (NEIGH_UPDATE_F_USE | NEIGH_UPDATE_F_MANAGED)) {
		new = old & ~NUD_PERMANENT;
		WRITE_ONCE(neigh->nud_state, new);
		goto out;
	}

	// 判断一下, 新的状态是不是合法的, 即l2是不是可达的
	if (!(new & NUD_VALID)) {
		// 停止定时器
		neigh_del_timer(neigh);
		// 如果旧装是连接的, 但是当前却断开了
		// 此时将output函数改为普通的connect函数
		// 以便后续能重新发出arp request
		if (old & NUD_CONNECTED)
			neigh_suspect(neigh);
		// 保存状态
		WRITE_ONCE(neigh->nud_state, new);
		// 移除合法的状态
		notify = old & NUD_VALID;
		// 如果之前发起了连接, 超时后没有收到响应, 失败了
		// 则处理
		if ((old & (NUD_INCOMPLETE | NUD_PROBE)) &&
		    (new & NUD_FAILED)) {
			neigh_invalidate(neigh);
		}
		// 跳过到out
		goto out;
	}

	// 查看一下设备的支持长度, 这个长度不是本地设备的长度
	// 而是支持邻居协议的长度, 例如arp和nd支持的长度不一样
	if (!dev->addr_len) {
		// 获取neigh的设备地址
		lladdr = neigh->ha;
	} else if (lladdr) {
		// 如果旧的状态是合法的, 但是当前lladdr更新了
		// 就更新了最新的状态
		if ((old & NUD_VALID) &&
		    !memcmp(lladdr, neigh->ha, dev->addr_len))
			lladdr = neigh->ha;		
	} else {
		// 检查设备状态
		err = -EINVAL;
		// 如果旧的状态是可达的, 但是本次更新却没有地址, 则认为更新失败
		if (!(old & NUD_VALID)) {
			NL_SET_ERR_MSG(extack, "No link layer address given");
			goto out;
		}
		// 此处获取lladdr
		lladdr = neigh->ha;
	}

	// 当前最新的状态是连接的, 那就把确认的连接时间更新
	if (new & NUD_CONNECTED)
		neigh->confirmed = jiffies;

	update_isrouter = flags & NEIGH_UPDATE_F_OVERRIDE_ISROUTER;

	// TODO: 
	if (old & NUD_VALID) {
		if (lladdr != neigh->ha && !(flags & NEIGH_UPDATE_F_OVERRIDE)) {
			update_isrouter = 0;
			if ((flags & NEIGH_UPDATE_F_WEAK_OVERRIDE) &&
			    (old & NUD_CONNECTED)) {
				lladdr = neigh->ha;
				new = NUD_STALE;
			} else
				goto out;
		} else {
			if (lladdr == neigh->ha && new == NUD_STALE &&
			    !(flags & NEIGH_UPDATE_F_ADMIN))
				new = old;
		}
	}
	// 看看新旧状态和lladdr是不是都需要更新, 如果是则更新一下状态
	if (new != old || lladdr != neigh->ha)
		neigh->updated = jiffies;
	// 新旧状态如果不一样
	if (new != old) {
		neigh_del_timer(neigh);
		// 旧状态不是probe, 新状态为probe
		// 当旧状态nud_delay超过delay_probe_time没收到回应
		// 此时需要重新尝试发起连接
		if (new & NUD_PROBE)
			atomic_set(&neigh->probes, 0);
		// TODO:
		if (new & NUD_IN_TIMER)
			neigh_add_timer(neigh, (jiffies +
						((new & NUD_REACHABLE) ?
						 neigh->parms->reachable_time :
						 0)));
	}

	// 判断一下是否新旧的lladdr是否一致, 如果不一致则需要更新 
	if (lladdr != neigh->ha) {
		// 将新的lladdr拷贝进来
		memcpy(&neigh->ha, lladdr, dev->addr_len);
		// 这里去更新header cache
		neigh_update_hhs(neigh);
		// 新状态不是非连接状态
		if (!(new & NUD_CONNECTED))
			neigh->confirmed = jiffies -
				      (NEIGH_VAR(neigh->parms, BASE_REACHABLE_TIME) << 1);
	}
	// 新旧状态则快速跳过
	if (new == old)
		goto out;
	// 更新output函数
	if (new & NUD_CONNECTED)
		neigh_connect(neigh);
	else
		neigh_suspect(neigh);
	// 如果旧状态不是合法的
	if (!(old & NUD_VALID)) {
		struct sk_buff *skb;
		// 这里检查一下新的状态, 如果新状态为合法的, 并且之前有skb的缓存, 
		// 也就意味着之前发送了arp请求, 暂时把skb缓存起来, 此时很可能收到了相应
		// 那么应该把arp_queue的缓存都发出去, 因为已经找到neigh都l2地址
		while (neigh->nud_state & NUD_VALID &&
		       (skb = __skb_dequeue(&neigh->arp_queue)) != NULL) {
			// 获取dst
			struct dst_entry *dst = skb_dst(skb);
			struct neighbour *n2, *n1 = neigh;
			// TODO: 这里调整n1
			if (dst && dst->obsolete != DST_OBSOLETE_DEAD) {
				n2 = dst_neigh_lookup_skb(dst, skb);
				if (n2)
					n1 = n2;
			}
			// 通过n1的output发出, 正常来说应该是connected_output
			n1->output(n1, skb);
		}
		// 发完了清空缓存
		__skb_queue_purge(&neigh->arp_queue);
		neigh->arp_queue_len_bytes = 0;
	}
	// TODO:
	if (update_isrouter)
		neigh_update_is_router(neigh, flags, &notify);
	// 这里就是判断一下新的和旧的包不包含permant, 
	// 如果都不包含, 不用管gc_list了
	if (((new ^ old) & NUD_PERMANENT) || gc_update)
		neigh_update_gc_list(neigh);
	if (managed_update)
		neigh_update_managed_list(neigh);
	if (notify)
		neigh_update_notify(neigh, nlmsg_pid);
}

// TODO
static void neigh_invalidate(struct neighbour *neigh)
	__releases(neigh->lock)
	__acquires(neigh->lock)
{
	// 把arp_queue全部清空
	// 然后发送了通告
	while (neigh->nud_state == NUD_FAILED &&
	       (skb = __skb_dequeue(&neigh->arp_queue)) != NULL) {
		write_unlock(&neigh->lock);
		neigh->ops->error_report(neigh, skb);
		write_lock(&neigh->lock);
	}
	__skb_queue_purge(&neigh->arp_queue);
	neigh->arp_queue_len_bytes = 0;
}

// 更新header cache
static void neigh_update_hhs(struct neighbour *neigh)
{
	struct hh_cache *hh;
	void (*update)(struct hh_cache*, const struct net_device*, const unsigned char *)
		= NULL;
	// 这里就是看看有没有header_ops, 即提供header cache功能
	if (neigh->dev->header_ops)
		update = neigh->dev->header_ops->cache_update;
	if (update) {
		hh = &neigh->hh;
		update(hh, neigh->dev, neigh->ha);		
	}
}
```

## 主动学习
tcp传输 
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
	err = INDIRECT_CALL_INET(icsk->icsk_af_ops->queue_xmit,
				 inet6_csk_xmit, ip_queue_xmit,
				 sk, skb, &inet->cork.fl);
}

int ip_queue_xmit(struct sock *sk, struct sk_buff *skb, struct flowi *fl)
{
	return __ip_queue_xmit(sk, skb, fl, inet_sk(sk)->tos);
}

int __ip_queue_xmit(struct sock *sk, struct sk_buff *skb, struct flowi *fl,
		    __u8 tos)
{
	res = ip_local_out(net, sk, skb);
}

static int ip_finish_output2(struct net *net, struct sock *sk, struct sk_buff *skb)
{
	neigh = ip_neigh_for_gw(rt, skb, &is_v6gw);
	if (!IS_ERR(neigh)) {
		// 这里其实就是确认一下是否获取dst的响应, 如果是的话, 就更新neigh信息
		sock_confirm_neigh(skb, neigh);
		// 发送arp请求, 以便更新neigh信息
		res = neigh_output(neigh, skb, is_v6gw);
	}
}

static inline struct neighbour *ip_neigh_for_gw(struct rtable *rt,
						struct sk_buff *skb,
						bool *is_v6gw)
{
		neigh = ip_neigh_gw4(dev, ip_hdr(skb)->daddr);
}

static inline struct neighbour *ip_neigh_gw4(struct net_device *dev,
					     __be32 daddr)
{
	struct neighbour *neigh;

	neigh = __ipv4_neigh_lookup_noref(dev, (__force u32)daddr);
	if (unlikely(!neigh))
		neigh = __neigh_create(&arp_tbl, &daddr, dev, false);

	return neigh;
}

static inline int neigh_output(struct neighbour *n, struct sk_buff *skb,
			       bool skip_cache)
{
	const struct hh_cache *hh = &n->hh;
	if (!skip_cache &&
	    (READ_ONCE(n->nud_state) & NUD_CONNECTED) &&
	    READ_ONCE(hh->hh_len))
		return neigh_hh_output(hh, skb);
	// 在arp_constructor设置的了output
	// 正常来说, 当第一次发送的连接时, dhcp请求后, 会触发arp, 此时output指向neigh_connected_output
	// 如果是手动配置的ip路由规则, 则此时output指向了neigh_resolve_output, 因为需要进行dns解析
	return n->output(n, skb);
}

// 此时还没有建立neigh状态, 则调用arp请求更新neigh
int neigh_resolve_output(struct neighbour *neigh, struct sk_buff *skb)
{
	if (!neigh_event_send(neigh, skb)) {

	}
}

// 这里发送arp请求, 以更新neigh信息
// 获取成功时, 将状态切换为connected, 并且设置output为neigh_connected_output
static inline int neigh_event_send(struct neighbour *neigh, struct sk_buff *skb)
{
	return neigh_event_send_probe(neigh, skb, true);
}

// 发送arp请求, 尝试更新neigh
static __always_inline int neigh_event_send_probe(struct neighbour *neigh,
						  struct sk_buff *skb,
						  const bool immediate_ok)
{
	unsigned long now = jiffies;
	if (READ_ONCE(neigh->used) != now)
		WRITE_ONCE(neigh->used, now);
	// 检查一下设备是不是含有这些状态, 如果不是以下的连接状态或者请求状态
	// 则发送arp请求
	if (!(READ_ONCE(neigh->nud_state) & (NUD_CONNECTED | NUD_DELAY | NUD_PROBE)))
		return __neigh_event_send(neigh, skb, immediate_ok);
	return 0;
}

// 则发送arp请求
int __neigh_event_send(struct neighbour *neigh, struct sk_buff *skb,
		       const bool immediate_ok)
{
	// 检查一下状态, 当设备不处于stale, 即还未过期, 但是又一段时间未确认
	// 或者不处于 当设备请求已经发送, 但是未收到回应
	// 也就是说其他状态都要经过此处处理, 也就是当初始化的时候, 一定得进入此逻辑
	if (!(neigh->nud_state & (NUD_STALE | NUD_INCOMPLETE))) {
		// 检查状态参数, 如果之前已经发送过arp探测了, 
		// MCAST_PROBES 代表多播的arp探测和 APP_PROBES 代表应用探测
		// 此时, 应该清空定时器，重置定时器, 以便发起连接
		if (NEIGH_VAR(neigh->parms, MCAST_PROBES) +
		    NEIGH_VAR(neigh->parms, APP_PROBES)) {
			// 设置状态, 因为是发起请求, 未收到响应时, 则就是incomplete
			WRITE_ONCE(neigh->nud_state, NUD_INCOMPLETE);
			// 看看是不是应该立马发起, 
			// 如果不是立马请求, 则使用RETRANS_TIME
			// 通常来说, 初始化时, 应该需要立马发送arp请求
			if (!immediate_ok) {
				next = now + 1;
			} else {
				immediate_probe = true;
				next = now + max(NEIGH_VAR(neigh->parms,
							   RETRANS_TIME),
						 HZ / 100);
			}
			// 添加定时器
			neigh_add_timer(neigh, next);			
		} else {
			// TODO: 此处直接设置为failed, 理由
			WRITE_ONCE(neigh->nud_state, NUD_FAILED);
			neigh->updated = jiffies;
			return 1;
		}
	// 如果只包含nud_stale
	} else if (neigh->nud_state & NUD_STALE) {
		// 如果旧设备处于stale, 则将状态设为delay,
		// 然后设置定时器
		neigh_del_timer(neigh);
		WRITE_ONCE(neigh->nud_state, NUD_DELAY);
		neigh->updated = jiffies;
		neigh_add_timer(neigh, jiffies +
				NEIGH_VAR(neigh->parms, DELAY_PROBE_TIME));
	}

	// 看看之前是不是incomplete, 如果是, 则说明发送了请求, 但是未收到响应
	// 此时, 先把arp请求存在arp_queue, 
	if (neigh->nud_state == NUD_INCOMPLETE) {
		if (skb) {
			// 这里做的事情就是, 一直把arp_queue往外丢, 
			// 停止的条件有两个, 1. arp_queue丢光了 2. 把skb放到arp_queue不会超过限制
			// 这里这么做的原因是防止arp_queue超过限制的QUEUE_LEN_BYTES长度
			while (neigh->arp_queue_len_bytes + skb->truesize >
			       NEIGH_VAR(neigh->parms, QUEUE_LEN_BYTES)) {
				buff = __skb_dequeue(&neigh->arp_queue);
				if (!buff)
					break;
				neigh->arp_queue_len_bytes -= buff->truesize;
				kfree_skb_reason(buff, SKB_DROP_REASON_NEIGH_QUEUEFULL)；
			}
			// 将skb放在arp_queue, 此arp_queue存放后, 也不会超过限制
			__skb_queue_tail(&neigh->arp_queue, skb);
			neigh->arp_queue_len_bytes += skb->truesize;
		}
	}

out_unlock_bh:
	// 这里看看是不是应该发生arp请求
	if (immediate_probe)
		neigh_probe(neigh);

out_dead:
	// 此处判断如果是stale, 则看看是不是应该立马发送neigh, 如果不是, 那么就等待一下
	if (neigh->nud_state & NUD_STALE)
		goto out_unlock_bh;

}

// 发送arp请求
static void neigh_probe(struct neighbour *neigh)
	__releases(neigh->lock)
{
	// 获取skb
	struct sk_buff *skb = skb_peek_tail(&neigh->arp_queue);
	// 这里需要复制skb
	// TODO: 为什么需要复制
	if (skb)
		skb = skb_clone(skb, GFP_ATOMIC);
	// 发送solicit请求
	// 如果是arp_direct_ops则不需要处理, 直接发送即可
	// arp_generic_ops处理函数为 arp_solicit
	if (neigh->ops->solicit)
		neigh->ops->solicit(neigh, skb);
	// 释放skb
	consume_skb(skb);
}

// 发送arp请求
static void arp_solicit(struct neighbour *neigh, struct sk_buff *skb)
{
	__be32 target = *(__be32 *)neigh->primary_key;	
	// 获取ip配置信息
	in_dev = __in_dev_get_rcu(dev);
	// 这里判断arp_announce, 根据不同的值, 采取不同的策略
	switch (IN_DEV_ARP_ANNOUNCE(in_dev)) {
	// 当值是0时, 选择ip和网卡时, 会根据源source ip和合适的mac发送arp请求
	// 当设置为1时, 会尽量选择source ip和合适的mac发送arp请求
	// 当设置为2时, 会选择合适的ip和mac发送arp请求
	default:
	case 0:
		if (skb && inet_addr_type_dev_table(dev_net(dev), dev,
					  ip_hdr(skb)->saddr) == RTN_LOCAL)
			// 这里获取的是设备对应的ip, 也就是source ip
			saddr = ip_hdr(skb)->saddr;
			break;
		break;
	// 如果是2的话, 自动获取最合适的saddr, 此处表现为直接break
	case 2:
		break;
	}

	// 这里如果是1或者2的话, 则可能需要寻找saddr
	if (!saddr)
		saddr = inet_select_addr(dev, target, RT_SCOPE_LINK);
	
	// 获取参数的arp请求的次数
	probes -= NEIGH_VAR(neigh->parms, UCAST_PROBES);
	// TODO: 
	if (probes < 0) {
	} else {
		probes -= NEIGH_VAR(neigh->parms, APP_PROBES);
		if (probes < 0) {
			neigh_app_ns(neigh);
			return;
		}		
	}
	
	// 发送arp的请求
	// 原先skb的请求都存在arp_queue
	// 等待响应到达后, arp_queue将原先的请求一次性发送出去
	// 消费的函数在 __neigh_update 
	arp_send_dst(ARPOP_REQUEST, ETH_P_ARP, target, dev, saddr,
		     dst_hw, dev->dev_addr, NULL, dst);
}

```

## 文档
https://blog.csdn.net/xiaoyu_750516366/article/details/104590052  
https://www.jianshu.com/p/734640384fda 