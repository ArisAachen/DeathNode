package main

import (
	"context"
	"log"
	"time"
)

func main() {
	contextTest()
}

func contextTest() {
	ctx := context.Background()
	ctx, cancel := context.WithCancel(ctx)

	go func() {
		for {
			select {
			case <-ctx.Done():
				log.Print("cancel")
			}
		}
	}()

	cancel()

	time.Sleep(5*time.Second)
}
