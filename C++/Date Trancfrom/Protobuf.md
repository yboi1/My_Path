# Protobuf

要编译程序需要先配置环境

1.protoc 编译`protoc ./persion.proto --cpp.out ./`生成两个文件

2.添加库和依赖

包含目录 `include`

库目录 `lib`

C/C++ 预处理定义`PROTOBUF_USE_DLLS`

链接器输入 添加依赖项`libprotobufd.lib`





```c++
#include<iostream>
#include<string.h>
#include"persion.pb.h"
using namespace std;
int main()
{
	/*int32 id = 1;
	string name = 2;
	bytes sex = 3;
	int32 age = 4;*/
	Persion p;
	p.set_id(1001);
	p.set_name("路飞");
	p.set_sex("男");
	p.set_age(17);

	string output;
	p.SerializeToString(&output);
	cout << "序列化后的数据：" << output << endl;

	Persion pp;
	pp.ParseFromString(output);
	cout << "id :" << pp.id() << " name :" << pp.name()
		<< " sex :" << pp.sex() << " age :" << pp.age() << endl;
	return 0;

}
```

> SerilizeToString  将字符串序列化
>
> ParseFromString  解析序列化字符串

类内调用其他类，需要将两个类都序列化

借用mutable_（元素）函数赋给临时变量来修改原内容

```c++
#include<iostream>
#include<string.h>
#include"persion.pb.h"
#include"info.pb.h"
using namespace std;
int main()
{
	/*int32 id = 1;
	string name = 2;
	bytes sex = 3;
	int32 age = 4;*/
	Persion p;
	p.set_id(1001);
	p.add_name();
	p.set_name(0,"路飞");
	p.add_name();
	p.set_name(1,"小红");
	p.add_name();
	p.set_name(2,"小花");
	p.set_sex("男");
	p.set_age(17);
	Info *info;
	info = p.mutable_ip();
	info->set_address("北京");
	info->set_num(911);


	string output;
	p.SerializeToString(&output);
	cout << "序列化后的数据：" << output << endl;

	Persion pp;
	pp.ParseFromString(output);
	Info in = pp.ip();
	cout << "id :" << pp.id() << " name0 :" << pp.name(0) 
		<< " name1 :" << pp.name(1)
		<< " name2 :" << pp.name(2)
		<< " sex :" << pp.sex() << " age :" << pp.age() 
		<<"\naddress :"<<in.address()<<" num :"<<in.num() << endl;
	return 0;

}
```

