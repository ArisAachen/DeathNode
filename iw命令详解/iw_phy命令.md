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



## 参考
http://lishiwen4.github.io/wifi/wireless-operation-mode     
http://linuxwireless.sipsolutions.net/en/users/Documentation/iw/__v55.html       
https://blog.csdn.net/a_tu_/article/details/51982976      