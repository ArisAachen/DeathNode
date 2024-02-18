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


### 添加网桥
``` shell
ip link set dev eth0 up
ip addr add dev eth0 192.168.10.10/24
ip route add default via 192.168.10.10

ip link add veth_br type veth peer name veth_eth
ip link add br-lan type bridge
ip link set dev veth_br master br-lan
ip addr add dev br-lan 192.168.20.1/24 
ip addr add dev veth0 192.168.20.10/24 
ip link set dev br-lan up
ip link set dev veth0 up
```


``` c
// 将设备添加进入网桥
int br_add_if(struct net_bridge *br, struct net_device *dev,
	      struct netlink_ext_ack *extack)
{
    // 检查一下是不是桥接的设备
	if (dev->netdev_ops->ndo_start_xmit == br_dev_xmit) {
		NL_SET_ERR_MSG(extack,
			       "Can not enslave a bridge to a bridge");
		return -ELOOP;
	}
	// 此处将设备作为端口添加进入网桥
	p = new_nbp(br, dev);
	// TODO: 创建 sysfs 文件
	err = br_sysfs_addif(p);
    // netpoll没啥用 暂时不关心
	err = br_netpoll_enable(p);
	// 这里其实就是把dev接收函数设置为bridge接收 
	err = netdev_rx_handler_register(dev, br_get_rx_handler(dev), p);

	err = netdev_master_upper_dev_link(dev, br->dev, NULL, NULL, extack);
	// 将设备添加进网桥的端口
	list_add_rcu(&p->list, &br->port_list);
	// 增加技术
	nbp_update_port_count(br);
	// 升级feature
	netdev_update_features(br->dev);
	// TODO: headroom 匹配
	br_hr = br->dev->needed_headroom;
	dev_hr = netdev_get_fwd_headroom(dev);
	if (br_hr < dev_hr)
		update_headroom(br, dev_hr);
	else
		netdev_set_rx_headroom(dev, br_hr);
	// 将设备添加到网桥的hash表中
	if (br_fdb_add_local(br, p, dev->dev_addr, 0))

	// 初始化 vlan
	err = nbp_vlan_init(p, extack);

	// 检查一下设备状态
	// 如果设备都是开启的状态
	// 则开启stp 状态
	if (netif_running(dev) && netif_oper_up(dev) &&
	    (br->dev->flags & IFF_UP))
		br_stp_enable_port(p);
}

// 将设备插入到桥接中 作为一个port 
static struct net_bridge_port *new_nbp(struct net_bridge *br,
				       struct net_device *dev)
{
    // 这里通过便利port_list找到没有用过的index,
    // 后面设置port_id时, 就是根据优先级配合index 计算得出
    index = find_portno(br);
    // 桥接的端口 
	struct net_bridge_port *p;
    // 设置一些基础的参数
	p->br = br;
	netdev_hold(dev, &p->dev_tracker, GFP_KERNEL);
	p->dev = dev;
    // 计算路径消耗
	p->path_cost = port_cost(dev);
	p->priority = 0x8000 >> BR_PORT_BITS;
    // port no 端口号
	p->port_no = index;
    // 这里开始计算port_id, 以及初始化为block状态  
    br_init_port(p);
	// 设置状态 
	br_set_state(p, BR_STATE_DISABLED);
	// TODO: timer
	br_stp_port_timer_init(p);

}

// 将设备添加进网桥的hash表
int br_fdb_add_local(struct net_bridge *br, struct net_bridge_port *source,
		     const unsigned char *addr, u16 vid)
{
	ret = fdb_add_local(br, source, addr, vid);
}

// 将设备添加进网桥的hash表
static int fdb_add_local(struct net_bridge *br, struct net_bridge_port *source,
			 const unsigned char *addr, u16 vid)
{
	struct net_bridge_fdb_entry *fdb;
	fdb = br_fdb_find(br, addr, vid);
	// 查看一下fdb是否存在, 如果存在则删除原先的
	if (fdb) {
		fdb_delete(br, fdb, true);
	}
	// 添加fdb记录到bridge
	fdb = fdb_create(br, source, addr, vid,
			 BIT(BR_FDB_LOCAL) | BIT(BR_FDB_STATIC));	
	// TODO: 添加进地址 
	fdb_add_hw_addr(br, addr);
	return 0;
}

// 添加fdb记录到bridge
static struct net_bridge_fdb_entry *fdb_create(struct net_bridge *br,
					       struct net_bridge_port *source,
					       const unsigned char *addr,
					       __u16 vid,
					       unsigned long flags)
{
	// 分配 fdb 内存
	fdb = kmem_cache_alloc(br_fdb_cache, GFP_ATOMIC);
	// 保存mac信息 
	memcpy(fdb->key.addr.addr, addr, ETH_ALEN);
	// 其实就是添加table
	err = rhashtable_lookup_insert_fast(&br->fdb_hash_tbl, &fdb->rhnode,
					    br_fdb_rht_params);
	// 添加进list
	hlist_add_head_rcu(&fdb->fdb_node, &br->fdb_list);
}

// 根据hash mac地址找一下是否存在对应的地址记录
static struct net_bridge_fdb_entry *br_fdb_find(struct net_bridge *br,
						const unsigned char *addr,
						__u16 vid)
{
	fdb = fdb_find_rcu(&br->fdb_hash_tbl, addr, vid);
	return fdb;
}

// 注册设备的接收函数, 此处是将br_handle_frame, 注册到端口设备的接收函数
// 指定参数为 net_bridge_port
int netdev_rx_handler_register(struct net_device *dev,
			       rx_handler_func_t *rx_handler,
			       void *rx_handler_data)
{
	/* Note: rx_handler_data must be set before rx_handler */
	rcu_assign_pointer(dev->rx_handler_data, rx_handler_data);
	rcu_assign_pointer(dev->rx_handler, rx_handler);
}

// 返回接收函数, 检查一下是不是DSA, 不是则把接收函数设置br_handle_frame
rx_handler_func_t *br_get_rx_handler(const struct net_device *dev)
{
	if (netdev_uses_dsa(dev))
		return br_handle_frame_dummy;

	return br_handle_frame;
}

// TODO
static rx_handler_result_t br_handle_frame(struct sk_buff **pskb)
{

}


// 开启stp端口
void br_stp_enable_port(struct net_bridge_port *p)
{
	br_init_port(p);
	br_port_state_selection(p->br);
	br_ifinfo_notify(RTM_NEWLINK, NULL, p);
}
```


## 接收帧
``` c
static int __netif_receive_skb_core(struct sk_buff **pskb, bool pfmemalloc,
				    struct packet_type **ppt_prev)
{
	rx_handler = rcu_dereference(skb->dev->rx_handler);
	if (rx_handler) {	
		switch (rx_handler(&skb)) {	
		}
	}
}

// 网桥接收包
static rx_handler_result_t br_handle_frame(struct sk_buff **pskb)
{
	// 看看是不是回环
	if (unlikely(skb->pkt_type == PACKET_LOOPBACK))
	// 重置一下cb
	memset(skb->cb, 0, sizeof(struct br_input_skb_cb));
	// 获取port信息, 此处其实就是之前设置的时候, 
	// netdev_rx_handler_register把net_bridge_port设置为了 rx_handler_data
	p = br_port_get_rcu(skb->dev);
	// TODO: 检查一下是否 是tunnel
	if (p->flags & BR_VLAN_TUNNEL)
		br_handle_ingress_vlan_tunnel(skb, p, nbp_vlan_group_rcu(p));	

	// TODO: 是否是local 
	if (unlikely(is_link_local_ether_addr(dest))) {
	}

	// 
	if (unlikely(br_process_frame_type(p, skb)))
		return RX_HANDLER_PASS;

	switch (p->state) {
	case BR_STATE_FORWARDING:
	case BR_STATE_LEARNING:
		if (ether_addr_equal(p->br->dev->dev_addr, dest))
		// 进入bridge
		return nf_hook_bridge_pre(skb, pskb);
	return RX_HANDLER_CONSUMED;	
}

// 处理桥接的hook
static int nf_hook_bridge_pre(struct sk_buff *skb, struct sk_buff **pskb)
{

}
```



## 文档 
https://github.com/beacer/notes/blob/master/kernel/bridging.md 