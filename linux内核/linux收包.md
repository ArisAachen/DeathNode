## 接收帧的模式
轮询:
中断: 
定时器驱动的中断事件:  


## 名词
接收-活锁: 中断产生后, 先将帧拷贝到内核的输入队列, 然后再处理帧。中断会抢占处理帧, 当不断有中断数据, 输入队列满了, 但是没办法继续处理了   



## 文档 
https://blog.csdn.net/weixin_38387929/article/details/118185914 
https://www.cnblogs.com/dream397/p/14536368.html  
https://zhuanlan.zhihu.com/p/256428917  