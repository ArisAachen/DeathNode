## 说明
ip-monitor 持续监控设备状态，地址和路由状态改变     
ip-tunnel tunnel配置工具

## ip-monitor

``` shell 
       ip monitor [ all | OBJECT-LIST ] [ file FILENAME ] [ label ] [
               all-nsid ] [ dev DEVICE ]
               
OBJECT-LIST:    the list of object types that we want to monitor.
       It may contain link, address, route, mroute, prefix, neigh,
       netconf, rule, nsid and nexthop.
```

``` shell 
# 监控固定设备
➜  ~ sudo ip monitor dev eno1
2: eno1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP group default 
    link/ether a8:a1:59:2e:fc:5f brd ff:ff:ff:ff:ff:ff
Deleted fdf1:c66:60e8::/64 proto kernel metric 100 pref medium
Deleted fe80::/64 proto kernel metric 100 pref medium
Deleted default via fdf1:c66:60e8::1 proto static metric 100 pref medium
Deleted local fdf1:c66:60e8::122 table local proto kernel metric 0 pref medium
Deleted local fe80::303f:2f36:3f8c:c591 table local proto kernel metric 0 pref medium
```

``` shell 
# 只监控设备ip地址改变
➜  ~ ip monitor address dev eno1
Deleted 2: eno1    inet6 fdf1:c66:60e8::122/64 scope global noprefixroute 
       valid_lft forever preferred_lft forever
Deleted 2: eno1    inet6 fe80::303f:2f36:3f8c:c591/64 scope link noprefixroute 
       valid_lft forever preferred_lft forever
Deleted 2: eno1    inet 10.20.43.136/24 brd 10.20.43.255 scope global dynamic noprefixroute eno1
       valid_lft 28559sec preferred_lft 28559sec
```

## ip-tunnel

### ip tunnel show
展示tunnel设备

``` shell
➜  ~ ip tunnel show 
tun1: ip/ip remote 10.20.45.243 local 10.20.43.136 ttl inherit
```

### ip tunnel add
新增tunnel设备和规则

``` shell
       ip [ OPTIONS ] tunnel add  [
               NAME ]
               [ mode MODE ] [ remote ADDR ] [ local ADDR ]
               [ [i|o]seq ] [ [i|o]key KEY ] [ [i|o]csum ] ]
               [ encaplimit ELIM ] [ ttl|hoplimit TTL ]
               [ tos TOS ] [ flowlabel FLOWLABEL ]
               [ prl-default ADDR ] [ prl-nodefault ADDR ] [ prl-delete
               ADDR ]
               [ 6rd-prefix ADDR ] [ 6rd-relay_prefix ADDR ] [ 6rd-reset
               ]
               [ [no]pmtudisc ] [ [no]ignore-df ] [ [no]allow-
               localremote ]
               [ dev PHYS_DEV ]

# local 必须是在本主机存在的其他设备的ip
# dev 绑定tunnel到该设备
# mode 模式  { ipip | gre | sit | isatap | vti | ip6ip6 | ipip6 |
               ip6gre | vti6 | any }
```

``` shell 
➜  ~ sudo ip tunnel add tun1 mode ipip local 10.20.43.136 remote 10.20.45.243
➜  ~ ip tunnel show 
tun1: ip/ip remote 10.20.45.243 local 10.20.43.136 ttl inherit
```

``` shell 
➜  ~ sudo ip tunnel add tun2 mode ip6ip6 local any remote fe02::02
➜  ~ ip tunnel show mode ip6ip6 
ip6tnl0: ipv6/ipv6 remote :: local :: encaplimit 0 hoplimit inherit tclass 0x00 flowlabel 0x00000 (flowinfo 0x00000000)
tun2: ipv6/ipv6 remote fe02::1 local :: encaplimit 4 hoplimit 64 tclass 0x00 flowlabel 0x00000 (flowinfo 0x00000000)
```