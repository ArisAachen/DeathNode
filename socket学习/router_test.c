//
// Created by aris on 2021/9/26.
//


//from BSD
/*
 * 路由域支持的唯一套接字是原始套接字
 * 创建AF_ROUTE域
 * 1) 进程可以通过路由套接字往内核发送消息
 * 2) 路由套接字可以读取来自内核的消息
 * 3) 使用sysctl函数到处路由表和接口
 * */

/*
 * if down设备使用 RTM_IFINFO  if_msghdr
 * add addr RTM_NEWADDR RTM_DELADDR 使用 ifa_msghdr
 * add multicast RTM_NEWMADDR RTM_DELMADDR 使用 ifma_msghdr
 * iface add and delete RTM_IFANNOUNCE 使用 if_announcemsghdr
 * other message 其他使用 rt_msghdr
 * */

