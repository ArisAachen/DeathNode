## 说明
ip-rule是路由策略的说明，指定了某些策略绑定ip route路由表


## ip-rule

### ip rule list
列出所有的路由表

``` shell
➜  ~ ip rule list
0:      from all lookup local 
32766:  from all lookup main 
32767:  from all lookup default
```

其中三条缺省规则，lookup 寻找路由表
local 对应 255 表
main 对应 254表
default 对应 253表

``` c
➜  ~ ip route show table default 
➜  ~ ip route show table 253 
```
可以看出都是空的

可以自定义 1 - 252 张route表

### 关系图
![rule_route](../asset/rule_route.jpg)

### 参数详解

#### ip rule list 打印目标规则
可以直接使用，也可以在后面加参数    
模板 ip rule list Selector

``` c
➜  ~ ip rule list to 192.168.1.1
32765:  from 10.42.88.8 to 192.168.1.1 lookup main
```

#### ip rule add 添加规则
模板 ip rule add Selector Action   
比list多出action




#### Selector
``` doc
       SELECTOR := [ not ] [ from PREFIX ] [ to PREFIX ] [ tos TOS ] [
               fwmark FWMARK[/MASK] ] [ iif STRING ] [ oif STRING ] [
               pref NUMBER ] [ l3mdev ] [ uidrange NUMBER-NUMBER ] [
               ipproto PROTOCOL ] [ sport [ NUMBER | NUMBER-NUMBER ] ] [
               dport [ NUMBER | NUMBER-NUMBER ] ] [ tun_id TUN_ID ]
```

``` shell
// from/to PREFIX 标记网段
➜  ~ sudo ip rule add from 10.22.0.0/16 table main
➜  ~ ip rule list
32762:  from 10.22.0.0/16 lookup main
```

``` shell
// iif 入口设备 
➜  ~ sudo ip rule add iif eno1 table local
➜  ~ ip rule list
32761:  from all iif eno1 lookup local
```

#### Action
``` doc
       ACTION := [ table TABLE_ID ] [ protocol PROTO ] [ nat ADDRESS ] [
               realms [SRCREALM/]DSTREALM ] [ goto NUMBER ] SUPPRESSOR
               
       nat 已废弃
```

``` shell
// unreachable 丢弃某些数据包
➜  ~ sudo ip rule add to 220.181.0.0/16 unreachable
➜  ~ ping baidu.com
connect: 网络不可达
```

## ip-route
