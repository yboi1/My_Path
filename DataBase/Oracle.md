## Oracle

数据库位于硬盘之上，实例位于内存之中

#### sqlplus登录

> scott用户密码: 11
>
> sys用户的密码: sys 
>
> 1. sqlplus  ↙ 用户名 ↙	密码 ↙
>
> 2. sqlplus  用户名/密码↙
>
> 3. sqlplus 用户名/密码@//ip/实例名 ↙
>
> 远程登录oracle服务器方式，如(sqlplus [scott/11@//192.168.1.100/orcl](mailto:scott/11@//192.168.1.100/orcl))
>
> 4. sqlplus 用户名/密码@实例别名 ↙（实例别名配置参考附件2：Oracle客户端实例别名配置.docx）
>
> 5. 以管理员身份登陆：sqlplus / as  sysdba	
>
> 在Oracle数据库安装时指定了登陆密码
>
> 6. 解锁用户：SQL> alter user scott account unlock 
>
> 管理员身份登陆，给scott用户解锁。用户默认锁定
>
> 7. 修改用户密码：SQL> alter user scott identified by 新密码
>
> 管理员身份登陆，给scott用户修改密码
>
> 8. 查看当前语言环境：SQL> select userenv('language') from dual  
>
> Scott hr  sys
>
> 

#### Linux/Unix上启动数据库服务

```
[oracle@deng ~]$ sqlplus  sys/sys as sysdba
Sqlplus: 是一个客户端命令
Sys是超级管理员的用户名
Sys是超级管理员的密码
As sysdba 表示使用系统管理员的方式登录

关闭数据库:
SQL> shutdown immediate 
Database closed.
Database dismounted.
ORACLE instance shut down.

关闭Oracle监听服务(先退出sqlplus)
SQL> quit;
Disconnected from Oracle Database 11g Enterprise Edition Release 11.2.0.1.0 - 64bit Production
With the Partitioning, OLAP, Data Mining and Real Application Testing options
[oracle@deng ~]$ lsnrctl stop

启动Oracle数据库

SQL> startup
ORACLE instance started.

Total System Global Area  830930944 bytes
Fixed Size		    2217912 bytes
Variable Size		  616564808 bytes
Database Buffers	  205520896 bytes
Redo Buffers		    6627328 bytes
Database mounted.
Database opened.
SQL>

启动监听服务:
[oracle@deng ~]$ lsnrctl start

启动和关闭使用oracle用户

Sqlplus使用管理员登录后
startup
启动数据库实例
shutdown
关闭数据库实例
如果要远程连接到数据库还得，启动监听服务
在命令行（不是sqlplus中）
lsnrctl start
lsnrctl status
lsnrctl stop
```

#### 设置表格展示形式

```sql
set pagesize 140
set linesize 120
```

#### as重命名

```sql
select empno as "员工号" from emp
```

#### DISTINCT去重

 作用于之后输入的所有列

select distinct empno from emp

#### 算数运算

与数学的运算符顺序一致

#### NULL值

> 任何包含NULL值运算的算式最终结果都为NULL
>
> NULL != NULL
>
> nvl(a,b) 	当a为NULL时，将结果为b，否则为a
>
> 在SQL中，判断一值是否等于另外一值不用“=” 和“!=”而使用is和is not。
>
> 空值不是空格或者零，是一个不可预知的数

#### 比较运算

特殊：不等于：<> 	or 	!=

​			等	于：=    （不是==）

且：and   或：or

in(10,20)  区间在10-20之间的数

not in  区间不在10-20之间的数（not in 中的所有条件都要满足）

特：

> 但是：如果是 ….. not in (10, 20, NULL) 可不可以呢？
>
> ​	☆NULL空值：如果结果中含有NULL，不能使用not in 操作符， 但可以使用in操作符。
>
> ​	课后思考为什么？？？
>
> 因为之前说过NULL的任何逻辑运算都是假，可得：
>
> deptno not in(10,20,NULL) -> deptno != 10 &&deptno != 20 &&deptno !=NULL （永远假）
>
> deptno in(10,20,NULL) -> deptno ==10 || deptno == 20 || deptno ==NULL （不影响）

#### where条件过滤

需要比较的时候语句中用 where 后面跟条件

字符串中大小写敏感

 select sysdate from dual 		查看系统当前的日期 (注意其格式)

修改日期格式可以查看文档

#### 模糊查询

‘%’ 匹配多个字符

‘_’匹配一个字符

转义字符：‘/’  escape /  

```
SQL> select * from emp where ename like '%\_% ' escape '\'  
```

#### 语句排序

> l 排序的规则
>
> • 可以按照select语句中的列名排序
>
> • 可以按照别名列名排序
>
> • 可以按照select语句中的列名的顺序值排序
>
> • 如果要按照多列进行排序，则规则是先按照第一列排序，如果相同，则按照第二列排序；以此类推

order by sal asc;

默认asc为升序排序，desc为降序排序

可以用别名代替sal，或者用序号（第几列的数据）代替

当含有多个参数时，先按照第一个排序，当相同时按照第二个排序

若想让值为NULL的行排在最后，则添加nulls late

#### 字符函数

##### concat连接函数

```sql
select concat('hello','world') as "你好" from dual;
select concat('hello','world','nihao') from dual //错误写法
select concat('hello',concat('world','nihao')) from dual
select  'hello' || 'world' || '我的'from dual;
```

##### replace替换函数

```
select replace('hello world', 'l', '*') from dual;
he**o wor*d
```

将*变为无可达到删除的效果

##### instr匹配函数

```
select instr('hello world', 'llo') from dual;  --3
返回llo匹配的下标
```

##### lpad&rpad填充函数

```
select lpad('abcd', 10, '*') , rpad('abcd', 10, '#') from dual;
******abcd	abcd######
```

##### trim删除函数

只删除前后的匹配的元素

```
select trim('    Hello     ') from dual;   //删除空格    
select trim('H' from 'Hello worldH') from dual;  //删除前后H
```

#### 数值函数

```
round（3.1415926，3） 保留三位小数，四舍五入

mod	（3，2） 3对2取模 结果为1

trunc （3.1415926,	3）保留三位小数，后面的数直接舍去 
```



#### 时间函数

```
select sysdate from dual;

select to_char(sysdata,'yyyy-mm-dd hh24:mi:ss') from dual;

select months_between(sysdate,sysdate-31) from dual;
计算95个月以后是哪年、哪月、那天：
select add_months(sysdate, 95) 哪一天 from dual

last_day：日期所在月的最后一天。
select last_day(sysdate) from dual  

next_day：指定日期的下一个日期
SQL> select next_day(sysdate, 'monday') from dual			从当前时间算起，下一个星期一
```

#### 转换函数

to_number -- to_char -- to_date     to_char为媒介

日期：

```
'yyyy-mm-dd hh24:mi:ss' 精确日期 年月日，时分秒
select to_char(sal, 'L9,999.99') from emp  货币转换
```

#### 通用函数

> l NVL (expr1, expr2)
>
> l NVL2 (expr1, expr2, expr3)
>
> l NULLIF (expr1, expr2)
>
> l COALESCE (expr1, expr2, ..., expr**n**)

```
nvl 若1为NULL，返回2，否则返回1
nvl2 若1为NULL，返回2，否则，返回3
nullif 如果1=2返回NULL，否则返回1
coalesce 返回第一个不为NULL的元素
```

#### 条件表达式

##### case-end



```
select ename, job, sal, case job when'PRESIDENT' then sal+1000
									 'MANAGER' 	 then sal+800
									 else sal+400
									end sal1
from sal_add
```

##### decode

```
select ename, job, sal, decode(job,'PRESIDENT',sal + 1000
									'MANAGER' ,sal+800
												sal+400) as sal_add
from emp
```

#### 分组函数

##### 分组函数

sum ()

count (*)		求种类个数： count(distinct job)

若要算得所有数可：count（nvl（comm，0））；

 组函数有自动排去NULL元素的特点

所以count所得的数为不包含NULL元素的个数

##### 分组数据

group by

select * from emp group by deptno

注：select中未在主函数中出现的列，必须都要包含在group by 后面

##### Having

> select	* from __   where __  group by __ Having __ order by __

where是先过滤后分组，其中不能使用组函数

Having是先分组后过滤，可以使用组函数，但是无用数据过多时，先过滤效率更高

#### 多表查询

##### 笛卡尔积

select * from emp,dept	得到的结果则为两表相乘得到的结果

多表的乘积拼接在一起

笛卡尔积的行数 = table1的行数 x table2的行数

笛卡尔积的列数 = table1的列数 + table2的列数

##### 等值连接和不等值连接

> 从概念上，区分等值连接和不等值连接非常简单，只需要辨别where子句后面的条件，是“=”为等值连接。不是“=”为不等值连接。

大于小于等运算符均为不等值连接

##### 外连接

> 左外连接：当 where e.deptno=d.deptno 不成立的时候，=左边所表示的信息，仍然被包含。
>
> 写法：与叫法相反：where e.deptno=d.deptno(+)  
>
> 右外连接：当 where e.deptno=d.deptno 不成立的时候，=右边所表示的信息，仍然被包含。
>
> 写法：依然与叫法相反：where e.deptno(+)=d.deptno

```sql
以上我们希望将没有员工的部门仍然包含到查询的结果当中。因此应该使用外链接的语法。
SQL> select d.deptno 部门号, d.dname 部门名称,count(e.empno) 人数  from emp e, dept d
  	 	where e.deptno(+)=d.deptno  group by d.deptno, d.dname; 

```



##### 自连接

同一个表储存的指引也在该表

>  select e.ename || ' 的主管是 ' || nvl(b.ename, '他自己' )
>
> ​    from emp e, emp b
>
> ​    where e.mgr=b.empno(+) 

##### 子查询

```
select * from emp where sal > (select sal from emp where  ename = 'SCOTT')  

select * from (select ename, sal, sal*12 年薪 from emp); 
在子查询得到的结果中查询
```

###### 1.单行子查询

```
SELECT last_name, job_id, salary
FROM   employees
WHERE  job_id =  
                (SELECT job_id
                 FROM   employees
                 WHERE  employee_id = 141)
AND    salary >
                (SELECT salary
                 FROM   employees
                 WHERE  employee_id = 143); 
```

###### 2.多行子查询

> **IN**     **等于列表中的任意一个**
>
> **ANY**   **和子查询返回的任意一个值比较**
>
> **ALL**    **和子查询返回的所有值比较**

任意代表所有!

#### 集合运算符

union  intersect  minus

```
select * from emp where deptno=10
union
select * from emp where deptno=20       

select * from emp where deptno in(10, 20)
intersect
select * from emp where deptno=20        

select * from emp where deptno in(10, 20)
minus
select * from emp where deptno in(20, 30)      
```

####    数据处理

insert into emptno values(1,'1name','1num');

> 如果：插入的时候没有插入所有的列，就必须显式的写出这些列的名字。
>
> SQL>  insert into emp(empno, ename, sal, deptno) values(1002, 'Marry', 6000, 20); 

#### &地址符

任何可以改变的地方都可以添加&，达到变量的目的

```
select * from &emp;
select &values from emp;
insert into emp values(&1,'&2','&3')
当输入的为字符型时，一般在输入之前加'',避免输入麻烦
```

#### 批处理

```
creat table emp1 as select * from emp where 1 = 2;
```

由于条件永远不会成立，所以相当于只拷贝了表的结构，而不拷贝表的数据

```
insert into emp10(empno, ename, sal, deptno)
	   select empno, ename, sal, deptno	 from emp
	   where deptno=10;
```

将emp表中deptno值为10的行插入到emp1中

#### 更新数据

update   set

```
update emp1 set sal=4000,comm=300 where ename = 'CLARK';
找到要修改的行的特殊值作为判断条件，否则将全部修改
```

#### 删除数据

delete  from

```
delete from emp1 where sal = 4000;
from 关键字在oracle中可以省略不写，但mysql中不可以
删除数据时最好添加条件，否则可能会全部删除
```

#### 事务

##### 隔离事务

多事务并发时可能出现的情况

> 1. **脏读**: 对于两个事务     T1, T2, T1 读取了已经被 T2 更新但还**没有被提交**的字段.     之后,     若     T2 回滚, T1读取的内容就是临时且无效的.
> 2. **不可重复读**: 对于两个事务     T1, T2, T1 读取了一个字段, 然后 T2 **更新**了该字段.     之后,     T1再次读取同一个字段,     值就不同了.
> 3. **幻读**: 对于两个事物     T1, T2, T1 从一个表中读取了一个字段, 然后 T2 在该表中**插入**了一些新的行.     之后,     如果     T1 再次读取同一个表, 就会多出几行.

##### 控制事务

创建保存点：savepoint aa;

回滚到保存点：rollback to aa;

回滚到最初保存点：rollback；

#### 表的创建

```
creat table test1 (tid number,tname varchar2(20),hiredate date default sysdate);
default sysdate //表示若不插入时间则使用默认时间

create table emp10  as  select * from emp where 1=2 
```

#### 修改表

```
alter table test1 add image blob;		加入新列image类型为blob
alter table test1 modofy tname varchar2(40);	改变列的大小
alter table test1 drop column image;	删除列
alter table test1 rename column tname to uername;	重命名
```

```
	export OCCI_HOME=/opt/instantclient_11_2                                                 
  5 export OCCI_INCLUDE_DIR=$OCCI_HOME/sdk/include
  6 export OCCI_LIBRARY_PATH=$OCCI_HOME
  7 export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OCCI_LIBRARY_PATH
  8 # 程序编译是搜索的库目录
  9 export LIBRARY_PATH=$LIBRARY_PATH:$OCCI_LIBRARY_PATH
 10 # 程序编译时搜索的头文件目录
 11 export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$OCCI_INCLUDE_DIR

```

