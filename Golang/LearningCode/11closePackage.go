package main

import (
	"fmt"
)

func a() func() int {
	i := 0
	b := func() int {
		i++
		fmt.Println(i)
		return i
	}
	return b
}

func test01(base int) (func(int) int, func(int) int) {
	add := func(i int) int {
		base += i
		return base
	}

	sub := func(i int) int {
		base -= i
		return base
	}
	return add, sub
}

func main() {
	c := a()
	c()

	fmt.Println("************")
	f1, f2 := test01(10)
	fmt.Printf("%d %d\n", f1(1), f2(2))
	fmt.Printf("%d %d\n", f1(3), f2(4))
}
