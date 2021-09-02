## 说明
iw dev 提供了类似于ip phy的功能，包含扩展功能


## iw dev

展示所有 dev 列表信息

``` shell
➜  ~ iw dev
phy#0
        Interface wlx08beac1c11e8
                ifindex 5
                wdev 0x1
                addr 36:3b:7f:94:a9:fc
                type managed
                txpower 12.00 dBm
```

``` shell
➜  ~ iw dev wlx08beac1c11e8 info
Interface wlx08beac1c11e8
        ifindex 5
        wdev 0x1
        addr 36:3b:7f:94:a9:fc
        type managed
        wiphy 0
        txpower 12.00 dBm
```

## iw dev interface add 
新增接口 

``` shell
➜  ~ iw dev wlan1 interface add wlan2 type managed
➜  ~ iw dev
phy#1
        Interface wlan2
                ifindex 9
                wdev 0x100000003
                addr 20:76:93:35:77:f1
                type managed
                txpower 20.00 dBm
        Interface wlan1
                ifindex 8
                wdev 0x100000002
                addr 20:76:93:35:77:f0
                type managed
                txpower 20.00 dBm
phy#0
        Interface wlan0
                ifindex 3
                wdev 0x1
                addr 20:76:93:35:77:f2
                type managed
                txpower 20.00 dBm
                multicast TXQ:
                        qsz-byt qsz-pkt flows   drops   marks   overlmt hashcol tx-bytes        tx-packets
                        0       0       0       0       0       0       0       0               0
```

## iw dev ibss
加入和离开ibss

### iw dev ibss join
命令行参数
``` shell
	dev <devname> ibss join <SSID> <freq in MHz> [HT20|HT40+|HT40-|NOHT|5MHZ|10MHZ] [fixed-freq] [<fixed bssid>] [beacon-interval <TU>] [basic-rates <rate in Mbps,rate2,...>] [mcast-rate <rate in Mbps>] [key d:0:abcde]
```

### iw dev ibss leave
命令行参数
``` shell
	dev <devname> ibss leave
```


## iw dev station
作为AP服务时，获取连接的STA信息

### iw dev station dump
打印连接当前AP的STA信息
``` shell
root@OpenWrt:~# iw dev wlan1 station dump
Station f0:41:c8:75:7b:f0 (on wlan1)
        inactive time:  15508 ms
        rx bytes:       68789
        rx packets:     444
        tx bytes:       116272
        tx packets:     254
        tx retries:     46
        tx failed:      6
        rx drop misc:   23
        signal:         -32 dBm
        signal avg:     -35 dBm
        tx bitrate:     52.0 MBit/s MCS 11
        tx duration:    0 us
        rx bitrate:     6.0 MBit/s
        rx duration:    0 us
        expected throughput:    28.106Mbps
        authorized:     yes
        authenticated:  yes
        associated:     yes
        preamble:       short
        WMM/WME:        yes
        MFP:            no
        TDLS peer:      no
        DTIM period:    2
        beacon interval:100
        short preamble: yes
        short slot time:yes
        connected time: 35 seconds
        associated at [boottime]:       152980.686s
        associated at:  18446725625584882366 ms
        current time:   18446744072175974514 ms
```

### iw dev station set vlan