## 说明
systemd 配置用于启动进程等一系列功能, 分为 systemd 和 user

## service 文件
用于开机自启或者管理进程服务的文件
1. [Unit] 区块
Description 服务描述, 会在 systemd 的启动日志中打印出来      
Documentation 给出文档的位置 
After 需要在列出的服务启动后, 再启动     
Before 定义了应该在哪些服务开启之前启动        
Wants 存在弱依赖关系, 即使启动失败也不影响服务启动, 只关乎依赖, 不关乎启动顺序         
Requires 标识强依赖, 如果启动失败, 则另一个也会被退出, 只关乎依赖, 不关乎启动顺序          
Requisite 如果依赖的服务没启动, 则该服务也不会被启动, 或者立马结束      
BindsTo/PartOf 类似于 Requires      
Conflicts 冲突, 指出两个服务是冲突的, 会在另一个服务关闭后, 再启动该服务       
OnFailure 此服务被激活失败时, 应该被激活的 unit        
OnSuccess 当此服务被激活成功时, 应该被激活的 unit       

ConditionArchitecture "x86"或者"arm64"等， 只有满足这些架构, 服务才会启动
ConditionVirtualization  "qemu" "kvm" 或者 "docker"等, 只有满足这些条件才会启动
ConditionFirstBoot 系统第一次启动时 才会启动服务
ConditionPathExists 配置存在时, 才会启动
ConditionUser/ConditionGroup 满足用户时 才会启动

参考文档:  
https://www.freedesktop.org/software/systemd/man/systemd.unit.html#

``` log 
1月 04 09:30:15 aris-PC systemd[1]: Starting Network Manager...
1月 04 09:30:22 aris-PC systemd[1]: Started Network Manager.
```

``` conf
[Unit]
Description=Network Manager
Documentation=man:NetworkManager(8)
Wants=network.target
After=network-pre.target dbus.service
Before=network.target
```

2. [Install] 区块  
Alias 启动时使用的别名, 设置 enable 时, 会创建别名的连接指向该服务配置           
WantedBy/RequiredBy 相当于 Want/Require 的相反, 会在需要的 .wants 和 .requires 目录下创建配置         
Also 当服务被启动时, 也启动此处的服务            

``` conf
[Install]
WantedBy=graphical.target
Also=NetworkManager-dispatcher.service
```

3. [Service] 区块
Type 