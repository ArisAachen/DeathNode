

## 中断注册 
``` c
static inline int __must_check
request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags,
	    const char *name, void *dev)
{
	return request_threaded_irq(irq, handler, NULL, flags, name, dev);
}


// 注册中断处理函数
int request_threaded_irq(unsigned int irq, irq_handler_t handler,
			 irq_handler_t thread_fn, unsigned long irqflags,
			 const char *devname, void *dev_id)
{
    // 获取结构体
    struct irq_desc *desc;
    // 根据irq中断号获取desc, 保存在全局的maple_tree中, 
    // 结构体 sparse_irqs
    desc = irq_to_desc(irq);

    // 这里分配一下 irqaction, 用于保存handler信息
    struct irqaction *action;
	action = kzalloc(sizeof(struct irqaction), GFP_KERNEL);
	if (!action)
		return -ENOMEM;
	action->handler = handler;
	action->thread_fn = thread_fn;
	action->flags = irqflags;
	action->name = devname;
	action->dev_id = dev_id;
    // 把irq保存到handler
    retval = __setup_irq(irq, desc, action);
}

// 将action保存到desc中, 也就是保存了中断处理例程
static int
__setup_irq(unsigned int irq, struct irq_desc *desc, struct irqaction *new)
{
    // TODO: irq_chip的作用
    if (desc->irq_data.chip == &no_irq_chip)
		return -ENOSYS;
    // 保存中断号
    new->irq = irq;
    // TODO: 嵌套进程
    nested = irq_settings_is_nested_thread(desc);
	if (nested) {
		if (!new->thread_fn) {
			ret = -EINVAL;
			goto out_mput;
		}
		/*
		 * Replace the primary handler which was provided from
		 * the driver for non nested interrupt handling by the
		 * dummy function which warns when called.
		 */
		new->handler = irq_nested_primary_handler;
	} else {
		if (irq_settings_can_thread(desc)) {
			ret = irq_setup_forced_threading(new);
			if (ret)
				goto out_mput;
		}
	}
    // 获取action
	old_ptr = &desc->action;
	old = *old_ptr;    
    // 这里检查一下中断是否存在
    // 如果存在就继续添加到list里面
    // 并且这个信号必须时允许共享的
    if (old) {
        // 不可屏蔽的中断 不允许共享处理
i       if (desc->istate & IRQS_NMI) {}
        // 这里检查一下是不是共享的, 标志一不一样
		if (!((old->flags & new->flags) & IRQF_SHARED) ||
		    (oldtype != (new->flags & IRQF_TRIGGER_MASK)) ||
		    ((old->flags ^ new->flags) & IRQF_ONESHOT)) {}
		do {
            // 将中断处理例程保存在next后面 
			thread_mask |= old->thread_mask;
			old_ptr = &old->next;
			old = *old_ptr;
		} while (old);
    }
}
```

## 设备初始化
``` c
// 模块初始化
module_init(e1000_init_module);
// 开始初始化模块
static int __init e1000_init_module(void)
{
	// 注册驱动 
	ret = pci_register_driver(&e1000_driver);
}

// 此处是注册驱动的内容
static struct pci_driver e1000_driver = {
	// 驱动名称
	.name     = e1000_driver_name,
	// pci_device_id 设备id, 新增设备时, 搜寻这个字段
	.id_table = e1000_pci_tbl,
	// 设备新增时, 会调用这个函数, 用于新增设备
	.probe    = e1000_probe,
	.remove   = e1000_remove,
	.driver = {
		.pm = &e1000_pm_ops,
	},
	.shutdown = e1000_shutdown,
	.err_handler = &e1000_err_handler
};

// e1000 设备管理
static const struct net_device_ops e1000_netdev_ops = {
	// 设备up时调用, ip link set dev eth0 up 
	.ndo_open		= e1000_open,
	.ndo_stop		= e1000_close,
	// 开始传送数据
	.ndo_start_xmit		= e1000_xmit_frame,
	.ndo_set_rx_mode	= e1000_set_rx_mode,
	.ndo_set_mac_address	= e1000_set_mac,
	.ndo_tx_timeout		= e1000_tx_timeout,
	.ndo_change_mtu		= e1000_change_mtu,
	.ndo_eth_ioctl		= e1000_ioctl,
	.ndo_validate_addr	= eth_validate_addr,
	.ndo_vlan_rx_add_vid	= e1000_vlan_rx_add_vid,
	.ndo_vlan_rx_kill_vid	= e1000_vlan_rx_kill_vid,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller	= e1000_netpoll,
#endif
	.ndo_fix_features	= e1000_fix_features,
	.ndo_set_features	= e1000_set_features,
};

// 新增设备调用函数
static int e1000_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	// 分配net_device
	// 也会分配 设备设置方法 ether_setup
	// 此处记住 net_device 的 net  dev_net_set(dev, &init_net);
	struct net_device *netdev;
	netdev = alloc_etherdev(sizeof(struct e1000_adapter));
	// 分配 adapter 
	struct e1000_adapter *adapter = NULL;
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	// 分配 ndo_open 
	// e1000_xmit_frame 
	netdev->netdev_ops = &e1000_netdev_ops;
	// 设置 ethtool 设置函数
	e1000_set_ethtool_ops(netdev);
	// 将 netdev 保存到 napi
	// 而 adapter 保存在 netdev 后面
	// 将 poll 保存到 napi
	netif_napi_add(netdev, &adapter->napi, e1000_clean);
	// 设置特性
	netdev->features |= netdev->hw_features;
	netdev->hw_features |= (NETIF_F_RXCSUM |
				NETIF_F_RXALL |
				NETIF_F_RXFCS);

	// 注册设备, 此处是将设置一些特性
	// 然后把设备添加进 net, list_netdevice(dev) 
	// netdev_name_node_add(net, dev->name_node)
	// TODO: netdev_run_todo 的原理
	err = register_netdev(netdev);
}

// 设置 iffflags 
SIOCSIFFLAGS
// 检查设备flags, 检查是不是up, 
// 如果是up, 那就调用 e1000_open
int __dev_change_flags(struct net_device *dev, unsigned int flags,
		       struct netlink_ext_ack *extack)
{
	if ((old_flags ^ flags) & IFF_UP) {
		if (old_flags & IFF_UP)
			__dev_close(dev);
		else
			ret = __dev_open(dev, extack);
	}
}

// 设备open, 调用ops->ndo_open
static int __dev_open(struct net_device *dev, struct netlink_ext_ack *extack)
{
	// 获取 netdev_ops
	const struct net_device_ops *ops = dev->netdev_ops;
	int ret;
	// 检查一下是不是ndo_open
	if (!ret && ops->ndo_open)
		ret = ops->ndo_open(dev);
}

// 设备open
int e1000_open(struct net_device *netdev)
{
	// 这里分配ring buffer
	// TODO: 分析分配的策略
	err = e1000_setup_all_tx_resources(adapter);
	err = e1000_setup_all_rx_resources(adapter);
	e1000_configure(adapter);
	// 设置中断处理函数
	err = e1000_request_irq(adapter);
	// 清楚down的标识, 因为是up
	clear_bit(__E1000_DOWN, &adapter->flags);
	// 设置napi状态未enable
	// TODO: 设置的bit位的方式
	napi_enable(&adapter->napi);
	// 设置接受中断信号
	e1000_irq_enable(adapter);
	// 设置打开接受的 netdev_queue, 就是清除 __QUEUE_STATE_DRV_XOFF 
	netif_start_queue(netdev);
}

// 注册中断处理函数
static int e1000_request_irq(struct e1000_adapter *adapter)
{
	// 这里处理的共享信号
	struct net_device *netdev = adapter->netdev;
	irq_handler_t handler = e1000_intr;
	int irq_flags = IRQF_SHARED;
	err = request_irq(adapter->pdev->irq, handler, irq_flags, netdev->name,
			  netdev);
}
```


``` c
maple_tree()
register_sysctl()
register_net_sysctl()
register_net_sysctl_sz()
```

# 文档 
https://www.jianshu.com/p/3738da62f5f6   
https://blog.csdn.net/Rong_Toa/article/details/109401935  