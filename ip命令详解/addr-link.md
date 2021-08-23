## 说明
ip-address 用于查看网卡状态信息

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
# 查找master

➜  ~ ip address show master virbr0 
7: virbr0-nic: <BROADCAST,MULTICAST> mtu 1500 qdisc pfifo_fast master virbr0 state DOWN group default qlen 1000
    link/ether 52:54:00:54:c1:39 brd ff:ff:ff:ff:ff:ff
```

``` shell
       TYPE := [ bridge | bridge_slave | bond | bond_slave | can | dummy
               | hsr | ifb | ipoib | macvlan | macvtap | vcan | veth |
               vlan | vxlan | ip6tnl | ipip | sit | gre | gretap |
               erspan | ip6gre | ip6gretap | ip6erspan | vti | vrf |
               nlmon | ipvlan | lowpan | geneve | macsec ]
```