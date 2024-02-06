c库中的io函数工作流程

错误处理函数

```
#include<stdioh.h>
#include<erron>
 FILE *New = fopen("txt","r");
 if(New == NULL)
 {
   printf("%d",erron);
   printf("%s",strerror(erron));
   
   简便：
   perron("fopen erron");
 }
```

## MakeFile

精华：

> 变量： OBJS = add.o sub.o     (变量可以数字开头，大小写敏感)
>
> $@  目标   $^ 全部依赖文件      $<第一个依赖文件
>
> 两个函数：SRC=$(wildcard *.c)
>
> ​					OBJS=$(patsubst %.c ,%.o,$(SRC))
>
> 

第一版：

```makefile
SRC=$(wildcard %.c)
OBJS=$(paysubst %.c , %.o ,$(SRC)) 
TARGET=test
====================================================================
test:add.o sub.o mul.o div.o  test.o
	gcc add.o sub.o mul.o div.o test.o -o test
====================================================================
$(TARGET):$(OBJS)
	gcc $(OBJS) -o $(TARGET)
	====================================================================
test.o:test.c
    gcc -c test.c
add.o:add.c
    gcc -c add.c
sub.o:sub.c
    gcc -c sub.c
mul.o:mul.c
    gcc -c mul.c
div.o:div.c
    gcc -c div.c
====================================================================
%.o:%.c
	gcc -c $< -o $@
	
.PHONY:clean
clean:
	rm -rf $(OBJS) $(TARGET)
```

第二版（变量）

```makefile
#变量
OBJS=add.o sub.o mul.o div.o test.o
TARGET=test
$(TARGET):$(OBJS)
    gcc $(OBJS) -o $(TARGET) 
add.o:add.c
    gcc -c add.c -o add.o
sub.o:sub.c
    gcc -c sub.c -o sub.o
mul.o:mul.c
    gcc -c mul.c -o mul.o
div.o:div.c
    gcc -c div.c -o div.o
test.o:test.c
    gcc -c test.c -o test.o
clean:
    rm -rf $(OBJS) $(TARGET)
```



```makefile
  1 OBJS = add.o sub.o mul.o div.o test.o
  2 TARGET = test
  3 
  4 $(TARGET):$(OBJS)
  5         gcc $(OBJS) -o $(TARGET)
  6 %.o:%.c
  7         gcc -c $< -o $@
  8 clean:
  9         rm -rf $(OBJS) $(TARGET)

```



## 修改子工作文件：

（文件内的工作行）

```c
  1 #include<stdio.h>
  2 #include<string.h>
  3 #include<stdlib.h>
  4 #include<unistd.h>
  5 #define SIZE 32
  6 int main(void)
  7 {
  8         int ret = -1;
  9         char buf[SIZE];
 10 
 11         //GetCwd
 12         memset(buf,0,SIZE);
 13         if(NULL==getcwd(buf,SIZE))
 14         {
 15                 perror("getcwd");
 16                 return 1;
 17         }
 18         printf("buf = %s\n",buf);
 19 
 20         //ChangeDir
 21         ret = chdir("/home/boyi");
 22         if(-1 == ret)
 23         {
 24                 perror("chdir");
 25                 return 1;
 26         }
 27 
 28         //GetDir
 29         if(NULL == getcwd(buf,SIZE))
 30         {
 31                 perror("getcwd");
 32                 return 1;
 33         }
 34         printf("buf = %s\n",buf);
 35         return 0;
 36 }
 37 

```



## 获取子类与父类PId

```
  1 #include<stdio.h>
  2 #include<sys/types.h>
  3 #include<unistd.h>
  4 
  5 int main()
  6 {
  7     pid_t pid = getpid();
  8     printf("The Pid is: %d\n",pid);
  9 
 10     pid = getppid();
 11     printf("The Parent Pid is : %d\n",pid);
 12 
 13     pid = getpgid(getpid());
 14     printf("The Group Pid is: %d\n",pid);
 15 
 16     return 0;
 17 }
```

## 子进程与父进程的分开操作

```c
  1 #include<stdio.h>
  2 #include<sys/types.h>
  3 #include<unistd.h>
  4 #include<stdlib.h>
  5 
  6 int main()
  7 {
  8     pid_t pid = fork();
  9     if(0 == pid)
 10     {
 11         while(1)
 12         {
 13             printf("Son: pid = %d , ppid = %d\n",getpid(),getppid());
 14             sleep(1);
 15         }
 16     }
 17     else
 18     {
 19         while(1)
 20         {
 21             printf("Father : pid = %d , spid = %d\n",getpid(),pid);
 22             sleep(1);
 23         }
 24     }
 25 
 26     return 0;
 27 }   
```

## 存储映射的代码示例

通过将文件的存储区与内存相关联，进而实现通过对内存的修改来修改文件的内容

```
 10 int main()
 11 {
 21         return 1;
 22     }
 23 
 24     //2.将文件映射到内存中
 25     addr = mmap(NULL,1024,PROT_WRITE | PROT_READ,MAP_SHARED,fd,0);
 26     if (addr == MAP_FAILED)
 27     {
 28         perror("mmap");
 29         return 1;
 30     }
 31     printf("文件存储映射Ok....\n");
 32     //3.关闭文件
 33     close(fd);
 34     //4.写文件（在内存中写）
 35     memcpy(addr,"1234567890",10);
 36     //5.断开存储映射
 37     munmap(addr,1024);
 38     return 0;
 39 }

```

**不同进程间可以通过对同一个文件进行映射，达到通信的作用！**



#### 会话

> 在Linux中，会话（session）是指用户登录到系统后，在一段时间内与系统交互的整个过程。它通常包含以下几个部分：
>
> 1. 登录过程：用户通过用户名和密码登录到系统。
> 2. shell会话：用户进入一个交互式shell环境，在其中可以执行命令、运行程序等操作。
> 3. 环境变量：用户可以设置环境变量，这些变量会在整个会话期间保持不变，对于该用户运行的所有程序都可见。
> 4. 作业控制：用户可以启动多个作业，使用shell提供的作业控制命令来管理这些作业。
> 5. 退出会话：用户可以通过执行exit或logout命令来退出会话。
>
> 在Linux中，每个会话都有一个唯一的会话ID（session ID），通常由init进程在创建新会话时分配。每个会话都有一个控制终端（controlling terminal），通常是用户登录时使用的终端。控制终端用于与用户交互，并且可以接收和发送信号。如果控制终端关闭或断开连接，会话将终止。

会话指的是用户与系统交流的整个过程，一个会话可以在后端运行，不需要终端。终端只是会话的一小部分。







#### 守护进程

> 在计算机操作系统中，守护进程（daemon）是一种在后台运行的进程，它通常不受直接的用户控制，而是在系统启动时自动启动，并且会一直运行直到系统关闭。守护进程通常不会向控制台输出信息，而是将日志信息写入日志文件。

守护进程的创建步骤：

1.先用fork创建一个子进程，将其pid返回给父进程

2.子进程中调用setsid（）函数创建一个会话，使得该子进程称为组长

使其脱离终端的控制

3.关闭所有的文件描述符

4.调用chdir（） 改变当前的工作目录

5.将输入输出，错误输出重定向到dev/null  文件中

6.运行守护进程任务
