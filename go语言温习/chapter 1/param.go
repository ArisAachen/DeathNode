package main

import (
	"log"
	"os"
)

func main() {
	// print all params,
	// the first param is program name
	for index := 0; index < len(os.Args); index++ {
		log.Println(os.Args[index])
	}
}
