package main

import "fmt"

func loopt() {
	i := 0
loop:
	if i < 15 {
		fmt.Printf("%d ", i)
		i++
		goto loop
	}
}

func fizzbuzz() {
	for i := 1; i <= 100; i++ {
		switch {
		case i%15 == 0:
			fmt.Println("FizzBuzz ", i)
		case i%3 == 0:
			fmt.Println("Fizz ", i)
		case i%5 == 0:
			fmt.Println("Buzz ", i)

		}

	}
}

func main() {
	for i := 0; i < 5; i++ {
		var v int
		fmt.Printf("%d ", v)
		v = 5
	}
}
