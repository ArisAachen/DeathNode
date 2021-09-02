## 说明
iw phy命令用于展示无线设备物理层信息


## iw phy info
显示物理层能力

``` shell
root@OpenWrt:~# iw phy0 info
Wiphy phy0
        wiphy index: 0
        max # scan SSIDs: 4
        max scan IEs length: 2247 bytes
        max # sched scan SSIDs: 0
        max # match sets: 0
        Retry short limit: 7
        Retry long limit: 4
        Coverage class: 0 (up to 0m)
        Device supports AP-side u-APSD.
        Device supports T-DLS.
        Available Antennas: TX 0x3 RX 0x3
        Configured Antennas: TX 0x3 RX 0x3
        Supported interface modes:
                 * IBSS
                 * managed
                 * AP
                 * AP/VLAN
                 * monitor
                 * mesh point
                 * P2P-client
                 * P2P-GO
```


## iw phy wowlan
无线局域网唤醒
``` shell
# 显示唤醒状态
➜  ~ iw phy phy0 wowlan show
WoWLAN is disabled.
```

``` shell 
# 设置可被唤醒的操作
# any disconnect magic-packet eap-identity-request ...
➜  ~ sudo iw phy phy0 wowlan enable any 
➜  ~ iw phy phy0 wowlan show            
WoWLAN is enabled:
 * wake up on special any trigger
```

``` shell
# 取消wowlan
➜  ~ sudo iw phy phy0 wowlan disable
➜  ~ iw phy phy0 wowlan show        
WoWLAN is disabled.
```

## iw phy coalesce 
用于数据包合并,减少接收到包的数量，达到降低功耗的作用
``` shell
➜  ~ iw phy phy0 coalesce show
command failed: Operation not supported (-95)
```

## iw phy add
新增设备接口

命令行参数
``` shell
	phy <phyname> interface add <name> type <type> [mesh_id <meshid>] [4addr on|off] [flags <flag>*]
	
type:	
	managed: 普通的STA模式或者AP mode   类似于  infrastructure AP, 当使用hotspad会自动转化为ap mode
	ibss: Idependent Basic Service Set mode 端对端模式   ad-hoc
	monitor:  sniffer抓包模式，不发送 只接收
	mesh:  多设置之间的路由
	wds:  Wireless Distribution System mode AP之间的连接模式  4addr相关
```

``` shell
➜  ~ sudo iw phy wlan0 interface add wlanTest type managed
```


## iw phy set

### ip phy set netns 
设置netns命名空间
``` shell
➜  ~ sudo iw phy phy0 set netns 2086
```

### iw phy set rts
设置rts阈值

``` shell
➜  ~ sudo iw phy phy0 set rts -70
```

``` shell
➜  ~ sudo iw --debug phy phy0 set rts off
-- Debug: Sent Message:
--------------------------   BEGIN NETLINK MESSAGE ---------------------------
  [NETLINK HEADER] 16 octets
    .nlmsg_len = 36
    .type = 24 <0x18>
    .flags = 5 <REQUEST,ACK>
    .seq = 1630547266
    .port = 1086344415
  [GENERIC NETLINK HEADER] 4 octets
    .cmd = 2
    .version = 0
    .unused = 0
  [PAYLOAD] 16 octets
    08 00 01 00 00 00 00 00 08 00 40 00 ff ff ff ff ..........@.....
---------------------------  END NETLINK MESSAGE   ---------------------------
-- Debug: Received Message:
--------------------------   BEGIN NETLINK MESSAGE ---------------------------
  [NETLINK HEADER] 16 octets
    .nlmsg_len = 36
    .type = 2 <ERROR>
    .flags = 256 <ROOT>
    .seq = 1630547266
    .port = 1086344415
  [ERRORMSG] 20 octets
    .error = 0 "??"
  [ORIGINAL MESSAGE] 16 octets
    .nlmsg_len = 16
    .type = 24 <0x18>
    .flags = 5 <REQUEST,ACK>
    .seq = 1630547266
    .port = 1086344415
---------------------------  END NETLINK MESSAGE   ---------------------------
```

### iw phy set freq
设置运行的频段

``` shell
Usage:  iw [options] phy <phyname> set freq <freq> [NOHT|HT20|HT40+|HT40-|5MHz|10MHz|80MHz]
        phy <phyname> set freq <control freq> [5|10|20|40|80|80+80|160] [<center1_freq> [<center2_freq>]]
```

``` shell
➜  ~ sudo iw --debug phy phy0 set freq 2422
-- Debug: Sent Message:
--------------------------   BEGIN NETLINK MESSAGE ---------------------------
  [NETLINK HEADER] 16 octets
    .nlmsg_len = 60
    .type = 24 <0x18>
    .flags = 5 <REQUEST,ACK>
    .seq = 1630548496
    .port = -650089922
  [GENERIC NETLINK HEADER] 4 octets
    .cmd = 2
    .version = 0
    .unused = 0
  [PAYLOAD] 40 octets
    08 00 01 00 00 00 00 00 08 00 26 00 76 09 00 00 ..........&.v...
    08 00 9f 00 00 00 00 00 08 00 27 00 00 00 00 00 ..........'.....
    08 00 a0 00 76 09 00 00                         ....v...
---------------------------  END NETLINK MESSAGE   ---------------------------
-- Debug: Received Message:
--------------------------   BEGIN NETLINK MESSAGE ---------------------------
  [NETLINK HEADER] 16 octets
    .nlmsg_len = 80
    .type = 2 <ERROR>
    .flags = 0 <>
    .seq = 1630548496
    .port = -650089922
  [ERRORMSG] 20 octets
    .error = -16 "??????"
  [ORIGINAL MESSAGE] 16 octets
    .nlmsg_len = 16
    .type = 24 <0x18>
    .flags = 5 <REQUEST,ACK>
    .seq = 1630548496
    .port = -650089922
---------------------------  END NETLINK MESSAGE   ---------------------------
command failed: Device or resource busy (-16)
```





## 参考
https://wireless.wiki.kernel.org/en/users/documentation/iw      
http://lishiwen4.github.io/wifi/wireless-operation-mode     
http://linuxwireless.sipsolutions.net/en/users/Documentation/iw/__v55.html       
https://blog.csdn.net/a_tu_/article/details/51982976      