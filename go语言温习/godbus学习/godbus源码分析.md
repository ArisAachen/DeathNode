``` go
type ImplObject struct { 

}

// 存放所有 dbus 名 
var globalRuleCounter = &ruleCounter{
	connRuleCount: make(map[string]map[string]uint),
}

```

``` go
func (v *interfaceSettings) ConnectNewConnection(cb func(connection dbus.ObjectPath)) (dbusutil.SignalHandlerId, error) {

	return obj.ConnectSignal_(rule, sigRule, handlerFunc)    
}

func (o *ImplObject) ConnectSignal_(rule string, sigRule *dbusutil.SignalRule, cb dbusutil.SignalHandlerFunc) (dbusutil.SignalHandlerId, error) { 
	// 将
	return o.connectSignal(rule, sigRule, cb)    
}

func (o *ImplObject) connectSignal(rule string, sigRule *dbusutil.SignalRule, cb dbusutil.SignalHandlerFunc) (dbusutil.SignalHandlerId, error) { 
	if o.ruleAuto {
		// sigRule是 包含 Path Name 的结构体
		/*
		 *  	sigRule := &dbusutil.SignalRule{
		 *			Path: obj.Path_(),
		 *			Name: v.GetInterfaceName_() + ".NewConnection",
		 *		}
		 */
		// 此处将 “rule“ 添加进 [:1.21] "sig='',path=''" 加入 globalRuleCounter
		err := o.addMatch(rule)		
		 // 添加进loop 
		handlerId := o.sigLoop.AddHandler(sigRule, cb)
		// 本地handler 包含 ruleMap["sig='' path=''"] = id
		o.addRuleHandlerId(rule, handlerId)		
	}
}

func (sl *SignalLoop) AddHandler(rule *SignalRule, cb SignalHandlerFunc) SignalHandlerId { 
	// 添加进handler
	sl.handlers[id] = SignalHandler{
		// 结构体对象
		rule: rule,
		// 回调函数
		cb:   cb,
	}	
}

```



``` go
// 	connRuleCount map[string]map[string]uint map[dbus名][rule "path signal interface"] 
func (rc *ruleCounter) addMatch(conn *dbus.Conn, rule string) error { 
    // 获取 ":1.21" 
	name := getConnName(conn)
    // 添加
	ruleCount, ok := rc.connRuleCount[name]   
	if count == 0 {
		// 
		err := conn.BusObject().Call("org.freedesktop.DBus.AddMatch", 0, rule).Err
	}
	// 把rule 放进每个 [name]  :1.21["sig="]
	ruleCount[rule] = count + 1
}

```


``` go
// 保存 session或system dest 和 interface
func (conn *Conn) Object(dest string, path ObjectPath) BusObject {
	return &Object{conn, dest, path}
}
```


``` go
func (sl *SignalLoop) Start() { 
	// 
	ch := make(chan *dbus.Signal, sl.bufSize)	
	// 
	sl.conn.Signal(ch)

}

// 添加channel
func (conn *Conn) Signal(ch chan<- *Signal) {
	// 本地的handler [:1.1.0]
	handler, ok := conn.signalHandler.(SignalRegistrar)
	// 添加进handler
	handler.AddSignal(ch)	
}

func (sh *defaultSignalHandler) AddSignal(ch chan<- *Signal) { 
	sh.signals = append(sh.signals, &signalChannelData{
		ch:   ch,
		done: make(chan struct{}),
	})	
}
```


## dbus-call
``` go
func (o *Object) Call(method string, flags Flags, args ...interface{}) *Call { 
	// 此处等待 create call完成Done 也就是如果需要返回函数 此处阻塞了
	return <-o.createCall(context.Background(), method, flags, make(chan *Call, 1), args...).Done
}


func (o *Object) createCall(ctx context.Context, method string, flags Flags, ch chan *Call, args ...interface{}) *Call { 
	// 此处根据最后一个 "org.freedesktop.NetworkManager.AddAndActivateConnection()"
	// 得到 iface 和 method 字符串
	i := strings.LastIndex(method, ".")	
			iface = method[:i]
	method = method[i+1:]
	
	// 构造message结构体
	msg := new(Message)
	// 指定头为 method_call 1 
	msg.Type = TypeMethodCall	
	// 构造header
	msg.Headers = make(map[HeaderField]Variant)
	msg.Flags = flags & (FlagNoAutoStart | FlagNoReplyExpected)	
	msg.Headers[FieldPath] = MakeVariant(o.path)             // path
	msg.Headers[FieldDestination] = MakeVariant(o.dest)	     // dest
	msg.Headers[FieldInterface] = MakeVariant(iface)         // iface
	msg.Headers[FieldMember] = MakeVariant(method)           // method
	msg.Body = args                                          // body
	if len(args) > 0 { 
		// 获取签名  "a{ax}"
		msg.Headers[FieldSignature] = MakeVariant(SignatureOf(args...))		
	}	
	
	return o.conn.SendWithContext(ctx, msg, ch)	
}

// 
func (conn *Conn) SendWithContext(ctx context.Context, msg *Message, ch chan *Call) *Call { 
	return conn.send(ctx, msg, ch)	
}

func (conn *Conn) send(ctx context.Context, msg *Message, ch chan *Call) *Call { 
	// 构造cancel context, ctx 一般是 background
	ctx, canceler := context.WithCancel(ctx)	

	// 此处是方法调用  且需要返回值
	if msg.Type == TypeMethodCall && msg.Flags&FlagNoReplyExpected == 0 { 
		// 保存当前调用的方法 和 接口
		// 通过 call 返回给 createCall，等待 Done
		// 而接到 reply 后对比 serial 找到调用的方法， 检查是否方法是否一致， 再返回
		call = new(Call)
		call.Destination, _ = msg.Headers[FieldDestination].value.(string)
		call.Method = iface + "." + member
		//  createCall返回的 call 里面等到Done
		call.Done = ch
		call.ctx = ctx
		call.ctxCanceler = canceler
		// 保存序号， reply的是否寻找 serial
		conn.calls.track(msg.serial, call)		
		conn.sendMessageAndIfClosed(msg, func() {
			
		}		
	} else {
		// 
		call = &Call{Err: nil, Done: ch}		
	}
}

func (conn *Conn) sendMessageAndIfClosed(msg *Message, ifClosed func()) { 
	// 此处调用 unixTransport.SendMessage 最后调用 msg.EncodeTo(t, nativeEndian)	t 是 unixTransport
	err := conn.outHandler.sendAndIfClosed(msg, ifClosed)	
}

func (h *outputHandler) sendAndIfClosed(msg *Message, ifClosed func()) error { 
	// 查看是否被关闭 
	if h.closed.isClosed { 
		if ifClosed != nil { 
			ifClosed()			
		}
		return nil		
	}	
	// 此处调用 unixTransport.SendMessage 最后调用 msg.EncodeTo(t, nativeEndian)	t 是 unixTransport	
	return h.conn.SendMessage(msg)	
}

func (msg *Message) EncodeToWithFDs(out io.Writer, order binary.ByteOrder) (fds []int, err error) { 
	// buf.WriteTo(unixTransport.*net.UnixConn.Write()）
	if _, err := buf.WriteTo(out); err != nil { 

	}	
	return enc.fds, nil
}


func SignatureOf(vs ...interface{}) Signature {
	var s string
	for _, v := range vs {
		s += getSignature(reflect.TypeOf(v), &depthCounter{})
	}
	return Signature{s}
}


func getSignature(t reflect.Type, depth *depthCounter) (sig string) { 

}
```


## dbus go
``` go


// 此处保存了 call是一个 Channel, 用于等待函数返回, 
func (o *Object) Go(method string, flags Flags, ch chan *Call, args ...interface{}) *Call {
	return o.createCall(context.Background(), method, flags, ch, args...)
}

// 这个函数主要用于函数调用超时判断 是在 ctx 
// 可以在外面传入 ctx， 然后定时器设置超时 cancel 
// 在 sender 函数 设置了 ctx.Done 接受 cancel 返回超时 给 handler
func (o *Object) GoWithContext(ctx context.Context, method string, flags Flags, ch chan *Call, args ...interface{}) *Call {
	return o.createCall(ctx, method, flags, ch, args...)
}
```



## dbus bus 
``` go
func SessionBus() (conn *Conn, err error) { 
	// 此处获取 环境变量 D
	conn, err = ConnectSessionBus()
	return	
}

// 连接到unix socket
func ConnectSessionBus(opts ...ConnOption) (*Conn, error) {
	// 根据环境变量获取 unix socket 地址 DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
	address, err := getSessionBusAddress()	

	return Connect(address, opts...)	
}

func Connect(address string, opts ...ConnOption) (*Conn, error) {
	// unix socket 连接 unix server
	conn, err := Dial(address, opts...)
}	


func Dial(address string, opts ...ConnOption) (*Conn, error) { 
	// 此处 dial unix path
	tr, err := getTransport(address)
	return newConn(tr, opts...)	
}


func getTransport(address string) (transport, error) { 
	// 多个 path
	addresses := strings.Split(address, ";")
	for _, v := range addresses {	
		// 此处根据 unix 获取 transports["unix"]    	transports["unix"] = newUnixTransport		
		f := transports[v[:i]]	
		// 调用 newUnixTransport("/run/user/1000/bus")
		t, err = f(v[i+1:])		
	}
}

func newUnixTransport(keys string) (transport, error) { 
	// 获取 ab
	abstract := getKey(keys, "abstract")	
	// 获取 unix path路径
	path := getKey(keys, "path")
	switch { 
	case abstract == "" && path != "": 
		// dial unix socket
		t.UnixConn, err = net.DialUnix("unix", nil, &net.UnixAddr{Name: path, Net: "unix"})			
	}		
}


func newConn(tr transport, opts ...ConnOption) (*Conn, error) { 
	// 保存 conn 用于给 unix socket 发送消息
	conn.transport = tr

	// 此处保存handler, handdler保存了一个 objects(map["/org/freedesktop/NetworkManager/Device/1"] (["org.freedesktop.NetworkManager.Device.wirelss"]methods))
	// 将会在export导出处被使用
	if conn.handler == nil {
		conn.handler = NewDefaultHandler()
	}
	
	// 此处讲conn保存到 busObj中，并 记录 dest 和 path, 此处应该保存的是默认值， 后续可以通过Object覆盖
	conn.busObj = conn.Object("org.freedesktop.DBus", "/org/freedesktop/DBus")

	// 返回一个conn
	return conn, nil	
}
```


## dbus auth
``` go
func (conn *Conn) Auth(methods []Auth) error { 
	// 发送0字节，确定连接是否存在 unix 可以如此做
	err := conn.transport.SendNullByte()	
	// 发送unix消息 auth
	err = authWriteLine(conn.transport, []byte("AUTH"))
	// 行读取
	s, err := authReadLine(in)	
	// 根据协议 此时服务端必须返回 rejected, 并列出所以支持的协议
	if len(s) < 2 || !bytes.Equal(s[0], []byte("REJECTED")) {}

	for _, v := range s {
		for _, m := range methods { 
			// 开启各种认证，直到收到OK，再发送BEGIN，则此时说明认证通过
			err = authWriteLine(conn.transport, []byte("BEGIN"))	
			// 	开始接受服务端的消息
			go conn.inWorker()
		}	
	}
}

```


## dbus read message

``` go
func (conn *Conn) inWorker() { 
	sequenceGen := newSequenceGenerator()
	for { 
		// 按照dbus协议读取msg
		msg, err := conn.ReadMessage()		
		// 查看当前 的目标是否为广播  或者 是自己
		dest, _ := msg.Headers[FieldDestination].value.(string)
		found := dest == "" ||
			!conn.names.uniqueNameIsKnown() ||
			conn.names.isKnownName(dest)
		if !found {
			continue
		}		
		switch msg.Type {	
			// 处理 error， 类似于 	handleReply
		case TypeError:
			// 此处是别处方法，由于此处调用了方法，进行的返回
		case TypeMethodReply:	
			conn.serialGen.RetireSerial(conn.calls.handleReply(sequence, msg))			
		case TypeSignal:	
		case TypeMethodCall:
			// 此处是别处调用了此接口的方法
			go conn.handleCall(msg)									
		}
	}	
}


func (t *unixTransport) ReadMessage() (*Message, error) { 
	// 读取子节流
	if _, err := io.ReadFull(t.rdr, csheader[:]); err != nil {}	
	// 根据协议，第一个字段是大小端
	switch csheader[0] {
	case 'l':
		order = binary.LittleEndian
	case 'B':
		order = binary.BigEndian
	default:
		return nil, InvalidMessageError("invalid byte order")
	}	

	// 读取 4 -8 为字节长度
	binary.Read(bytes.NewBuffer(csheader[4:8]), order, &blen)
	// 12 - 16 是 array header 的长度
	binary.Read(bytes.NewBuffer(csheader[12:]), order, &hlen)	

	// 此处靠背 消息标识
	copy(headerdata, csheader[12:])	
	// 由于标识占4位, 所以从第4位开始读取   根据dbus协议  读取的消息必须是8位对齐  a(yv) 格式
	if _, err := io.ReadFull(t.rdr, headerdata[4:]); err != nil {	}


}
```


## dbus call
``` go
func (conn *Conn) handleCall(msg *Message) { 
	// 获取被调用的方法
	name := msg.Headers[FieldMember].value.(string)
	path := msg.Headers[FieldPath].value.(ObjectPath)
	ifaceName, _ := msg.Headers[FieldInterface].value.(string)
	sender, hasSender := msg.Headers[FieldSender].value.(string)	

	// 寻找 method 
	m, exists := iface.LookupMethod(name)
	// 解析参数
	args, err := conn.decodeArguments(m, sender, msg)
	// 根据method字符串，在之前保存输出的字符串[reflect.Value]的方法调用方法
	ret, err := m.Call(args...)	
	// err
	if err != nil { 
		conn.sendError(err, sender, serial)		
	}		
	// 需要返回值
	if msg.Flags&FlagNoReplyExpected == 0 {	
		// 返回的参数	
		for i := 0; i < len(ret); i++ {
			reply.Body[i] = ret[i]
		}
		// 消息序号
		reply.Headers[FieldReplySerial] = MakeVariant(msg.serial)		
		// 函数签名
		reply.Headers[FieldSignature] = MakeVariant(SignatureOf(reply.Body...))
		// 发送回复
		conn.sendMessageAndIfClosed(reply, nil)		
	}
}

```


## dbus handle reply
``` go
func (conn *Conn) inWorker() { 
	sequenceGen := newSequenceGenerator()
	for {
		// 方法回调
		// 此处处理是将 serial 对应的 Call(存放了之前的调用方法) 删除
		// 并且把 body返回值 设置给 call，再 调用 done 这样就返回给了 createCall.Done
		case TypeMethodReply:
			conn.serialGen.RetireSerial(conn.calls.handleReply(sequence, msg))		
	}
}

// 处理回复
func (tracker *callTracker) handleReply(sequence Sequence, msg *Message) uint32 { 
	// 获取当前的 序号
	serial := msg.Headers[FieldReplySerial].value.(uint32)
	// 看看当前是否存在这个方法
	_, ok := tracker.calls[serial]

	if ok { 
		// 把msg.Body 返回值 传给当前的方法
		tracker.finalizeWithBody(serial, sequence, msg.Body)		
	}	

}

// 处理回复
func (tracker *callTracker) finalizeWithBody(sn uint32, sequence Sequence, body []interface{}) { 
	if ok {
		c.Body = body
		c.ResponseSequence = sequence
		c.done()
	}
}
```



## decode
``` go
func (dec *decoder) Decode(sig Signature) (vs []interface{}, err error) { 

}

func DecodeMessage(rd io.Reader) (msg *Message, err error) { 

}
```



## dbus export
export 主要用于保存当前的["dbus-path"]["dbus-interface"]["dbus-method"]reflect.method 
将路径  接口  方法 字符串绑定到 reflect函数,其中保存了函数的地址

``` go
func (conn *Conn) Export(v interface{}, path ObjectPath, iface string) error { 
	return conn.ExportWithMap(v, nil, path, iface)
}

func (conn *Conn) ExportWithMap(v interface{}, mapping map[string]string, path ObjectPath, iface string) error { 
	return conn.export(getMethods(v, mapping), path, iface, false)	
}

func getMethods(in interface{}, mapping map[string]string) map[string]reflect.Value { 
	// 使用reflect获取所有方法，包外获取的一般是大写
	typ := val.Type()	
	for i := 0; i < typ.NumMethod(); i++ {	 
		// 此处保存了 方法名 和 调用名的 map， 后续通过 name 找到 方法 进行调用
	}
}

// 导出方法
func (conn *Conn) export(methods map[string]reflect.Value, path ObjectPath, iface string, includeSubtree bool) error { 
	// 此处获取每个conn对应的handler  handler中存放这 map[dbus-path]map[dbus-interface]map[dbus-method]reflect.value(存放这函数定位)
	h, ok := conn.handler.(*defaultHandler)
	if !h.PathExists(path) {
		// 如果 [dbus-path]nil， 则创建
		h.AddObject(path, newExportedObject())
	}

	// 此处再次封装了一次 reflect.value method
	exportedMethods := make(map[string]Method)
	for name, method := range methods {
		exportedMethods[name] = exportedMethod{method}
	}

	// 此处存放[dbus-interface]map[dbus-method]reflect.value(存放这函数定位)
	obj := h.objects[path]
	obj.AddInterface(iface, newExportedIntf(exportedMethods, includeSubtree))
}

func (h *defaultHandler) AddObject(path ObjectPath, object *exportedObj) { 
	h.objects[path] = object	
}

```





## dbus requestname

``` c
func (conn *Conn) RequestName(name string, flags RequestNameFlags) (RequestNameReply, error) { 
	err := conn.busObj.Call("org.freedesktop.DBus.RequestName", 0, name, flags).Store(&r)	
}

```