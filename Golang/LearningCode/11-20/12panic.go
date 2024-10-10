package main

import "fmt"

func test01() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Println(err.(string))
		}
	}()
	panic("this is panic")
}

func Try(fun func(), handler func(interface{})) {
	defer func() {
		if err := recover(); err != nil {
			handler(err)
		}
	}()
	fun()
}

func main() {
	test01()
	Try(func() {
		panic("this is panic two")
	}, func(err interface{}) {
		fmt.Println(err)
	})
}
