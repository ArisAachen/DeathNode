## 说明
TCP: Transmission Control Protocol        
RFC: https://datatracker.ietf.org/doc/html/rfc793       
ECN: Explicit Congestion Notification 显式拥塞通知

## 报文头

``` c
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          Source Port          |       Destination Port        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                        Sequence Number                        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Acknowledgment Number                      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Data |           |U|A|P|R|S|F|                               |
| Offset| Reserved  |R|C|S|S|Y|I|            Window             |
|       |           |G|K|H|T|N|N|                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           Checksum            |         Urgent Pointer        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Options                    |    Padding    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                             data                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

在linux内核源码中，定义了如下结构体:
struct tcphdr {
	__be16	source;
	__be16	dest;
	__be32	seq;
	__be32	ack_seq;
#if defined(__LITTLE_ENDIAN_BITFIELD)
	__u16	res1:4,
		doff:4,
		fin:1,
		syn:1,
		rst:1,
		psh:1,
		ack:1,
		urg:1,
		ece:1,
		cwr:1;
#elif defined(__BIG_ENDIAN_BITFIELD)
	__u16	doff:4,
		res1:4,
		cwr:1,
		ece:1,
		urg:1,
		ack:1,
		psh:1,
		rst:1,
		syn:1,
		fin:1;
#else
#error	"Adjust your <asm/byteorder.h> defines"
#endif	
	__be16	window;
	__sum16	check;
	__be16	urg_ptr;
};

source: 来源端口 16位端口号
dest:   目标端口 16位端口号
seq:    第一个数据的序列号  32位
ack_seq:    当前期望接收下一位 seq+len+1 32位
doff:       数据偏移量 4位

res1:       保留字段, 4位   协议中位6位 (res1+ece+cwr)
ece:        ECN-Echo, 拥塞通知 1位
cwr:        Congestion Window Reduced, 确认收到ECE通知

urg:        紧急标识 1位， 此时Urgent Pointer也会被设置
ack:        确认号是否合法
psh:        PUSH标志的数据，置1时请求的数据段在接收方得到后就可直接送到应用程序，而不必等到缓冲区满时才传送。
rst:        用于复位因某种原因引起出现的错误连接，也用来拒绝非法数据和请求。如果接收到RST位时候，通常发生了某些错误。
syn:        用来建立连接，在连接请求中，SYN=1，ACK=0，连接响应时，SYN=1，ACK=1。
fin:        用来释放连接，表明发送方已经没有数据发送了

window:     窗口大小
check:      校验和
urg_ptr:    紧急指针
__LITTLE_ENDIAN_BITFIELD 小端
__BIG_ENDIAN_BITFIELD    大端
```