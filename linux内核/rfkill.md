``` c
int main(int argc, char **argv)
{
	if (argc > 0) {
		act = string_to_action(*argv);

	switch (act) {
	case ACT_EVENT:
		ret = rfkill_event();
		break;
    }        
}

static int string_to_action(const char *str)
{
	for (i = 0; i < ARRAY_SIZE(rfkill_actions); i++)
		if (strcmp(str, rfkill_actions[i]) == 0)
			return i;    
}

static int rfkill_event(void)
{
	while (1) {
		if (n)
			rc = rfkill_read_event(fd, &event);
    }
}


static int rfkill_block(uint8_t block, const char *param)
{
	id = rfkill_id_to_type(param);

	switch (id.result) {
	case RFKILL_IS_TYPE:
		event.type = id.type;
		xasprintf(&message, "type %s", param);
		break;
	case RFKILL_IS_INDEX:
		event.op = RFKILL_OP_CHANGE;
		event.idx = id.index;
		xasprintf(&message, "id %d", id.index);
		break;
	case RFKILL_IS_ALL:
		message = xstrdup("all");
		break;
    }

	fd = open(_PATH_DEV_RFKILL, O_RDWR);

	len = write(fd, &event, sizeof(event));            
}

```










``` c
static struct input_handler rfkill_handler = {
	.event = rfkill_event,
}


static void rfkill_event(struct input_handle *handle, unsigned int type,
			unsigned int code, int data)
{
	if (type == EV_KEY && data == 1) {
		switch (code) {
		case KEY_WLAN:
			rfkill_schedule_toggle(RFKILL_TYPE_WLAN);
			break;
		case KEY_BLUETOOTH:
			rfkill_schedule_toggle(RFKILL_TYPE_BLUETOOTH);
			break;
		case KEY_RFKILL:
			rfkill_schedule_toggle(RFKILL_TYPE_ALL);
			break;
		}
    }
	spin_unlock_irqrestore(&rfkill_op_lock, flags);    
}

static void rfkill_schedule_toggle(enum rfkill_type type)
{
	if (!rfkill_op_pending) {
		__set_bit(type, rfkill_sw_pending);
		__change_bit(type, rfkill_sw_state);
		rfkill_schedule_ratelimited();
    }
}

static void rfkill_schedule_ratelimited(void)
{
	if (schedule_delayed_work(&rfkill_op_work,
				  rfkill_ratelimit(rfkill_last_scheduled)))
		rfkill_last_scheduled = jiffies;
}

static DECLARE_DELAYED_WORK(rfkill_op_work, rfkill_op_handler);

static void rfkill_op_handler(struct work_struct *work)
{
	do {
		if (rfkill_op_pending) {
			__rfkill_handle_global_op(op);
        }

		for (i = 0; i < NUM_RFKILL_TYPES; i++) {
			if (__test_and_clear_bit(i, rfkill_sw_pending)) {
				__rfkill_handle_normal_op(i, c);
            }
        }        
    } while (rfkill_op_pending);
}

static void __rfkill_handle_normal_op(const enum rfkill_type type,
				      const bool complement)
{
	bool blocked;

	rfkill_switch_all(type, blocked);    
}

void rfkill_switch_all(enum rfkill_type type, bool blocked)
{
	if (!rfkill_epo_lock_active)
		__rfkill_switch_all(type, blocked);
}

static void __rfkill_switch_all(const enum rfkill_type type, bool blocked)
{
	rfkill_update_global_state(type, blocked);

	list_for_each_entry(rfkill, &rfkill_list, node) {
		if (rfkill->type != type && type != RFKILL_TYPE_ALL)
			continue;

		rfkill_set_block(rfkill, blocked);
	}    
}


// 汇编指令
static __always_inline void __set_bit(long nr, volatile unsigned long *addr)
{
	asm volatile(__ASM_SIZE(bts) " %1,%0" : : ADDR, "Ir" (nr) : "memory");
}


```












``` c
static void rfkill_set_block(struct rfkill *rfkill, bool blocked)
{
	err = rfkill->ops->set_block(rfkill->data, blocked);

	if (prev != curr)
		rfkill_event(rfkill);    
}

static void rfkill_event(struct rfkill *rfkill)
{
	if (!rfkill->registered)
		return;

	kobject_uevent(&rfkill->dev.kobj, KOBJ_CHANGE);

	/* also send event to /dev/rfkill */
	rfkill_send_events(rfkill, RFKILL_OP_CHANGE);
}
```










``` c
int __must_check rfkill_register(struct rfkill *rfkill)
{
	INIT_WORK(&rfkill->uevent_work, rfkill_uevent_work);
}


bool rfkill_set_hw_state(struct rfkill *rfkill, bool blocked)
{
	if (rfkill->registered && prev != blocked)
		schedule_work(&rfkill->uevent_work);
}

bool rfkill_set_sw_state(struct rfkill *rfkill, bool blocked)
{
	if (prev != blocked && !hwblock)
		schedule_work(&rfkill->uevent_work);
}

static void rfkill_uevent_work(struct work_struct *work)
{
	rfkill_event(rfkill);
}


static void rfkill_event(struct rfkill *rfkill)
{
	kobject_uevent(&rfkill->dev.kobj, KOBJ_CHANGE);

	/* also send event to /dev/rfkill */
	rfkill_send_events(rfkill, RFKILL_OP_CHANGE);    
}


int kobject_uevent(struct kobject *kobj, enum kobject_action action)
{
	return kobject_uevent_env(kobj, action, NULL);
}

static void rfkill_send_events(struct rfkill *rfkill, enum rfkill_operation op)
{
	list_for_each_entry(data, &rfkill_fds, list) {
		ev = kzalloc(sizeof(*ev), GFP_KERNEL);
    }
}


```