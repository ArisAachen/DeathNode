package main

import (
	"flag"
	"fmt"
	"strconv"
	"strings"
	"time"
)

type Self []int

func (s *Self) String() string {
	return fmt.Sprint(*s)
}

func (s *Self) Set(param string) error {
	// split with space   1 2 3
	sl := strings.Split(param, ",")
	// set default value
	if len(sl) == 0 {
		*s = make([]int, 0)
		*s = append(*s, 0, 0, 0, 0, 0)
	}
	// convert num string to int
	for _, value := range sl {
		num, err := strconv.Atoi(value)
		if err != nil {
			return fmt.Errorf("%s is not a number", value)
		}
		*s = append(*s, num)
	}
	// none error
	return nil
}

func parse() {
	var num int
	var msg string
	var second time.Duration
	var self Self

	// flags
	flag.IntVar(&num, "number", 0, "show number")
	flag.StringVar(&msg, "message", "", "show message")
	flag.DurationVar(&second, "duration", 0, "time duration")
	flag.Var(&self, "array", "self define array")

	// must parse
	flag.Parse()

	// print
	fmt.Printf("self is %v \n", self)
}

func parseSet() {
	var self Self

	set := flag.NewFlagSet("self_program", flag.ContinueOnError)
	set.Var(&self, "array", "self define array")

	err := set.Parse([]string{"--array", "1,2,3,4,abc"})
	if err != nil {
		fmt.Printf("parse failed, err: %v \n", err)
	}
	return
}
