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




## 参考
http://linux-ip.net/html/tools-ip-neighbor.html      
https://zhuanlan.zhihu.com/p/28929126      