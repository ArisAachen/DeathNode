## 知识点 
1. 中断处理例程上下文无法被阻塞, 
2. 中断号要么是探测获取的, 要么是动态确定的 
3. request_irq中, flags的作用:   
IRQF_DISABLED  中断处理例程执行期间, 禁止所有中断      
IRQF_SAMPLE_RANDOM  
IRQF_TIMER  定时器中断   
IRQF_SHARED 共享中断线 
4. mask_and_ack_8259A 

## 流程
1. 取得中断码
2. 标志寄存器入栈
3. 设置标志寄存器的TF和IF位
4. CS和IP寄存器入栈
5. 将中断类型码 * 4    中断类型码 * 4 + 2 存入 IP和CS


## 硬件中断
``` c
DEFINE_IDTENTRY_IRQ(common_interrupt) {
	desc = __this_cpu_read(vector_irq[vector]);
	if (likely(!IS_ERR_OR_NULL(desc)))
		handle_irq(desc, regs);
}

static __always_inline void handle_irq(struct irq_desc *desc,
				       struct pt_regs *regs)
{
	if (IS_ENABLED(CONFIG_X86_64))
		generic_handle_irq_desc(desc);
}

static inline void generic_handle_irq_desc(struct irq_desc *desc)
{
	desc->handle_irq(desc);
}

void handle_level_irq(struct irq_desc *desc)
{
	handle_irq_event(desc);
}

irqreturn_t handle_irq_event(struct irq_desc *desc)
{
	ret = handle_irq_event_percpu(desc);    
}

irqreturn_t handle_irq_event_percpu(struct irq_desc *desc)
{
	retval = __handle_irq_event_percpu(desc);
}

irqreturn_t __handle_irq_event_percpu(struct irq_desc *desc)
{

}
```


## 软件中断
``` c
DEFINE_IDTENTRY_IRQ(common_interrupt) {

}

void irq_exit_rcu(void)
{
	__irq_exit_rcu();	
}

static inline void __irq_exit_rcu(void)
{
	if (!in_interrupt() && local_softirq_pending())
		invoke_softirq();	
}

static inline void invoke_softirq(void)
{
		__do_softirq();	
}

__do_softirq()

```


## 工作队列 
``` c
pool_workqueue
```

## 关键点
### 待处理的软中断会被检查和执行
1. 从一个硬件中断代码处返回时
2. 在ksoftirqd内核线程中
3. 在那些显式检查和执行待处理的软中断的代码中，如网络子系统中

### 知识点
1. 如果同一个软中断在它被执行的同时再次被触发了，那么另外一个处理器可以同时运行其处理程序。这意味着任何共享数据都需要严格的锁保护  
2. tasklet本质上也是软中断，只不过同一个处理程序的多个实例不能在多个处理器上同时运行

## TODO
ret_from_intr 的机制 



## 文档
https://www.cnblogs.com/hustcat/archive/2009/08/11/1543889.html 