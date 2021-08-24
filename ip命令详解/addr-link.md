## 说明
ip-address 用于查看网卡状态信息    
ip-link 用于管理链路状态

## ip-address

### ip address show
``` shell
➜  ~ ip address show
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host 
       valid_lft forever preferred_lft forever
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether a8:a1:59:2e:fc:5f brd ff:ff:ff:ff:ff:ff
    inet 10.20.43.136/24 brd 10.20.43.255 scope global dynamic noprefixroute eno1
       valid_lft 27979sec preferred_lft 27979sec
    inet6 fe80::1/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
       
# 列出所有设备ip地址信息    
# 详细参数解析
# mtu 1500 最大传输单位（数据包大小）为1,500字节         
# qdisc pfifo_fast 用于数据包排队     
# state UP 网络接口已启用       
# group default 接口组     
# qlen 1000 传输队列长度       
# link/ether 00:1e:4f:c8:43:fc 接口的 MAC（硬件）地址      
# brd ff:ff:ff:ff:ff:ff 广播地址              
```

``` shell
# 显示设备类型 
➜  ~ ip -details link
3: test_dev: <BROADCAST,MULTICAST> mtu 1000 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 9a:be:ee:1d:f1:4f brd ff:ff:ff:ff:ff:ff promiscuity 0 minmtu 68 maxmtu 65535 
    bridge forward_delay 1500 hello_time 200 max_age 2000 ageing_time 30000 stp_state 0 priority 32768 vlan_filtering 0 vlan_protocol 802.1Q bridge_id 8000.0:0:0:0:0:0 designated_root 8000.0:0:0:0:0:0 root_port 0 root_path_cost 0 topology_change 0 topology_change_detected 0 hello_timer    0.00 tcn_timer    0.00 topology_change_timer    0.00 gc_timer    0.00 vlan_default_pvid 1 vlan_stats_enabled 0 group_fwd_mask 0 group_address 01:80:c2:00:00:00 mcast_snooping 1 mcast_router 1 mcast_query_use_ifaddr 0 mcast_querier 0 mcast_hash_elasticity 4 mcast_hash_max 512 mcast_last_member_count 2 mcast_startup_query_count 2 mcast_last_member_interval 100 mcast_membership_interval 26000 mcast_querier_interval 25500 mcast_query_interval 12500 mcast_query_response_interval 1000 mcast_startup_query_interval 3124 mcast_stats_enabled 0 mcast_igmp_version 2 mcast_mld_version 1 nf_call_iptables 0 nf_call_ip6tables 0 nf_call_arptables 0 numtxqueues 1 numrxqueues 1 gso_max_size 65536 gso_max_segs 65535
```

### 参数详解

``` shell
       ip address [ show [ dev IFNAME ] [ scope SCOPE-ID ] [ to PREFIX ]
               [ FLAG-LIST ] [ label PATTERN ] [ master DEVICE ] [ type
               TYPE ] [ vrf NAME ] [ up ] ]
```

``` shell
# 同一个设备的ipv4 和 ipv6 scope信息是不同的

➜  ~ ip address show scope link
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether a8:a1:59:2e:fc:5f brd ff:ff:ff:ff:ff:ff
    inet6 fe80::1/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever

➜  ~ ip address show scope global
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    link/ether a8:a1:59:2e:fc:5f brd ff:ff:ff:ff:ff:ff
    inet 10.20.43.136/24 brd 10.20.43.255 scope global dynamic noprefixroute eno1
       valid_lft 27181sec preferred_lft 27181sec
```

``` shell
# 根据prefix列出地址信息
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    inet 10.20.43.136/24 brd 10.20.43.255 scope global dynamic noprefixroute eno1
       valid_lft 25410sec preferred_lft 25410sec
```

#### Type

``` shell
       TYPE := [ bridge | bridge_slave | bond | bond_slave | can | dummy
               | hsr | ifb | ipoib | macvlan | macvtap | vcan | veth |
               vlan | vxlan | ip6tnl | ipip | sit | gre | gretap |
               erspan | ip6gre | ip6gretap | ip6erspan | vti | vrf |
               nlmon | ipvlan | lowpan | geneve | macsec ]
```
``` shell
# 查找master

➜  ~ ip address show master virbr0 
7: virbr0-nic: <BROADCAST,MULTICAST> mtu 1500 qdisc pfifo_fast master virbr0 state DOWN group default qlen 1000
    link/ether 52:54:00:54:c1:39 brd ff:ff:ff:ff:ff:ff
```

### ip address add
添加ip地址信息

``` shell
       ip address add IFADDR dev IFNAME [
               LIFETIME ] [ CONFFLAG-LIST ]
```

``` shell
# 添加多ip地址
➜  ~ sudo ip address add 10.20.43.138 dev eno1
➜  ~ ip address show dev eno1 to 10.20.43.0/16
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    inet 10.20.43.136/24 brd 10.20.43.255 scope global dynamic noprefixroute eno1
       valid_lft 25004sec preferred_lft 25004sec
    inet 10.20.43.138/32 scope global eno1
       valid_lft forever preferred_lft forever
```

#### IFADDR

``` shell
       IFADDR := PREFIX | ADDR peer PREFIX [ broadcast ADDR ] [ anycast
               ADDR ] [ label LABEL ] [ scope SCOPE-ID ]
```

#### LIFETIME 

``` shell
# valid_lft from RFC 4862; preferred_lft from RFC 4862
LIFETIME := [ valid_lft LFT ] [ preferred_lft LFT ]
```

``` shell
# ip有效时间 10s 
➜  ~ sudo ip address change 10.20.43.138 dev eno1 valid_lft 10 preferred_lft 5
➜  ~ ip address show dev eno1 to 10.20.43.0/16                
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default qlen 1000
    inet 10.20.43.136/24 brd 10.20.43.255 scope global dynamic noprefixroute eno1
       valid_lft 24725sec preferred_lft 24725sec
```

#### CONFFLAG-LIST

``` shell
       CONFFLAG := [ home | mngtmpaddr | nodad | optimstic |
               noprefixroute | autojoin ]
               
# home ipv6 指home address,移动IP中地址不会随着移动而改变,对应漫游
# nodad ipv6 不进行地址冲突检测    
# optimistic ipv6  
# noprefixroute 不产生一个默认的路由      
# autojoin 与vxlan相关      
```


## ip-link

### ip link show 展示当前链路状态
``` shell
                 ip link show [ DEVICE | group GROUP ] [ up ] [ master
                         DEVICE ] [ type ETYPE ] [ vrf NAME ]
```

``` shell 
➜  ~ ip link show dev eno1      
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
    link/ether a8:a1:59:2e:fc:5f brd ff:ff:ff:ff:ff:ff
```

``` shell
➜  ~ ip link show group default
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP mode DEFAULT group default qlen 1000
link/ether a8:a1:59:2e:fc:5f brd ff:ff:ff:ff:ff:ff
3: test_dev: <BROADCAST,MULTICAST> mtu 1000 qdisc noop state DOWN mode DEFAULT group default qlen 1000
link/ether 9a:be:ee:1d:f1:4f brd ff:ff:ff:ff:ff:ff
4: test_macvlan@eno1: <BROADCAST,MULTICAST> mtu 1000 qdisc noop state DOWN mode DEFAULT group default qlen 1000
link/ether 86:9a:6a:ab:92:82 brd ff:ff:ff:ff:ff:ff
```

### ip link add
新增链路 link

``` shell
       ip link add [ link DEVICE ] [ name ] NAME
               [ txqueuelen PACKETS ]
               [ address LLADDR ] [ broadcast LLADDR ]
               [ mtu MTU ] [ index IDX ]
               [ numtxqueues QUEUE_COUNT ] [ numrxqueues QUEUE_COUNT ]
               [ gso_max_size BYTES ] [ gso_max_segs SEGMENTS ]
               type TYPE [ ARGS ]
```

``` shell 
# 新增链路
➜  ~ sudo ip link add link eno1 name test_dev mtu 1000 index 3 type bridge
3: test_dev: <BROADCAST,MULTICAST> mtu 1000 qdisc noop state DOWN group default qlen 1000
    link/ether 9a:be:ee:1d:f1:4f brd ff:ff:ff:ff:ff:ff
```

### ip link set
设置和替换 链路信息

``` shell
       ip link set { DEVICE | group GROUP }
               [ { up | down } ]
               [ type ETYPE TYPE_ARGS ]
               [ arp { on | off } ]
               [ dynamic { on | off } ]
               [ multicast { on | off } ]
               [ allmulticast { on | off } ]
               [ promisc { on | off } ]
               [ protodown { on | off } ]
               [ protodown_reason PREASON { on | off } ]
               [ trailers { on | off } ]
               [ txqueuelen PACKETS ]
               [ name NEWNAME ]
               [ address LLADDR ]
               [ broadcast LLADDR ]
               [ mtu MTU ]
               [ netns { PID | NETNSNAME } ]
               [ link-netnsid ID ]
               [ alias NAME ]
               [ vf NUM [ mac LLADDR ]
                        [ VFVLAN-LIST ]
                        [ rate TXRATE ]
                        [ max_tx_rate TXRATE ]
                        [ min_tx_rate TXRATE ]
                        [ spoofchk { on | off } ]
                        [ query_rss { on | off } ]
                        [ state { auto | enable | disable } ]
                        [ trust { on | off } ]
                        [ node_guid eui64 ]
                        [ port_guid eui64 ] ]
               [ { xdp | xdpgeneric | xdpdrv | xdpoffload } { off |
                       object FILE [ section NAME ] [ verbose ] |
                       pinned FILE } ]
               [ master DEVICE ]
               [ nomaster ]
               [ vrf NAME ]
               [ addrgenmode { eui64 | none | stable_secret | random } ]
               [ macaddr [ MACADDR ]
                         [ { flush | add | del } MACADDR ]
                         [ set MACADDR ] ]
```

``` shell 
# 开启link
➜  ~ sudo ip address add 10.20.45.156 dev test_dev
➜  ~ sudo ip link set dev test_dev up
➜  ~ ip address show
3: test_dev: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1000 qdisc noqueue state UNKNOWN group default qlen 1000
    link/ether 9a:be:ee:1d:f1:4f brd ff:ff:ff:ff:ff:ff
    inet 10.20.45.156/32 scope global test_dev
       valid_lft forever preferred_lft forever
```

``` shell 
# 开启混杂模式
➜  ~ sudo ip link set promisc on dev test_dev
➜  ~ ip link show dev test_dev 
3: test_dev: <BROADCAST,MULTICAST,PROMISC,UP,LOWER_UP> mtu 1000 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/ether 9a:be:ee:1d:f1:4f brd ff:ff:ff:ff:ff:ff
```

``` shell 
# 设置别名
➜  ~ sudo ip link set dev test_dev alias bridge_dev
➜  ~ sudo ip link show dev test_dev                
3: test_dev: <BROADCAST,MULTICAST,PROMISC,UP,LOWER_UP> mtu 1000 qdisc noqueue state UNKNOWN mode DEFAULT group default qlen 1000
    link/ether 9a:be:ee:1d:f1:4f brd ff:ff:ff:ff:ff:ff
    alias bridge_dev
```

``` shell
# 添加命名空间
# loopback bridge wirelss 不能设置命名空间(wireless使用iw)
➜  ~ sudo ip link set dev eno1 netns `pgrep NetworkManager`

```

### Bridge Slave Support

``` shell 
# Bridge Slave Support支持额外的特性
              ip link set type bridge_slave [ fdb_flush ] [ state STATE
              ] [ priority PRIO ] [ cost COST ] [ guard { on | off } ] [
              hairpin { on | off } ] [ fastleave { on | off } ] [
              root_block { on | off } ] [ learning { on | off } ] [
              flood { on | off } ] [ proxy_arp { on | off } ] [
              proxy_arp_wifi { on | off } ] [ mcast_router
              MULTICAST_ROUTER ] [ mcast_fast_leave { on | off} ] [
              mcast_flood { on | off } ] [ mcast_to_unicast { on | off }
              ] [ group_fwd_mask MASK ] [ neigh_suppress { on | off } ]
              [ vlan_tunnel { on | off } ] [ isolated { on | off } ] [
              backup_port DEVICE ] [ nobackup_port ]
```
