package main

import (
	"fmt"
)

var (
	num int = 3
)

func main() {
	switch { // 只会满足一个 最前面的 之后自动退出
	case num > 0:
		fmt.Println("1")
		fallthrough
	case num < 0:
		fmt.Println("2")
	case num > 0:
		fmt.Println("3")
	}
}
