## 说明
主要讲述使用iw命令连接无线网络的操作

## iw dev scan
使用命令进行扫描网络

命令行参数
``` shell
	dev <devname> scan [-u] [freq <freq>*] [ies <hex as 00:11:..>] [meshid <meshid>] [lowpri,flush,ap-force] [ssid <ssid>*|passive]
    -u 打印出未知的扫描结果
```

``` shell
root@OpenWrt:~# iw dev wlan1 scan
BSS 64:09:80:68:39:97(on wlan1)
        TSF: 621475130794 usec (7d, 04:37:55)
        freq: 2467
        beacon interval: 100 TUs
        capability: ESS (0x0c31)
        signal: -54.00 dBm
        last seen: 224 ms ago
        Information elements from Probe Response frame:
        SSID: uniontech-buqingzhen-2.4G
        HT capabilities:
                Capabilities: 0x11ee
                        HT20/HT40
                        SM Power Save disabled
                        RX HT20 SGI
                        RX HT40 SGI
                        TX STBC
                        RX STBC 1-stream
                        Max AMSDU length: 3839 bytes
                        DSSS/CCK HT40
                Maximum RX AMPDU length 65535 bytes (exponent: 0x003)
                Minimum RX AMPDU time spacing: 4 usec (0x05)
                HT RX MCS rate indexes supported: 0-15, 32
                HT TX MCS rate indexes are undefined
```

``` shell
# 可用于扫描隐藏网络
root@OpenWrt:~# iw dev wlan2 scan ssid Shark
BSS f0:41:c8:75:7b:f0(on wlan1)
        TSF: 2896799184 usec (0d, 00:48:16)
        freq: 2447
        beacon interval: 100 TUs
        capability: ESS (0x1431)
        signal: -30.00 dBm
        last seen: 14456 ms ago
        Information elements from Probe Response frame:
        SSID: Shark
        RSN:     * Version: 1
                 * Group cipher: CCMP
                 * Pairwise ciphers: CCMP
                 * Authentication suites: PSK
                 * Capabilities: 16-PTKSA-RC 1-GTKSA-RC (0x000c)
```


``` shell
# 停止扫描
root@OpenWrt:~# iw dev wlan0 scan trigger
root@OpenWrt:~# iw dev wlan0 scan abort
```

## iw dev connect
iw 仅能连接基础的 wep 类型的认证    
wpa或者wpa2使用wpa_supplicant进行连接   

``` shell
iw wlan0 connect Shark keys d:0:123456789
"123456789" 是密碼   d: default, 0: 第0個密碼  
```

### iw dev link 
查看连接的信息
``` shell
root@OpenWrt:~# iw dev wlan1 link
Connected to f0:41:c8:75:7b:f0 (on wlan1)
        SSID: Shark
        freq: 2427
        RX: 17328 bytes (127 packets)
        TX: 6925 bytes (73 packets)
        signal: -26 dBm
        rx bitrate: 1.0 MBit/s
        tx bitrate: 13.0 MBit/s MCS 8
```

### iw dev offchannel
当连接上某个AP后，继续在其他未连接的信道进行扫描，用来漫游

命令行参数
``` shell
	dev <devname> offchannel <freq> <duration>
		Leave operating channel and go to the given channel for a while.
```

``` shell
➜  ~ sudo iw dev wlx08beac1c11e8 offchannel 2412 5
```

### iw dev cqm rssi
rssi的阈值
``` shell
	dev <devname> cqm rssi <threshold|off> [<hysteresis>]
		Set connection quality monitor RSSI threshold.
```

### iw dev 4addr 
``` shell
root@OpenWrt:~# iw dev wlan1 set 4addr on
```


## 参考
https://www.huaweicloud.com/articles/09f7b6ab2e68ee37294dd6ec64902e53.html   
https://www.wi-fi.org/knowledge-center/faq/what-is-off-channel-scanning-for-wi-fi-access-points-aps     
https://www.wi-fi.org/knowledge-center/faq/what-is-off-channel-scanning-for-wi-fi-client-devices