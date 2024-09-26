package main

import (
	"fmt"
	"time"
)

func main() {
	Start := time.Now()
	var tmpChar string
	fmt.Scanln(&tmpChar)
	End := time.Now()
	fmt.Println(End.Sub(Start))

}
