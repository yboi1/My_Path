C++函数中调用C语言函数：

```c++
#include<stdio.h>
#ifdef  __cplusplus
extern"C"
{
#endif
	void func();
#ifdef __cplusplus
}
#endif
```

extern的调用原因：

c++与c语言中对于函数预编译后所产生的名字不相同，c++的名字中还会包含传入参数的数据类型，所以c++可以进行函数重载。

同时c++中许多库函数任然继承着c的内容
