## 说明
iw工具：iw工具是iwconfig的替代者，iw可以用于2种“认证和加密”，分别是open（开放系统认证+有效等线加密）、wep方式（共享秘钥认证+有效等线加密）。

## ip features
展示所有支持的特性

``` shell
➜  ~ iw features
nl80211 features: 0x1
        * split wiphy dump
```


## ip commands 
展示所有支持的命令和编号

``` shell
➜  ~ iw commands
1 (0x1): get_wiphy
2 (0x2): set_wiphy
3 (0x3): new_wiphy
4 (0x4): del_wiphy
5 (0x5): get_interface
... ...
```

## iw list
列出所有网络设备和能力

``` shell
➜  ~ iw list
Wiphy phy0
max # scan SSIDs: 9
Supported Ciphers:
                 * WEP40 (00-0f-ac:1)
                 * WEP104 (00-0f-ac:5)
Supported interface modes:          
                 * IBSS
                 * managed
                 * AP
Band 1:
     Capabilities: 0x1962
... ...     
```


## iw dev
列出所有无线设备的硬件信息

``` shell
➜  ~ iw dev
phy#0
        Interface wlx08beac1c11e8
                ifindex 3
                wdev 0x1
                addr 96:62:6f:62:4e:f4
                type managed
                txpower 12.00 dBm
```

### iw dev add 
新增接口 