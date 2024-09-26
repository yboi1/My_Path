package main

import (
	"fmt"
	"log"
	"runtime"
)

func add(a, b int) {
	fmt.Println(a + b)
}

func callback(c int, f func(int, int)) {
	f(c, 2)
}

func f() (ret int) {
	defer func() {
		ret++
	}()
	return 1
}

func main() {
	callback(2, add)
	fmt.Println(f())

	where := func() {
		_, file, line, _ := runtime.Caller(1)
		log.Printf("%s:%d", file, line)
	}
	// var where = log.Print
	where()
	// some code
	where()
	// some more code
	where()

}
