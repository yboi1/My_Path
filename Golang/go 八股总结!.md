## go 八股总结!

#### No1 GC垃圾回收机制

> 1.首先把所有对象放入到白色集合
>
> 2.从根节点开始遍历对象, 把遍历到的对象放入到灰色集合中



- #### 连nil切片和空切片一不一样都不清楚？那BAT面试官只好让你回去等通知了。

> 1. nil 切片 底层的ptr指针是nil 	空切片的底层ptr指针指向数组地址
>
> ```
> nil切片: var s = []string	// 不会自动分配内存
> 空切片: 	var s = []string{}
> 				var s = make([]string, 0)
> ```
>
> 2. encoding 时编码出的结果不同	
>
>     nil : null  空切片: []
>
> 3. 当需要判断空切皮时 不应该判断其是否为nil 因为它可能返回的是空切片 而不是nil切片, 可以通过判断len来避免两者之间的差异, 或者返回函数直接返回nil 而不是返回空切片



- #### 字符串转成byte数组，会发生内存拷贝吗？

> 标准转换为: []byte(str), 标准的转换方法都会发生内存拷贝，所以为了减少内存拷贝和内存申请我们可以使用强转换的方式对两者进行转换, 强转换使用了unsafe.ptr



- #### 翻转含有中文、数字、英文字母的字符串

> rune 定义为int32 比byte表示的字符范围更大, 因此可以转换为rune类型然后进行反转

```go
package main

import"fmt"

func main() {
 src := "你好abc啊哈哈"
 dst := reverse([]rune(src))
 fmt.Printf("%v\n", string(dst))
}

func reverse(s []rune) []rune {
 for i, j := 0, len(s)-1; i < j; i, j = i+1, j-1 {
  s[i], s[j] = s[j], s[i]
 }
 return s
}
```



- #### 拷贝大切片一定比小切片代价大吗？

> ```
> type SliceHeader struct {
> 	Data uintptr
> 	Len  int
> 	Cap  int
> }
> ```
>
> 切片底层实现, 发生拷贝时, 拷贝的大小相同



- #### map不初始化使用会怎么样

> 可以对未初始化的map取值, 但是取出来的值为空
>
> 不可以对未初始化的map赋值, 会出现报错 panic: assignment to entry in nil map



- map不初始化长度和初始化长度的区别
- map承载多大，大了怎么办
- map的iterator是否安全？能不能一边delete一边遍历？
- 字符串不能改，那转成数组能改吗，怎么改
- 怎么判断一个数组是否已经排序
- 普通map如何不用锁解决协程安全问题
- array和slice的区别
- [golang面试题：json包变量不加tag会怎么样？](https://link.segmentfault.com/?enc=zxrKat9c241ywoH5VNe4Dw%3D%3D.WPU2kr9DFZZluisM2FgPZji1lab2Jihtk%2F98tc4R6JfBCEhqrZHZ1VfHUpbGDPbYRo79kZJXYkmxtL1wf5qNLA%3D%3D)
- 零切片、空切片、nil切片是什么
- slice深拷贝和浅拷贝
- map触发扩容的时机，满足什么条件时扩容？
- map扩容策略是什么
- 自定义类型切片转字节切片和字节切片转回自动以类型切片
- make和new什么区别
- slice ，map，chanel创建的时候的几个参数什么含义
- 线程安全的map怎么实现