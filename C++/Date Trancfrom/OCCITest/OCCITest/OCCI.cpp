#include<iostream>
#include<occi.h>
using namespace std;
using namespace oracle::occi;
int main()
{
	//初始化连接环境
	Environment* env = Environment::createEnvironment();
	//创建一个连接数据库的实例对象
	//参数:用户名,密码,连接串
	//连接串(Oracle服务器地址):IP:端口/实例名
	//192.168.  :1521/orcl
	Connection* conn = env->createConnection("scott","11","192");
	//创建操作对象
	Statement* st = conn->createStatement();
	string sql = "select * from dept";

	st->setSQL(sql);

	ResultSet* result = st->executeQuery();
	while (result->next())
	{
		cout << "no: " << result->getInt(1)
			<< "name: " << result->getInt(2)
			<< "location " << result->getInt(3) << endl;
	}

	//关闭查询的结果集
	st->closeResultSet(result);
	//释放
	conn->terminateStatement(st);
	//释放连接对象
	env->terminateConnection(conn);
	//释放环境对象
	Environment::terminateEnvironment(env);
	return 0;
}