## 架构图
传统网络架构图: 
可能存在资源浪费  

![传统网络架构](../asset/tradition.png)



虚拟化架构图

![虚拟化架构](../asset/vm-struct.png)

这一整套虚拟网络的模块都可以独立出去，由第三方来完成，如其中比较出名的一个解决方案就是 Open vSwitch（OVS）。

## 架构图

![虚拟化架构](../asset/OpenVSwitch.png)

## 虚拟化设备

### tun/tap/veth
tap工作在OSI二层，tun在三层。
基于tap驱动，则可以使得虚拟机的vNIC与tap相连，就像NIC与eth设备一样。