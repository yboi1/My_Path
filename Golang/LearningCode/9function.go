package main

import (
	"fmt"
)

var (
	a, b int
)

func add(a int, b int) int {
	return a + b
}

func sub(a int, b int) int {
	return a - b
}

func mul(a int, b int) int {
	return a * b
}

func dev(a int, b int) int {
	return a / b
}

func main() {
	a = 10
	b = 10
	fmt.Println(add(a, b))
	fmt.Println(sub(a, b))
	fmt.Println(mul(a, b))
	fmt.Println(dev(a, b))
}
