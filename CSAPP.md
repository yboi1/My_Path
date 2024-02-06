







## 计算机中的抽象



### 指令集架构（ISA）

> 定义了机器级程序的格式和行为，定义了处理器状态，指令的格式，以及每条指令对状态的影响。

### 虚拟地址

> 提供的内存模型看上去是一个非常大的字节数组（页表）

### 存储器系统

`存储器系统的实现是将多个硬件存储器和操作系统软件结合起来` （第九章）



# 第三章、程序的机器级表示

## 汇编指令

```
movb movw movl movq		--一个byte是两个字节
```

```
vmovss	X	M32		传送单精度数		X(寄存器)	M32(内存)
vmovss	M32	X		传送单精度数
vmovsd	M64	X		传送双精度数
vmovsd	X	M64		传送双精度数

vmovaps X	X		传送封装好的单精度数
vmovapd X	X		传送封装好的双精度数
```

move的常见错误：

> （内存引用的寄存器是四字的，两个操作数不能都是内存引用）



```
leaq	S,D		D<-&S	加载数据
```

```
INC		D		+1
DEC		D		-1
NEG		D		取负
NOT		D		取反
```

```
ADD		S,D		D=D+S
SUB		S,D		-
IMUL	S,D		*
XOR		S,D		异或（^）
OR		S,D		|
AND		S,D		&
```

`浮点数`

```
vaddss	vaddsd	+
vsubss	vsubsd	-
vmulss	vmulsd	*
vdivss	vdivsd	/
vmaxss	vmaxsd	max
vminss	vminsd	min
sqrtss	sqrtsd	开根号

vxorps	vorpd	位级异或
vandps	andpd	位级与

ucomiss S1, S2		S2-S1		比较单精度
ucomisd	S1, S2		S1-S2		比较双精度

条件码：
		CF(进位标志位)	ZF(零标志位)	PF(奇偶标志位)
S2>S1	0			   0			  0
S2=S1	0			   1			  0
S2<S1	1			   0			  0
```



`算数移位时会加上符号位`	`>>a(算数)	>>l(逻辑)`

```
SAL		k,D		算数左移
SHL		k,D		逻辑左移
SAR		k,D		算数右移
SHR		k,D		逻辑右移
```



```
imulq	S	有符号乘法
mulq	S	无符号乘法
```

```
clto		高位扩展
```

```
idivq	S	有符号除法
divq	S	无符号除法
```



`set`

```
sete	D	相等
setne	D	不相等

sets	D	负数
setns	D	非负数

setg	D	大于
setge	D	大于等于
setl	D	小于
setle	D	小于等于

seta	D	超过
setae	D	超过等于
setb	D	低于
setbe	D	低于等于
```



`跳转指令`

```
testq	%rdi, %rdi	//%rdi != 0
jne	.L3
```



## c语言，汇编，机器代码之间的关系

 	c 预处理器扩展源代码，插入所有的调用文件，扩展#define 声明的宏。然后编译器将源文件产生为汇编代码，接下来汇编器将汇编代码转换为二进制的目标代码，但是此时还未填入全局值的地址。最后链接器将目标代码与库函数的代码合并，产生最后的可执行文件

> 1、扩展源代码，插入文件，扩展宏
>
> 2、编译器编译源代码为汇编代码
>
> 3、汇编器将汇编代码转换为目标代码
>
> 4、链接器将目标代码与库函数合并

## 3.2 程序编码

### 3.2.1 机器级代码

#### 寄存器

> 规律：	r开头的为8字	e开头的为4字	无开头的为2字	以l结尾的为1字

> 程序计数器：PC	%rip
>
> 整数寄存器文件：	包含16个命名的位置，分别存储64位的值	可以记录程序状态，保存临时数据（例如函数参数，局部变量，返回值）	R开头
>
> 条件码寄存器：保存最近执行的算数或者逻辑指令的状态信息	用来实现控制或者数据流中的条件变化，如`if`和`while`语句
>
> 一组向量寄存器：存放一个或多个整数或浮点数的值
>
> 通用目的存储器：（16个存储64位值）存储整数数据和指针	以E开头

#### 程序内存

> 程序可执行机器代码，操作系统需要的信息，用于管理过程调用和返回的运行时栈，以及用户分配的内存块（malloc）



#### 转换为汇编代码

```c
long mult2(long, long);

void multstore(long x, long y, long *dest){
    long t = mult2(x, y);
    *dest = t;
}
```

`gcc -Og -c `

```
	pushq	%rbx
	movq	%rdx, %rbx
	call	mult2@PLT
	movq	%rax, (%rbx)
	popq	%rbx
	ret
```



#### 展示程序的字节表示

> 将源代码编译为`.o`文件，然后用GDB调试，输入x/14 函数名



#### 操作数指示符

> 操作数：指示出执行一个操作中要使用的源数据值，以及放置结果的目标位置
>
> 格式：立即数（$+常数）	寄存器（寄存器的内容）	内存引用（将内存视为数组读取）



#### 寻址

> %rax：R[%rax]	0x104：M[0x104]	$0x108: 常数	(%rax): M[ R [%rax ] ]	
>
> 4(%rax):M[4 + R[%rax]]	9(%rax, %rdx): M[9 + R[%rax]+ R[%rdx]]
>
> 0xFC(, $rcx, 4): M[0xFC + R[%rcx] * 4]







### x86-64的细节

> 从数据的表示和处理以及控制的实现开始



## c语言中的控制结构

> 汇编中实现控制结构是通过jmp指令来在不同的函数中跳转

`if`

```c
long test(long x, long y, long z){
    long val = x + y + z;
    if(x<-3){
        if(y<z){
            val = x * y;
        } else {
            val = y * z;
        }
    } else if(x>2){
        val = x * z;
    }
    return val;
}
```

汇编

```
leaq	(%rdi,%rsi), %rax
	addq	%rdx, %rax
	cmpq	$-2, %rdi
	jge	.L2
	movq	%rsi, %rax
	imulq	%rdx, %rax
	ret
.L2:
	cmpq	%rdx, %rsi
	je	.L4
.L1:
	ret
.L4:
	movq	%rdi, %rax
	imulq	%rsi, %rax
	ret
```



`while`

> 通过jmp函数来实现无限次跳转	实现while的功能

```c
long loop_while2(long a, long b)
{
    long result = b;

    while(b > 0){
        result = a * result;
        b = b - a;
    }
    return result;
}
```



```
testq	%rsi, %rsi
	jle	.L4
	movq	%rsi, %rax
.L3:
	imulq	%rdi, %rax
	subq	%rdi, %rsi
	testq	%rsi, %rsi
	jg	.L3
	ret
.L4:
	movq	%rsi, %rax
	ret
```



> 注：如果将优化程度提升为-O1的话，while会被优化成do-while结构~



## 局部变量必须存在内存中的情况

> 寄存器不足以存放所有的局部变量
>
> 对一个局部变量取地址
>
> 局部变量为数组或者结构体 



## 机器级如何实现数据结构

> 结构体，联合
>
> 结构体地址按照对应的类型进行排列
>
> 联合，中的元素起始地址相同，多个元素使用同一个地址









## 内存访问越界的问题

> 1、设置偏移量，使无法轻易找到栈地址
>
> 2、设置标志位
>
> 3、设置栈权限，使其为读写状态

## 系统容易遭受缓冲区溢出攻击的问题





# 第四章、处理器体系结构

## 简单的指令集







# 第六章 硬盘

### 写内存





# 第七章 链接

**链接：**将各种代码和数据片段收集并组合成单一文件的过程                                                                     



### 7.1	编译器驱动程序

`main.c`

```
#include <stdio.h>
int sum(int *a, int n);
int arr[2] = {1, 2};

int main()
{
    int val = sum(arr, 2);
    return val;
}
```

`sum.c`

```
int sum(int *a, int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum+=a[i];
    }
    return sum;
}
```





**将两个文件链接生成一个可执行文件：**

> 一步执行的代码：
>
> ​	`gcc -Og -o prog main.c sum.o`

下面是逐个步骤：

​	1、将main.c 翻译为ASCII码的中间文件 main.i

```
cpp main.c main.i
```

​	2、运行c 编译器， 将ASCII中间文件翻译为一个ASCII汇编语言文件

```
cc1 main.i  -Og -o main.s
```

​	3、运行汇编器， 将汇编文件翻译为一个可重定位的目标文件

```
as -o main.o main.s
```

​	4、重复上述步骤生成 sum.o文件

​	5、运行链接器程序， 将两个文件以及一些必要的系统目标文件组合为一个可执行文件

```
ld -o prog main.o sum.o
```



### 7.2 静态链接

​		像上面程序中， 这样的静态链接器以一组可重定位目标文件和命令行参数为输入， 生成一个完全链接的、可以加载和运行的可执行目标文件作为输出。



为了构造可执行文件，链接器的主要作用：

1、符号解析

​		目标文件定义和引用符号， 每个全局变量、静态变量、函数名都对应于一个特点的符号。符号解析的作用就是将每一个符号引用正好与一个符号定义相对应。

2、重定位

​		链接器把每个符号定义与一个内存位置联系起来， 从而重定位这些代码、数据节。 然后修改每个符号的引用， 让他们指向这个内存地址。 链接器使用汇编器产生的重定位目录进行修改。



### 7.3	目标文件

**类型：**

- ​	可重定位目标文件	可以在编译时与其他可重定位文件结合生成可执行文件
- ​    可执行目标文件    可以直接复制到内存执行
- ​     共享目标文件   可以在加载和运行时，被动态地加载到内存并链接



### 7.4	可重定位目标文件

EL头

```
ELF 头：
  Magic：  7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (Position-Independent Executable file)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：              0x1020
  程序头起点：              64 (bytes into file)
  Start of section headers:          13528 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         28
  Section header string table index: 27
```



> 1）模数
> 第1个字节：DEL控制符，固定的
> 第2、3、4个字节：ELF三个字母
> 第5个字节：文件位数（0：无效、1：ELF32、2：ELF64）
> 第6个字节：大小端（0：无效、1：小端、2：大端）
> 第7个字节：ELF文件的主版本号，一般为1
> 后面的为预留字段。
> 2）文件类型：REL (Relocatable file)、DYN (Shared object file)、EXEC (Executable file)
> 3）Machine:   Intel 80386 ：硬件平台，此文件适合在哪个硬件平台下运行        
> 4）程序入口地址
>   Entry point address:               0x8048310
> 代表程序入口的虚拟地址，只有可执行文件跟共享库有入口（共享库的入口地址有什么用呢？）
> 5）Start of program headers:   52 (bytes into file) : (readelf -l ), 程序表头，装载时用到，因为目标文件不需要装载，所以为0。
> 6）Start of section headers:          2000 (bytes into file)
>       段表在文件中的偏移，也就是说段表从文件中的2000个字节开始的
>       2000是10进制，用计算器转换成16进制后就可以在那个，这个特别重要，找到段表，就代表了什么都有了
> 7）Size of section headers:           40 (bytes)
> 段表描述符的大小，猜测：会根据平台的不同，这个是固定的，因为在同一个平台下不同代码编出来的目标文件，结果是一样的
> 8）Number of section headers:         11
> 段表描述符数量，elf文件中，拥有的段的数量（所以说，一个段表描述符就是在描述一个段呗）
> 证明（readelf -S ）
> 9）Size of this header:     52 (bytes)
> ELF文件头本身的大小，猜测：会根据平台的不同，这个是固定的
> 10）Section header string table index: 8
> 段表字符串表所在的段在段表中的下标
>
> 总结：通过文件头找段表，之后在段表里面找到段表字符串表，段表中就能找到段表字符串标在文件中的偏移，之后就能生成整个段表。
>
> 原文链接：https://blog.csdn.net/qq_21331015/article/details/103210449





### 7.5	符号和符号表

**链接器中三种不同的符号：**

- 由本模块定义并能被其他模块引入的全局符号
- 本模块定义和引入的局部符号
- 由其他模块定义并引入本模块的全局符号







# 命令行上的操作合集



## GDB使用

```
quit	停止
run		运行
kill	关闭程序

layout asm	展示图形界面， 显示当前执行的语句

stepi 	执行1条指令	（si）

disas	反汇编当前函数
disas add	反汇编add函数

print	$rax
bt	backtrace	打印
info frame	打印栈帧信息
info registers
help
```

 

## 查看ELF文件

1、readelf(具体查看	第七章链接)

```
-h		查看头部表
-S		段表
-s		符号表
-d		依赖库
-p		查看某个段的内容
```









**打印出main函数的返回值**

​	`echo $?`







# 练习题

### 3.49

```
long vframe(long n ,long idx, long *q){
    long i;
    long *p[n];
    p[0] = &i;
    for (i = 1; i < n; i++) {
        p[i] = q;
    }

    return *p[idx];
}

long vframe(long n ,long idx, long *q)
n in %rdi, idx in %rsi, q in %rdx
```

```
vframe:
    pushq   %rbp                  	基址
    movq    %rsp, %rbp             	保存
    subq    %16, %rsp              	为i分配空间，留下空余
    leaq    22(,%rdi,8), %rax      	计算偏移量
    andq    $-16, %rax              偏移量
    subq    %rax, %rsp           	将指针向下移动，即为数组分配空间
    leaq    7(%rsp), %rax          	与下一步一起，保证对齐
    shrq    $3, %rax                
    leaq    0(,%rax,8), %r8         返回p[0]
```

 
