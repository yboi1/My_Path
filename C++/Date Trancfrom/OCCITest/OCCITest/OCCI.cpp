#include<iostream>
#include<occi.h>
using namespace std;
using namespace oracle::occi;
int main()
{
	//��ʼ�����ӻ���
	Environment* env = Environment::createEnvironment();
	//����һ���������ݿ��ʵ������
	//����:�û���,����,���Ӵ�
	//���Ӵ�(Oracle��������ַ):IP:�˿�/ʵ����
	//192.168.  :1521/orcl
	Connection* conn = env->createConnection("scott","11","192");
	//������������
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

	//�رղ�ѯ�Ľ����
	st->closeResultSet(result);
	//�ͷ�
	conn->terminateStatement(st);
	//�ͷ����Ӷ���
	env->terminateConnection(conn);
	//�ͷŻ�������
	Environment::terminateEnvironment(env);
	return 0;
}