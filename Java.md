## 关键字

extends	一个类型是另一个类型的子类（继承）

final	最终属性	表面一个类不能派生出子类（常量类）

finally	处理异常情况，声明一个肯定会被执行的语句块（default?）

goto	跳转指令

implements	表明一个类实现了给定的接口

instanceof	测试一个对象是否为指定类型的实例对象

interface	接口

native	实现一个方法，与计算机相关的语言（其他高级语言）

package	包

strictfp	严格保证浮点数的运算

super	父类型的引用或父类型的构造方法

synchronized	表面一段代码需要同步执行	（线程同步）

transient		被transient关键字修饰的成员属性变量不被序列化

volatile	两个或多个变量必须同步发生变化



## 方法重载

> 普通函数需要加static关键字，否则无法直接被调用，需要实例对象

```
public class Main{
    public static void main(String []args){
        System.out.println(Add(1));
        System.out.println(Add(1, 2));
        System.out.println(Add(1, 2, 3));
    }

    public static int Add(int a, int b, int c){
        return a+b+c;
    }
    public static int Add(int a, int b){
        return a+b;
    }
    public static int Add(int a){
        return a;
    }
}
```



## 多态，接口

> 接口：	写的形式类似于类
>
> ​			interface(相当于函数声明)	声明之间可以继承
>
> ​			implements(相当于函数实现)	必须将定义全部实现，否则仍然为一个抽象类



## 构造方法&子类构造方法调用父类构造方法

**构造函数**：函数名同主类名相同，不能被（final，abstract，static）修饰

**子类调用父类**：super() (无参)	/  super(data)(有参)		默认都会先调用父类的构造

​				注：子类调用父类的构造函数时，需要写在子类构造的第一行

​	

## 多线程编程

> 进程：程序的一次动态执行的过程	并发过程中，**分配**的最小单位
>
> 线程：进程内可调度的最小单元

**线程的创建：**

头文件支持`java.lang.Thread`	/	通过实现Runnable接口或者Callable接口来完成定义



**都是通过重载或者实现run()函数实现的多线程**：



### No.1	继承Thread类

```
// Thread类定义：
public class Thread extends Object implements Runnable {}
```

> Thread 同为Runnable接口的子类



> 创建线程对象，调用start()函数

```java
import java.lang.Thread;
public class Thread1 extends Thread{
    private String str; 

    public Thread1(String str){
        this.str =str; 
    }

    public void run(){
        for(int i = 0; i < 50; i++){
            System.out.println(this.str + "正在运行..." +  i);
        }
    }
}
```

```java
public class Test{
    public static void main(String[] args) {
        Thread1 th1 = new Thread1("一号");
        Thread1 th2 = new Thread1("二号");
        th1.start();
        th2.start();
    }
}
```



### No.2	Runnable接口实现

> 创建Runnable类型指针，指向自定义线程对象	
>
> 将Runnable对象作为Thread参数，创建Thread对象
>
> 调用Thread对象的start();

```java
public class Thread1 implements Runnable{
    private String name;
    public Thread1(String name){
        this.name = name;
    }
    public void run(){
        for(int i = 0; i < 50; i++){
            System.err.println(name + "正在运行：" + i);
        }
    }
}
```

```java
public class Test{
    public static void main(String[] args) {
        Runnable th1 = new Thread1("一号");
        Runnable th2 = new Thread1("二号");
        
        new Thread(th1).start();
        new Thread(th2).start();
    }
}
```

**缺点：run没有返回值**(callable 可以传递返回值)



### No.3	Callable接口

> 1.将实现了Callable接口的对象类型作为参数传给FutureTask	生成FutureTask对象；
>
> 2.将Future对象作为参数，调用Thread一个构造函数，生成Thread对象
>
> 3.用Thread对象的start()函数，可以使用Future对象.get()得到call函数的返回值



```java
import java.util.concurrent.Callable;
public class Thread1 implements Callable<Integer>{
    private String name;
    public Thread1(String name){
        this.name = name;
    }

    public Integer call(){
        Integer sum = 0;
        for(int i = 0; i < 50; i++){
            System.out.println(this.name + i);
            sum += i;
        }
        return sum;
    }
}
```

```java
import java.util.concurrent.FutureTask;

public class Test{
    public static void main(String []args) throws Exception{
        Thread1 th1 = new Thread1("一号");
        Thread1 th2 = new Thread1("二号");
        Thread1 th3 = new Thread1("三号");

        FutureTask<Integer> ft1 = new FutureTask<Integer>(th1);
        FutureTask<Integer> ft2 = new FutureTask<Integer>(th2);
        FutureTask<Integer> ft3 = new FutureTask<Integer>(th3);

        new Thread(ft1).start();
        new Thread(ft2).start();
        new Thread(ft3).start();
        
        System.out.println(ft1.get());
        System.out.println(ft2.get());
        System.out.println(ft3.get());

    }

}
```



## 线程同步

```java
public class Thread1 implements Runnable{
    private int ticket = 10;
    public void run(){ 
        while(this.sale());
    }
    public synchronized boolean sale(){

                if(ticket<0){
                    System.out.println(Thread.currentThread().getName()+"已售完。");
                    return false;
                }

                try{
                    Thread.sleep(10);
                }catch(InterruptedException e){
                    e.printStackTrace();
                }
                System.out.println(Thread.currentThread().getName()+"正在收票"+ticket--);
                return true;
    }
}
```

```java
public class Test{

    public static void main(String[] args) {
        Runnable th1 = new Thread1();

        new Thread(th1).start();
        new Thread(th1).start();
        new Thread(th1).start();
    }
}
```



### 线程的五种状态（线程的生命周期）

> 创建、就绪、运行、阻塞、终止





## **static** 

> ​	当同一个类对象需要共享一个数据时：
>
> 将一个元素变为全局变量，声明周期同类一致；
>
> 
>
> ​	方便访问变量时：不需要类对象直接访问该元素：
>
> 无需创建实例对象即可直接调用函数后者成员变量；	





## 标识符的命名规则

> - 只能由字母（大小写，26个英文字母）、数字（0~9）、下划线“_”和“$”符组成。
> - 数字不可以开头。
> - 不可以使用关键字和保留字，但是可以包含关键字和保留字。
> - Java中严格区分字母大小写。
> - 对长度无要求。
> - 标识符内不能含有空格。



## GUI(Graphical User Interface)基础知识

>  AWT,Java最早的界面库。（java.awt：Abstract Windows ToolKit（抽象窗口工具包），**需要调用本地系统方法来实现功能，属重量级控件**。）
>
> Swing,是对AWT的扩展。（javax.swing：在AWT的基础上， 建立的一套图像界面系统，其中提供了更多的组件，**而且完全由Java实现。增强了移植性，属轻量级组件**。）



## 组件-容器

> panel -最简单的容器		Applet -提供applet及其运行环境之间的接口
>
> scrollPane -滚动的容器类
>
> window -窗口，无边框和菜单栏	frame	带标题和边框的顶层窗口
>
> ​															Dialog 对话框	fileDialog -文件对话框



## 布局管理器

> FlowLayer 流式布局管理器	左到右，上到下排列	panel和Applet的默认模式
>
> GridLayer 网络布局管理器	每个单元格放一个组件或元素
>
> GridBagLayer	网络包布局管理器	
>
> BorderLayer	边缘布局管理器	按照东西南北中放置	window、Frame、Dialog的默认模式
>
> CardLayer	卡片布局管理器	



## 访问权限控制符

> default	具有包访问权限，当不适用其他三种修饰时，说明具有包访问权限，即使用同一个包的可以互相访问
>
> public：	可以被任意类使用
>
> private:	只能被自己类中的方法使用
>
> protected：	可以被同一个包下的类使用，也可以被子类使用，其他类不可用



## 字符串比较

> 1.equals	比较两个字符串是否相同



> 2. ==		
>
>     当两个都被赋予常数时，返回true
>
>     当任意一个指向对象时，返回false
>
> ```java
> class Teststringcomparison3{  
>  public static void main(String args[]){  
>    String s1="Sachin";  
>    String s2="Sachin";  
>    String s3=new String("Sachin");  
>    System.out.println(s1==s2);//true
>    System.out.println(s1==s3);//false  
>  }  
> } 
> ```



> 3.compareTo()
>
> ​	比较两个字符串的字典序	大于为正，等于为零，小于为负



## 内部类

> ```
> class test{
>         public final static int a = 10;
>    }
> ```
>
> 





## 异常处理

try-catch	对异常进行检查并处理

throw	抛出异常对象（只能一个）

throws	声明可能会出现的异常（可以多个）



> Exception 是所有异常的父类，可以抓取所有异常，然后将栈顶的信息打印出：

e.printStackTrace()

```JAVA
public static void main(String[] args) {
        int[] arr = {1, 2, 3};
        try {
            System.out.println("before");
            arr = null;
            System.out.println(arr[100]);
            System.out.println("after");
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("after try catch");
    }

```



## 事件处理的方式（不确定）

内部类处理、外部类处理、自身类处理、匿名类处理



## ArrayList

```
add			添加元素
remove		删除元素
size		获取长度
get			查找指定位置的元素
clear		清空元素
set			将指定位置设为指定元素
```

