## Pthread

pthread_self   pthread_equal

```c
  1 #include<stdio.h>
  2 #include<stdlib.h>
  3 #include<string.h>
  4 #include<pthread.h>
  5 
  6 int main()
  7 {
  8     pthread_t tid = -1;
  9     tid = pthread_self();
 10     printf("tid = %lu\n",tid);
 11     if(pthread_equal(tid,pthread_self()))
 12     {
 13         printf("Equal..\n");
 14     }
 15     return 0;
 16 }   

```



打字机特效：

关键 fflush:清空缓存区

​		putchar：输入到缓存区

​		usleep：微秒单位

```c
#include<stdio.h>
  2 #include<string.h>
  3 #include<stdlib.h>
  4 #include<unistd.h>
  5 #include<pthread.h>
  6 
  7 void *fun1(void *arg)
  8 {
  9     char i;
 10     for(i = 'a';i<='z';i++)
 11     {
 12         putchar(i);
 13         fflush(stdout);
 14         usleep(100000);
 15     }
 16     return NULL;
 17 }
 18 void *fun2(void *arg)
 19 {
 20     char i;
 21     for(i = 'A';i<='Z';i++)
 22     {
 23         putchar(i);
 24         fflush(stdout);
 25         usleep(100000);
 26     }
 27     return NULL;
 28 }
 29
 30 int main()
 31 {
 32     int ret = -1;
 33     int ret2 = -1;
 34     pthread_t tid1, tid2;
 35     ret = pthread_create(&tid1,NULL,fun1,NULL);
 36     ret2 = pthread_create(&tid2,NULL,fun2,NULL);
 37     printf("press any to end...\n");
 38     getchar();
 39     return 0;
 40 }

 
 

```

