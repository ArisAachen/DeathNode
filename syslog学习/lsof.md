## 说明
lsof (lists openfiles)： 列出打开文件   
而在unix系统中都是以文件形式存在的


## 命令

``` shell 
       lsof [ -?abChlnNOPRtUvVX ] [ -A A ] [ -c c ] [ +c c ] [ +|-d d ] [ +|-D
       D ] [ +|-e s ] [ +|-E ] [ +|-f [cfgGn] ] [ -F [f] ] [ -g [s] ] [ -i [i]
       ]  [ -k k ] [ -K k ] [ +|-L [l] ] [ +|-m m ] [ +|-M ] [ -o [o] ] [ -p s
       ] [ +|-r [t[m<fmt>]] ] [ -s [p:s] ] [ -S [t] ] [ -T [t] ] [ -u  s  ]  [
       +|-w ] [ -x [fl] ] [ -z [z] ] [ -Z [Z] ] [ -- ] [names]
```

### 参数详解

-u 输出属于某个用户的文件信息

``` shell
➜  ~ lsof -u aris
ode      6505 aris   89u     unix 0x0000000000000000       0t0     248026 type=STREAM
code      6505 aris   90u     unix 0x0000000000000000       0t0     248027 type=STREAM
code      6505 aris   91u     unix 0x0000000000000000       0t0     246288 type=SEQPACKET
code      6505 aris   92u     unix 0x0000000000000000       0t0     246289 type=SEQPACKET
```

-p 属于某个进程id的文件信息

``` shell
➜  ~ lsof -p 4274
lsof: WARNING: can't stat() tracefs file system /sys/kernel/debug/tracing
      Output information may be incomplete.
COMMAND  PID USER   FD      TYPE             DEVICE  SIZE/OFF    NODE NAME
chrome  4274 aris  cwd       DIR               8,22      4096  810584 /home/aris
chrome  4274 aris  rtd       DIR               8,22      4096       2 /
chrome  4274 aris  txt       REG               8,22 179134080  931842 /opt/google/chrome/chrome
chrome  4274 aris  mem       REG               8,22   1048576 1180133 /home/aris/.config/google-chrome/CrashpadMetrics-active.pma
```

-c 标志


-s 选取协议protocol
