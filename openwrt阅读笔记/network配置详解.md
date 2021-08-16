## 存放路径
openwrt存放配置的路劲为 /etc/config/network

## 工具命令行
ubus 

## 配置详解

### Interface
通常配置格式为 

config interface 'xxx'
    option device 'xxx' 接口指定设备
    option 



### VLAN
通常在OSI二层进行分区，虚拟局域网，用于一张网卡虚拟成多张虚拟网卡，而不互相影响。使用VLAN ID