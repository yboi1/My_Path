# MasterCalculate

`#pragma omp parallel private(tid)`作为并行开始的标志

#### 输出多个hello world

```c
#include<cstdio>
#include<omp.h>
int main()
{
	int nthreads, tid;
#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		printf("hello World from thread = %d\n", tid);
		if (tid == 0)
		{
			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

	}
	return 0;
}
```

#### 线程的嵌套

```c
#include<cstdio>
#include"omp.h"
int i = 0;
void output()
{
#pragma omp parallel num_threads(2)
	printf("inner : region 2  %d  %d\n", i++,omp_get_thread_num());
}
int main()
{
	int n = 3;

	printf("begin...\n");
	printf("n = %d\n", n);
	omp_set_nested(2);
#pragma omp parallel num_threads(3)
	{
		printf("outer : region 1  %d  %d\n",i++, omp_get_thread_num());
		output();
#pragma omp parallel num_threads(2)
		printf("inner : region 3  %d  %d\n",i++, omp_get_thread_num());
	}
	printf("end...\n");
	return 0;
}
```

> 首先先创建三个线程，分别调用了函数创建两个线程，之后回到主函数又创建了两个新的线程

#### 变量传入的状态

private 私有  firstprivate 有初始值  shared 线程间共享的  lastprivate 将最后并行结果赋给主函数中的变量

```c
#include<cstdio>
#include"omp.h"
int main()
{
	int i = 1, j = 2, k = 3;
#pragma omp parallel num_threads(2)\
	private(i) firstprivate(j) shared(k)
	{
		i = 0;
		printf("初值： %d  %d  %d\n", i, j, k);
#pragma omp barrier
		i = omp_get_thread_num();
		j += omp_get_thread_num() + 1;
		if (omp_get_thread_num() == 0) k = 0;
#pragma imp barrier 
		printf("%d  %d  %d\n", i, j, k);
	}
	printf("终值： %d  %d  %d\n", i, j, k);
	return 0;
}
```

#### section代码段

> section代码段只会被一个线程执行，执行完不等待

```c
#include<cstdio>
#include"omp.h"
#define _CRT_SECURE_NO_WARNINGS
int main()
{
	int i = 10, j = 20, k = 30;
	int nt;
	scanf_s("%d",&nt);
#pragma omp parallel num_threads(nt)
	{
		printf("ouput 1 : %d %d %d\n", i, j, k);
#pragma  omp barrier
#pragma omp sections private(i) firstprivate(k) lastprivate(j) 
		{
#pragma omp section 
			{
				i = 11; k += 10; j = k;

				printf("output 2 k = %d thread = %d\n", k, omp_get_thread_num());
			}
#pragma omp section 
			{
				i = 12; k += 20; j = k;
				printf("output 2 k = %d thread = %d\n", k, omp_get_thread_num());
			}
#pragma omp section 
			{
				i = 13; k += 30; j = k;
				printf("output 2 k = %d thread = %d\n", k, omp_get_thread_num());
			}
		}
		printf("output 3 : %d %d %d\n", i, j, k);
	}
	printf("output 4 : %d %d %d\n", i, j, k);
	return 0;
}
```

#### atomic 和critical代码段

当操作同一个共享变量时，可以保证每一个线程的操作都是有效的

```c
#include<cstdio>
#include"omp.h"
int main()
{
	int i = 0;
#pragma omp parallel num_threads(800)
	{
#pragma omp critical（atomic）
		i++;
	}
	printf("%d", i);
	return 0;
}
```

可以保证输入时的顺序

```
#include<cstdio>
#include"omp.h"
int main()
{
	int i, th;
	scanf_s("%d", &th);
#pragma omp parallel num_threads(th)
	{
#pragma omp critical
		{
			printf("请输入线程 %d 中i的值：\n", omp_get_thread_num());
			scanf_s("%d", &i);
		}
		printf("线程 %d 中i的值：%d\n", omp_get_thread_num(),i);
	}
}
```

#### flush代码段

当一个a线程需要使用另一个b线程改变的变量时，确保使用成功需要b在修改完之后刷新缓存，即调用flush代码段`#pragma omp flush(a,b,...)`若不标注变量则默认为所有

#### collapse合并for/do循环

![image-20230413114704765](C:\Users\Lenovo\AppData\Roaming\Typora\typora-user-images\image-20230413114704765.png)