package main

import (
	"log"
	"time"
)

func timestamp() {
	t := time.Now().Unix()
	log.Print(t)
}

func main() {
	timestamp()
}
