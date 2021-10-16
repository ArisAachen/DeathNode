package main

import (
	"github.com/godbus/dbus"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

func main() {
	busCall()
}

func dbusProtocol() {
	members := os.Getenv("DBUS_SESSION_BUS_ADDRESS")
	if members == "" {
		log.Fatalln("env error")
	}
	memSl := strings.Split(members, "=")
	if len(memSl) < 2 {
		log.Fatalln("count error")
	}
	addr := net.UnixAddr{
		Name: memSl[1],
		Net:  "unix",
	}
	conn, err := net.DialUnix("unix", nil, &addr)
	if err != nil {
		log.Fatalf("dial failed, err: %v", err)
	}
	go cycle(conn)
	_, err = conn.Write([]byte{0})
	if err != nil {
		log.Fatalf("write null failed, err: %v", err)
	}

	_, err = conn.Write([]byte("AUTH\r\n"))
	if err != nil {
		log.Fatalf("write auth failed, err: %v", err)
	}


	time.Sleep(10 * time.Hour)
}

func cycle(conn net.Conn) {
	if conn == nil {
		log.Fatalln("nil")
	}
	buf := make([]byte, 512)
	_, err := conn.Read(buf)
	if err != nil {
		log.Fatalf("read failed, err: %v", err)
	}

	log.Printf("msg is %v\n", string(buf))
}

func busCall() {
	bus, err := dbus.SystemBus()
	if err != nil {
		log.Fatalln(err)
	}
	obj := bus.Object("org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager")
	call := obj.Call("org.freedesktop.NetworkManager.GetAllDevices", 0)
	log.Println(call.Body[0])
}
