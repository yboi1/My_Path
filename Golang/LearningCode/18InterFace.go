package main

import (
	"fmt"
)

type Animal interface {
	run()
}

type Cat struct {
	name string
	age  int
}

type Dog struct {
	name string
	age  int
}

func (c Cat) run() {
	fmt.Printf("Cat %s is Running\n", c.name)
}

func (d Dog) run() {
	fmt.Printf("Dog %s is Running\n", d.name)
}

func main() {
	cat := &Cat{"mimi", 10}
	dog := &Dog{"wangcai", 5}

	cat.run()
	dog.run()
}
