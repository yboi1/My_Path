# Mysql

### 登录与重启

```
mysql -uroot -pZyb187367..
[root@localhost ~]# systemctl stop mysqld  		//关闭数据库
[root@localhost ~]# systemctl start mysqld		//开启数据库
```

```
systemctl restart mysqld		//重启数据库
systemctl status mysqld			//查看数据库状态
```

### 数据库操作

##### 创建

```
1.默认创建
mysql> create database mydb1;
2.设置使用utf_8字符集的数据库
mysql> create database mydb2 character set utf8;
3.创建一个使用utf-8字符集，并带校对规则的mydb3数据库。会对存入的数据进行检查。
mysql> create database mydb3 character set utf8 collate utf8_general_ci;
```

##### 查看

```
show databases;
show creat databases mydb2;
```

##### 修改

```
alter database mydb1 character set utf8;
```

##### 删除

```
drop database mydb1;
```

### 表操作

```
创建
creat table emp(id int ,name varchar(20));
查看
show tables;
show create table emp;
desc emp;
修改
rename table emp to worker;
alter table emp add column height double;
alter table emp modify column height float;
alter table emp drop column height;
alter table emp character set gbk;
删除
drop table worker;

```

### 表数据的CURD

```
创建
creat table emp(id int,name varchar(20));
insert into emp values(1,"张三");
修改
update emp set id = 2 where name = "张三";
删除
delete from emp where name = "张三";
部分查找
select id,name as "姓名"，id * 10 部门id from emp where name = "张三";
```

### 开发前准备

```
找到对应的头文件
/usr/include/mysql/mysql.h
找到对应的库文件
/usr/lib64/mysql/libmysqlclient.a
```

### mysql与c语言连接

#### 增删改操作

编译运行

```
gcc __.c -L/usr/lib64/mysql -lmysqlclient
```



```
  1 #include<stdio.h>
  2 #include<string.h>
  3 #include<stdlib.h>
  4 
  5 #include<mysql/mysql.h>
  6 #define __HOST__ "192.168.122.1"
  7 #define __USER__ "root"
  8 #define __PWD__ "Zyb187367.."
  9 #define __DB__  "scott"
 10 
 11 #define SIZE 128
 12 int main()
 13 {
 14     char buf[SIZE];
 15     MYSQL *mysql = NULL;
 16     int ret = -1;
 17     mysql = mysql_init(NULL);
 18     if(NULL == mysql)
 19     {
 20         printf("mysql_init failed...\n");
 21         return 1;
 22     }
 23     printf("初始化ok...\n");
 24     MYSQL *mysql1 = NULL;
 25     mysql = mysql_read_connect(mysql,__HOST__,__UESR__,__PWD__
 		，__DB__,0,NULL,0);
 26     if(NULL == mysql)
 27     {
 28         printf("mysql_real_connect failed...\n");
 29         return 1;
 30     }
 31     printf("连接数据库成功\n");
 32     memset(buf,0,SIZE);
 33     strcpy(buf,"insert into dept values(1,'1name','1loc')");
 34     ret = mysql_query(mysql,buf);
 35     if(0 != ret)
 36     {
 37         printf("mysql_query failed...\n");
 38         return 1;
 39     }
 40     printf("Operate Success...\n");
 41 
 42     mysql_close(mysql);
 43     return 0;
 44 }


```

#### select语句

```
1.初始化
2.连接
3.输入buf select * from empt
4.MYSQL_RES * res 来接收返回的值 mysql_store_result(mysql)
5.mysql_num_rows	mysql_num_fields
	行数			   列数
```

> ```
> #include <stdio.h>
> #include <string.h>
> #include <stdlib.h>
> 
> #include <mysql/mysql.h>
> 
> #define __HOST__ "192.168.21.28"
> #define __USER__ "root"
> #define __PASSWD__ "123456"
> #define __DB__ "scott"
> 
> #define SIZE 128
> ```

>     int ret = -1;
>     int i, j;
>     unsigned long row_nums = 0;
>     unsigned int col_nums = 0;
>     
>     MYSQL *mysql = NULL;
>     MYSQL_RES *res = NULL;
>     MYSQL_ROW row = NULL; //一行一行的获取
>     
>     char buf[SIZE];

```
1.初始化
mysql = mysql_init(NULL);
2.连接数据库
mysql = mysql_real_connect(mysql,__HOST__,__USER__, __PASSWD__, __DB__, 0, NULL, 0);)
3.执行select语句
strcpy(buf, "select * from dept");
ret = mysql_query(mysql,buf);
4.获取结果集
res = mysql_store_result(mysql);
5.获取结果集中行数
row_nums = mysql_num_rows(res);
6.获取结果集中列数
col_nums = mysql_num_fields(res);
```

