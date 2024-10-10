package main

import (
	"fmt"
	"unsafe"
)

func main() {
	str := "Hello, World!"

	strPtr := unsafe.Pointer(&str)
	byteSlice := *(*[]byte)(strPtr)

	fmt.Println(byteSlice)

	testNilSlice()
}

func testNilSlice() {
	var s []int
	var a = make([]int, 0)

	if s == nil {
		fmt.Println("yes")
	}

	if a == nil {
		fmt.Println("no")
	}

}
