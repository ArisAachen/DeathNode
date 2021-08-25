## 说明
ip-neighbour 地址转发表管理 


## ip-neighbour

### ip neigh show 
显示地址转发表信息  
``` shell 
       ip neigh { show | flush } [ proxy ] [ to PREFIX ] [ dev DEV ] [
               nud STATE ] [ vrf NAME ]

# nud STATE:
# PERMANENT: 永久有效，只能超级权限删除
# NOARP: 永久有效，不验证可行性，到期后消失
# REACHABLE: 一直到可达状态失效都是合法的
# STABLE: 可疑的，但是是合法的
# NONE: 伪状态
# INCOMPLETE: 还未验证
# DELAY: 认证延后
# PROBE: 正在尝试认证
# FAILED: 尝试次数过后仍然失败
```


``` shell 
➜  ~ ip neigh show 10.20.43.136/16
10.20.45.156 dev eno1 lladdr 9a:be:ee:1d:f1:4f PERMANENT
10.20.43.29 dev eno1 lladdr 00:e0:70:d1:5d:a9 STALE
```


### ip neigh add 
新增地址转发表  
``` shell
       ip neigh { add | del | change | replace } { ADDR [ lladdr LLADDR
               ] [ nud STATE ] | proxy ADDR } [ dev DEV ] [ router ] [
               extern_learn ]
```

``` shell 
# 新增一条普通的地址转发表
➜  ~ sudo ip neigh add 10.20.43.139 lladdr aa:aa:aa:aa:aa:ab dev test_dev nud permanent
➜  ~ ip neigh show dev test_dev
10.20.43.139 lladdr aa:aa:aa:aa:aa:ab PERMANENT
```

``` shell
# 设置arp代理(没有设置默认网关)
➜  ~ sudo ip neigh add proxy 10.20.43.1 dev test_dev
➜  ~ ip neigh show 
```

## ip-netns
创建一个独立的network namespace，用于隔离网络资源 

### ip netns
显示所有命名空间信息
``` shell
       ip netns [ list ]
```

``` shell
➜  ~ ip -details netns list                 
ns1 (id: 0)
```

### ip netns add 
新增一个命名空间

``` shell 
       ip netns add NETNSNAME
```

``` shell 
# 新增一个命名空间
➜  ~ sudo ip netns add ns1
➜  ~ ip netns list        
ns1
```

### ip netns attach (uos不支持)
将pid 绑定到 netns

``` shell
       ip netns attach NETNSNAME PID
```

``` shell 
➜  ~ sudo ip netns attach java_ns 1759
➜  ~ ls -al /proc/1759/ns/
lrwxrwxrwx 1 aris aris 0 8月  25 09:57 net -> 'net:[4026532000]'
```

### ip netns set
设置命名空间的id
``` shell 
       ip netns set NETNSNAME NETNSID
```

``` 
# 设置命名空间，仅在当前命名空间内可设置
➜  ~ sudo ip netns exec ns1 ip netns set ns1 999
➜  ~ sudo ip netns exec ns1 ip netns list        
java_ns
ns1 (id: 999)
``` 

### ip netns pids
列出命名空间内的进程

``` shell
       ip netns pids NETNSNAME
```

``` shell
# 在命名空间内执行
➜  ~ sudo ip netns exec ns1 wireshark
➜  ~ sudo ip netns exec ns1 ls -al /proc/27219/ns
lrwxrwxrwx 1 aris aris 0 8月  25 10:15 net -> 'net:[4026532000]'
```

### ip netns monitor
监控命名空间新增和移除
``` shell
➜  ~ sudo ip netns delete ns1
➜  ~ sudo ip netns monitor
delete ns1
```

### ip netns exec
在命名空间内执行操作
``` shell
       ip [-all] netns exec [ NETNSNAME ] command...
```

``` shell
# 新增设备
➜  ~ sudo ip netns exec ns1 ip link add name v_ns1 type veth peer name v1
➜  ~ sudo ip netns exec ns1 ip link show type veth                       
2: v1@v_ns1: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether 46:a7:c8:f7:33:18 brd ff:ff:ff:ff:ff:ff
3: v_ns1@v1: <BROADCAST,MULTICAST,M-DOWN> mtu 1500 qdisc noop state DOWN mode DEFAULT group default qlen 1000
    link/ether fa:67:4c:67:76:26 brd ff:ff:ff:ff:ff:ff
```


## 参考
http://linux-ip.net/html/tools-ip-neighbor.html      
https://zhuanlan.zhihu.com/p/28929126      