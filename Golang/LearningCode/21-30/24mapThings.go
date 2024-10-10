package main

import "fmt"

func main() {
	var m map[string]string = make(map[string]string, 0)
	m["1"] = "1"
	fmt.Println(m["1"])
}
