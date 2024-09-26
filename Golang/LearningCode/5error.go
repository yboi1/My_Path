package main

import (
	"fmt"
	"strconv"
)

var (
	an  int
	err error
)

func main() {
	var orig string = "ABC"
	// var an int
	var newS string
	// var err error

	fmt.Printf("The size of ints is: %d\n", strconv.IntSize)
	// anInt, err = strconv.Atoi(origStr)

	if an, err := strconv.Atoi(orig); err != nil {
		fmt.Printf("orig %s is not an integer - exiting with error\n", orig)
		return
	} else {
		fmt.Printf("The integer is %d\n", an)
		an = an + 5
		newS = strconv.Itoa(an)
		fmt.Printf("The new string is: %s\n", newS)
	}
}
