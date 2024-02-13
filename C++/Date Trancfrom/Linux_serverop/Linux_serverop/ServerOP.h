#pragma once
#include<map>
#include<string>
#include"TcpServer.h"
#include"TcpSocket.h"
#include"Message.pb.h"  //为什么加入头文件以后出现大量奇妙的报错?
class ServerOP
{
public:
	enum KeyLen{Len16=16,Len24=24,Len32=32};
	ServerOP(string json);
	~ServerOP();
	void startServer();	//连接(打开)服务器
	string seckeyAgree(RequestMsg* reqMsg); //秘钥协商
	static void* working(void* arg);	//回调函数
	string getRandKey(KeyLen len);	//生成随机字符串
private:
	unsigned int m_port;
	string m_serverID;
	map<pthread_t, TcpSocket*> m_tcp;
	TcpServer* m_server = NULL;
};
