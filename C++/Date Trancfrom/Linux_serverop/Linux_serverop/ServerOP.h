#pragma once
#include<map>
#include<string>
#include"TcpServer.h"
#include"TcpSocket.h"
#include"Message.pb.h"  //Ϊʲô����ͷ�ļ��Ժ���ִ�������ı���?
class ServerOP
{
public:
	enum KeyLen{Len16=16,Len24=24,Len32=32};
	ServerOP(string json);
	~ServerOP();
	void startServer();	//����(��)������
	string seckeyAgree(RequestMsg* reqMsg); //��ԿЭ��
	static void* working(void* arg);	//�ص�����
	string getRandKey(KeyLen len);	//��������ַ���
private:
	unsigned int m_port;
	string m_serverID;
	map<pthread_t, TcpSocket*> m_tcp;
	TcpServer* m_server = NULL;
};
