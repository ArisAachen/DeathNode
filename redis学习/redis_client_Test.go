package main

import (
	"context"
	"flag"
	"github.com/go-redis/redis"
	"log"
)

func init() {

}

type goods struct {
	user string
	id   string
}

func main() {
	var test goods

	// parse goods
	flag.StringVar(&test.user, "user name", "", "input user name")
	flag.StringVar(&test.id, "good id", "", "good id")

	flag.Parse()

	_ = MSRedis(test.user, test.id)
}

var ctx = context.Background()

func MSRedis(user string, id string) error {
	// check
	if user == "" || id == "" {
		log.Fatalf("invalid params, user %v, id %v \n", user, id)
	}

	client := redis.NewClient(&redis.Options{
		Network: "tcp",
		Addr:    "127.0.0.1:6379",
	})

	left, err := client.Get(ctx, "goods:id").Int()
	if err != nil {
		log.Printf("get last failed, err: %v \n", err)
		return err
	}

	// check left
	if left <= 0 {
		log.Println("good left is 0 ")
		return nil
	}

	log.Printf("left good is %v \n", left)

	// check if user is already in list
	exit, err := client.SIsMember(ctx, "user:ms", &user).Result()
	if err != nil {
		log.Printf("check is member failed, err: %v", err)
		return err
	}
	if exit {
		log.Printf("user %v already in list \n", user)
		return nil
	}

	// add to set
	_, err = client.SAdd(ctx, "user:ms", &user).Result()
	if err != nil {
		log.Printf("add user %v to set failed, err: %v \n", user, err)
		return err
	}

	// decr good num
	_, err = client.Decr(ctx, "goods:id").Result()
	if err != nil {
		log.Printf("decr good failed, err: %v \n", err)
		return err
	}

	return nil
}
